#include "ZFUniformManager.h"
using namespace cocos2d;
using namespace ZhiFa;


#define UNIFORMCOMPLEMENT(Type,DataType,UniformType) Type::Type()\
{\
	m_uniformType = UniformType; \
}\
	Type::~Type()\
{\
}\
	bool Type::setData(DataType v_data)\
{\
	bool rtn = m_data == v_data; \
	m_data = v_data; \
if (m_manager && (!rtn))\
	m_manager->uniformChanged(); \
	m_updated = false;\
	return rtn; \
}\
	Type* Type::create(std::string v_name, ShaderUniformManager *v_manager, DataType v_iniValue)\
{\
	Type *rtn = new Type(); \
if (rtn&&rtn->init(v_manager,v_name))\
{\
	rtn->setData(v_iniValue); \
	return rtn; \
}\
	return NULL; \
}\
	DataType Type::getData()\
{\
	return m_data; \
}\

ZFManageredUniform::ZFManageredUniform() :
m_updated(false),
m_manager(NULL),
m_name(""),
m_location(-1),
m_uniformType(GLManageredUniformNS::Abstract)
{

}

ZFManageredUniform::~ZFManageredUniform()
{

}

void ZFManageredUniform::setManager(ShaderUniformManager *v_manager)
{
	m_manager = v_manager;
}

void ZFManageredUniform::setName(std::string v_name)
{
	m_name = v_name;
}

std::string ZFManageredUniform::getName()
{
	return m_name;
}

GLManageredUniformNS::UniformType ZFManageredUniform::getType()
{
	return m_uniformType;
}

bool ZFManageredUniform::init(ShaderUniformManager *v_manager, std::string v_name)
{
	m_manager = v_manager;
	m_name = v_name;
	return true;
}

void ZFManageredUniform::setLocation(GLint v_location)
{
	m_location = v_location;
}

void ZFManageredUniform::submitUniform()
{
	if (!m_updated)
	{
		updateUniform();
	}
	m_updated = true;
}


static bool operator == (cocos2d::Mat4 &lft, cocos2d::Mat4 &rgt)
{
    return memcpy(lft.m, lft.m, sizeof(float) * 16) == 0;
}


UNIFORMCOMPLEMENT(GLManageredUniformBool, bool, GLManageredUniformNS::Boolean)
UNIFORMCOMPLEMENT(GLManageredUniformi, int, GLManageredUniformNS::Integer)
UNIFORMCOMPLEMENT(GLManageredUniformf, float, GLManageredUniformNS::Float)
UNIFORMCOMPLEMENT(GLManageredUniformVec2, Vec2, GLManageredUniformNS::Vector2)
UNIFORMCOMPLEMENT(GLManageredUniformVec3, Vec3, GLManageredUniformNS::Vector3)
UNIFORMCOMPLEMENT(GLManageredUniformVec4, Vec4, GLManageredUniformNS::Vector4)
UNIFORMCOMPLEMENT(GLManageredUniformMat4, Mat4, GLManageredUniformNS::Matrix4x4)

void GLManageredUniformi::updateUniform()
{
	glUniform1i(m_location, m_data);
}

void GLManageredUniformBool::updateUniform()
{
	//当前无法传递布尔变量，先用整形替代
	glUniform1i(m_location, m_data ? 1 : 0);
}

void GLManageredUniformf::updateUniform()
{
	glUniform1f(m_location, m_data);
}

void GLManageredUniformVec2::updateUniform()
{
	glUniform2f(m_location,m_data.x,m_data.y);
}

void GLManageredUniformVec3::updateUniform()
{
	glUniform3f(m_location, m_data.x, m_data.y,m_data.z);
}

void GLManageredUniformVec4::updateUniform()
{
	glUniform4f(m_location, m_data.x, m_data.y, m_data.z,m_data.w);
}

void GLManageredUniformMat4::updateUniform()
{
	glUniformMatrix4fv(m_location, 1, false, m_data.m);
}




