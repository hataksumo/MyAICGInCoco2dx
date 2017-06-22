//
//  Curb2.cpp
//  openGLTest
//
//  Created by chuzy on 14-7-25.
//
//

#include "Curb2.h"
#include "GeometryGenerator.h"
#include "ZhiFaMath.h"
using ZhiFa::GeometryGenerator;

using namespace cocos2d;


Curb2::Curb2() :
m_radium(5.0f),
m_VAO(-1),
m_VBO(-1),
m_EBO(-1),
m_posLoc(-1),
m_texCordLoc(-1),
m_model_loc(-1),
m_view_loc(-1),
m_project_loc(-1),
m_modelInv_loc(-1),

m_ambientIntenseLoc(-1),
m_ambientIntense(0.0f,0.0f,0.0f),
m_directionLoc1(-1),
m_difuseInstenceLoc1(-1),
m_specularInstenceLoc1(-1),
m_shinessLoc1(-1),
m_shiness1(0.0f),
m_positionLoc2(-1),
m_difuseInstenceLoc2(-1),
m_specularInstenceLoc2(-1),
m_shinessLoc2(-1),
m_pointLightAttrLoc(-1),
m_shiness2(0.0f),
m_pointLightAttr(1.0f,0.0f,0.0f),
m_eyePositionLoc(-1)
{

}

Curb2::~Curb2()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}


void Curb2::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	renderer->addCommand(&m_renderCommand);
	auto glp = getGLProgram();
	glp->use();
}

void Curb2::setShader(std::string v_vetx, std::string v_frag)
{
	auto fileUtiles = FileUtils::getInstance();

	// frag
	auto fragmentFilePath = fileUtiles->fullPathForFilename(v_frag);
	auto fragSource = fileUtiles->getStringFromFile(fragmentFilePath);

	// vert
	std::string vertSource;
	if (v_vetx.empty()) {
		vertSource = ccPositionTextureColor_vert;
	}
	else {
		std::string vertexFilePath = fileUtiles->fullPathForFilename(v_vetx);
		vertSource = fileUtiles->getStringFromFile(vertexFilePath);
	}

	auto glprogram = GLProgram::createWithByteArrays(vertSource.c_str(), fragSource.c_str());
	auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
	setGLProgramState(glprogramstate);
}


Curb2* Curb2::create()
{
	Curb2* rtn = new Curb2();
	if (rtn&&rtn->init())
	{
		rtn->autorelease();
		return rtn;
	}
	else
	{
		delete rtn;
		return NULL;
	}
}

bool Curb2::init()
{
	if (!Node::init())
		return false;
	m_renderCommand.init(_globalZOrder);
	m_renderCommand.func = CC_CALLBACK_0(Curb2::onDraw, this);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		onMouseBegin(touch->getLocation());
		return true;
	};
	listener->onTouchMoved = [=](Touch* touch, Event* event)
	{
		onMouseMove(touch->getLocation());
	};
	listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		onMouseEnd(touch->getLocation());
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void Curb2::generateBufferObject()
{
	GeometryGenerator gg;
	GeometryGenerator::MeshData ggm;
	gg.CreateBox(3.0f, 3.0f, 3.0f,ggm);
	Curb2Primative::Vertex *vertex;
	vertex = new Curb2Primative::Vertex[ggm.Vertices.size()];
	for (unsigned int i = 0; i < ggm.Vertices.size(); i++)
	{
		vertex[i].m_pos = ggm.Vertices[i].Position;
		vertex[i].m_texCoord = ggm.Vertices[i].TexC;
		vertex[i].m_norm = ggm.Vertices[i].Normal;
        
        log("pos = {%f,%f,%f},norm = {%f,%f,%f}",vertex[i].m_pos.x,vertex[i].m_pos.y,vertex[i].m_pos.z,
            vertex[i].m_norm.x,vertex[i].m_norm.y,vertex[i].m_norm.z);
	}

	m_vertexNum = ggm.Vertices.size();
	m_indexNum = ggm.Indices.size();

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);

	//¥´∂•µ„À˜“˝BUFF
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ggm.Indices.size() * sizeof(GLushort), (void*)(ggm.Indices.data()), GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//¥´∂•µ„ ˝æ›
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Curb2Primative::Vertex) * m_vertexNum, vertex, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] vertex;
	glClearColor(0.05f, 0.03f, 0.1f, 1.0f);
}