ShaderUniformManager::ShaderUniformManager() :
m_needUpdate(true)
{

}

ShaderUniformManager::~ShaderUniformManager()
{

}

void ShaderUniformManager::uniformChanged()
{
	m_needUpdate = true;
}

ZFManageredUniform* ShaderUniformManager::addUniform(GLManageredUniformNS::UniformDesc v_desc)
{
	ZFManageredUniform *rtn;
	switch (v_desc.Type)
	{
		case GLManageredUniformNS::Abstract:
			break;
		case GLManageredUniformNS::Boolean:
			rtn = GLManageredUniformBool::create(v_desc.Name, this, false);
			break;
		case GLManageredUniformNS::Integer:
			rtn = GLManageredUniformi::create(v_desc.Name, this, 0);
			break;
		case GLManageredUniformNS::Float:
			rtn = GLManageredUniformf::create(v_desc.Name, this, 0.0f);
			break;
		case GLManageredUniformNS::Vector2:
			rtn = GLManageredUniformVec2::create(v_desc.Name, this, Vec2(0.0f,0.0f));
			break;
		case GLManageredUniformNS::Vector3:
			rtn = GLManageredUniformVec3::create(v_desc.Name, this, Vec3(0.0f, 0.0f, 0.0f));
			break;
		case GLManageredUniformNS::Vector4:
			rtn = GLManageredUniformVec4::create(v_desc.Name, this, Vec4(0.0f, 0.0f, 0.0f,1.0f));
			break;
		case GLManageredUniformNS::Matrix4x4:
		{
			Mat4 m;
			m.setIdentity();
			rtn = GLManageredUniformMat4::create(v_desc.Name, this, m);
		}
			break;
	}
	m_uniformsArray.push_back(rtn);
	m_uniformMap[rtn->getName()] = m_uniformsArray.size()-1;
	return rtn;
}
void ShaderUniformManager::addUniform(std::vector<GLManageredUniformNS::UniformDesc> &v_descArr)
{
	for (unsigned int i = 0; i < v_descArr.size(); i++)
	{
		addUniform(v_descArr[i]);
	}
}

ZFManageredUniform* ShaderUniformManager::getUniform(std::string v_name)
{
	int idx = -1;
	std::map<std::string, int>::iterator it = m_uniformMap.find(v_name);
	if (it != m_uniformMap.end())
	{
		idx = it->second;
		return m_uniformsArray[idx];
	}
	else
	{
		return NULL;
	}
}

void ShaderUniformManager::addUniform(ZFManageredUniform *v_uniform)
{
	m_uniformsArray.push_back(v_uniform);
	m_uniformMap[v_uniform->getName()] = m_uniformsArray.size() - 1;
}

GLManageredUniformBool* ShaderUniformManager::addUniformBool(std::string v_name)
{
	GLManageredUniformBool *rtn = GLManageredUniformBool::create(v_name, this, false);
	addUniform(rtn);
	return rtn;
}

GLManageredUniformi* ShaderUniformManager::addUniformi(std::string v_name)
{
	GLManageredUniformi *rtn = GLManageredUniformi::create(v_name, this, 0);
	addUniform(rtn);
	return rtn;
}
GLManageredUniformf* ShaderUniformManager::addUniformf(std::string v_name)
{
	GLManageredUniformf *rtn = GLManageredUniformf::create(v_name, this, 0.0f);
	addUniform(rtn);
	return rtn;
}
GLManageredUniformVec2* ShaderUniformManager::addUniformVec2(std::string v_name)
{
	GLManageredUniformVec2 *rtn = GLManageredUniformVec2::create(v_name, this, Vec2(0.0f,0.0f));
	addUniform(rtn);
	return rtn;
}
GLManageredUniformVec3* ShaderUniformManager::addUniformVec3(std::string v_name)
{
	GLManageredUniformVec3 *rtn = GLManageredUniformVec3::create(v_name, this, Vec3(0.0f, 0.0f,0.0f));
	addUniform(rtn);
	return rtn;
}
GLManageredUniformVec4* ShaderUniformManager::addUniformVec4(std::string v_name)
{
	GLManageredUniformVec4 *rtn = GLManageredUniformVec4::create(v_name, this, Vec4(0.0f, 0.0f,0.0f,1.0f));
	addUniform(rtn);
	return rtn;
}
GLManageredUniformMat4* ShaderUniformManager::addUniformMat4(std::string v_name)
{
	Mat4 m;
	m.setIdentity();
	GLManageredUniformMat4 *rtn = GLManageredUniformMat4::create(v_name,this,m);
	addUniform(rtn);
	return rtn;
}

GLManageredUniformBool* ShaderUniformManager::getUniformBool(std::string v_name)
{
	ZFManageredUniform *rtn = getUniform(v_name);
	if (rtn&&rtn->getType() == GLManageredUniformNS::Integer)
		return dynamic_cast<GLManageredUniformBool*>(rtn);
	else
		return NULL;
}

GLManageredUniformi* ShaderUniformManager::getUniformi(std::string v_name)
{
	ZFManageredUniform *rtn = getUniform(v_name);
	if (rtn&&rtn->getType() == GLManageredUniformNS::Integer)
		return dynamic_cast<GLManageredUniformi*>(rtn);
	else
		return NULL;
}
GLManageredUniformf* ShaderUniformManager::getUniformf(std::string v_name)
{
	ZFManageredUniform *rtn = getUniform(v_name);
	if (rtn&&rtn->getType() == GLManageredUniformNS::Float)
		return dynamic_cast<GLManageredUniformf*>(rtn);
	else
		return NULL;
}
GLManageredUniformVec2* ShaderUniformManager::getUniformVec2(std::string v_name)
{
	ZFManageredUniform *rtn = getUniform(v_name);
	if (rtn&&rtn->getType() == GLManageredUniformNS::Vector2)
		return dynamic_cast<GLManageredUniformVec2*>(rtn);
	else
		return NULL;
}
GLManageredUniformVec3* ShaderUniformManager::getUniformVec3(std::string v_name)
{
	ZFManageredUniform *rtn = getUniform(v_name);
	if (rtn&&rtn->getType() == GLManageredUniformNS::Vector3)
		return dynamic_cast<GLManageredUniformVec3*>(rtn);
	else
		return NULL;
}
GLManageredUniformVec4* ShaderUniformManager::getUniformVec4(std::string v_name)
{
	ZFManageredUniform *rtn = getUniform(v_name);
	if (rtn&&rtn->getType() == GLManageredUniformNS::Vector4)
		return dynamic_cast<GLManageredUniformVec4*>(rtn);
	else
		return NULL;
}
GLManageredUniformMat4* ShaderUniformManager::getUniformMat4(std::string v_name)
{
	ZFManageredUniform *rtn = getUniform(v_name);
	if (rtn&&rtn->getType() == GLManageredUniformNS::Matrix4x4)
		return dynamic_cast<GLManageredUniformMat4*>(rtn);
	else
		return NULL;
}

void ShaderUniformManager::getUniformLocations(GLProgram *v_program)
{
	for (unsigned int i = 0; i < m_uniformsArray.size(); i++)
	{
		ZFManageredUniform *uniform = m_uniformsArray[i];
		GLint loc = v_program->getUniformLocation(uniform->getName());
		if (loc == -1)continue;
		//CCAssert(~loc, "there is no var in this shader");
		uniform->setLocation(loc);
		uniform->getName();
	}
}

void ShaderUniformManager::updateUniforms()
{
	if (m_needUpdate)
	{
		for (unsigned int i = 0; i < m_uniformsArray.size(); i++)
		{
			ZFManageredUniform *uniform = m_uniformsArray[i];
			uniform->submitUniform();
		}
	}
	m_needUpdate = false;
}