void Curb2::bindVertexArray()
{
	auto glp = getGLProgram();
	glp->use();
	m_posLoc = glp->getAttribLocation("in_position");
	m_texCordLoc = glp->getAttribLocation("in_tex");
	m_normLoc = glp->getAttribLocation("in_norm");
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glEnableVertexAttribArray(m_posLoc);
	glVertexAttribPointer(m_posLoc, 3, GL_FLOAT, false, sizeof(Curb2Primative::Vertex), VertexOffset(GLfloat,0));

	glEnableVertexAttribArray(m_normLoc);
	glVertexAttribPointer(m_normLoc, 3, GL_FLOAT, false, sizeof(Curb2Primative::Vertex), VertexOffset(GLfloat,3));

	glEnableVertexAttribArray(m_texCordLoc);
	glVertexAttribPointer(m_texCordLoc, 2, GL_FLOAT, false, sizeof(Curb2Primative::Vertex), VertexOffset(GLfloat,6));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Curb2::bindUniforms()
{
	auto glp = getGLProgram();
	glp->use();
	m_model_loc = glp->getUniformLocationForName("modelMatrix");
    m_modelInv_loc = glp->getUniformLocationForName("modelInverseMatrix");
	m_view_loc = glp->getUniformLocationForName("viewMatrix");
	m_project_loc = glp->getUniformLocationForName("projectMatrix");
	m_theta = 1.5f * 3.14f;
	m_phi = 0.25f * 3.14f;
	m_radium = 6.5f;
    
    float x = m_radium*sinf(m_phi)*cosf(m_theta);
	float z = m_radium*sinf(m_phi)*sinf(m_theta);
	float y = m_radium*cosf(m_phi);
    m_eyePos = Vec3(x,y,z);
    m_phi = m_theta = 0;
    
    Mat4::createLookAt(Vec3(m_eyePos.x, m_eyePos.y, m_eyePos.z), Vec3(0, 0, 0), Vec3(0.0f, 1.0f, 0.0f), &m_viewMatrix);
	glp->setUniformLocationWithMatrix4fv(m_view_loc, m_viewMatrix.m, 1);
    
	Size winsize = Director::getInstance()->getWinSize();
	Mat4::createPerspective(0.25f * 180.0f, winsize.width / winsize.height, 0.1f, 1000, &m_projectMatrix);
	glp->setUniformLocationWithMatrix4fv(m_project_loc, m_projectMatrix.m, 1);
    
    
	updateMVP();
}


void Curb2::iniLight()
{
	auto glp = getGLProgram();
	glp->use();
	m_ambientIntenseLoc = glp->getUniformLocation("ambientIntense");
	m_directionLoc1 = glp->getUniformLocation("directLightDir");
	m_difuseInstenceLoc1 = glp->getUniformLocation("difuseIntense1");
	m_specularInstenceLoc1 = glp->getUniformLocation("specularIntense1");
	m_shinessLoc1 = glp->getUniformLocation("shiness1");

	m_positionLoc2 = glp->getUniformLocation("lightPos");
	m_difuseInstenceLoc2 = glp->getUniformLocation("difuseIntense2");
	m_specularInstenceLoc2 = glp->getUniformLocation("m_specularInstenceLoc2");
	m_shinessLoc2 = glp->getUniformLocation("shiness2");
	m_pointLightAttrLoc = glp->getUniformLocation("attr");

	m_ambientIntense = Vec3(0.1,0.1,0.1);
	m_direction1 = Vec3(0,-1,1);
	m_direction1.normalize();
	m_difuseInstence1 = Vec3(1.0f, 1.0f, 1.0f);
	m_specularInstence1 = Vec3(0.35f,0.35f,0.35f);

	//m_difuseInstence1 = Vec3(0.0f, 0.0f, 0.0f);
	//m_specularInstence1 = Vec3(0.0f, 0.0f, 0.0f);

	m_shiness1 = 2.8f;

	m_position2 = Vec3(0.0, 1.5, 0.4);
	m_difuseInstence2 = Vec3(3.55f, 3.55f, 3.55f);
	m_specularInstence2 = Vec3(0.85f, 0.85f, 0.85f);
	m_shiness2 = 2.3f;

	m_eyePositionLoc = glp->getUniformLocation("eyePos");
	m_pointLightAttr.set(0.3f, 0.3f, 0.5f);
    
	glp->setUniformLocationWith3f(m_ambientIntenseLoc, m_ambientIntense.x, m_ambientIntense.y, m_ambientIntense.z);
	glp->setUniformLocationWith3f(m_directionLoc1, m_direction1.x, m_direction1.y, m_direction1.z);
	glp->setUniformLocationWith3f(m_difuseInstenceLoc1, m_difuseInstence1.x, m_difuseInstence1.y, m_difuseInstence1.z);
	glp->setUniformLocationWith3f(m_specularInstenceLoc1, m_specularInstence1.x, m_specularInstence1.y, m_specularInstence1.z);
	glp->setUniformLocationWith1f(m_shinessLoc1, m_shiness1);
	glp->setUniformLocationWith3f(m_positionLoc2, m_position2.x, m_position2.y, m_position2.z);
	glp->setUniformLocationWith3f(m_difuseInstenceLoc2, m_difuseInstence2.x, m_difuseInstence2.y, m_difuseInstence2.z);
	glp->setUniformLocationWith3f(m_specularInstenceLoc2, m_specularInstence2.x, m_specularInstence2.y, m_specularInstence2.z);
	glp->setUniformLocationWith1f(m_shinessLoc2, m_shiness2);
	glp->setUniformLocationWith3f(m_pointLightAttrLoc, m_pointLightAttr.x, m_pointLightAttr.y, m_pointLightAttr.z);
    
    glp->setUniformLocationWith3f(m_eyePositionLoc, m_eyePos.x, m_eyePos.y, m_eyePos.z);
}


void Curb2::setTexture(const char *v_filePath)
{
	m_texture = Director::getInstance()->getTextureCache()->addImage(v_filePath);
	m_texture->retain();
}

void Curb2::onDraw()
{
	auto glp = getGLProgram();
	glp->use();
	glBindTexture(GL_TEXTURE_2D, m_texture->getName());
	//TextureAtlas
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indexNum, GL_UNSIGNED_SHORT, (GLvoid*)0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

void Curb2::updateMVP()
{
	auto glp = getGLProgram();
	glp->use();
    
    //Quaternion qy;
    //qy.set(Vec3(0,1,0), m_theta);
    //Quaternion qx;
    //qx.set(Vec3(1,0,0),m_phi);
    
    m_modelMatrix.setIdentity();
    m_modelMatrix.rotateY(ZhiFa::Math::RadToAngle(m_theta));
    m_modelMatrix.rotateX(ZhiFa::Math::RadToAngle(m_phi));
    
    glp->setUniformLocationWithMatrix4fv(m_model_loc, m_modelMatrix.m, 1);

	m_modelInverseMatrix = m_modelMatrix.getInversed().getTransposed();
	glp->setUniformLocationWithMatrix4fv(m_modelInv_loc, m_modelInverseMatrix.m, 1);
    
}

void Curb2::onMouseBegin(Point v_mp)
{
	m_last = v_mp;
}

static float XMConvertToRadians(float v_fDegrees)
{
	return MATH_DEG_TO_RAD(v_fDegrees);
}

void Curb2::onMouseMove(Point v_mp)
{
	float dx = XMConvertToRadians(0.25f*static_cast<float>(v_mp.x - m_last.x));
	float dy = XMConvertToRadians(0.25f*static_cast<float>(v_mp.y - m_last.y));
    
    dx /= m_radium * m_radium;
    dy /= m_radium * m_radium;
    
	m_theta += dx;
	m_phi += dy;
	//m_phi = clampf(m_phi, 0.1f, 3.1415926f - 0.1f);
	updateMVP();
	m_last = v_mp;
}
void Curb2::onMouseEnd(Point v_mp)
{

}


