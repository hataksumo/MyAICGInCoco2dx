//
//  Curb1.cpp
//  openGLTest
//
//  Created by chuzy on 14-7-25.
//
//

#include "Curb1.h"
#include "GeometryGenerator.h"
using ZhiFa::GeometryGenerator;

using namespace cocos2d;


Curb1::Curb1() :
m_radium(5.0f),
m_VAO(-1),
m_VBO(-1),
m_EBO(-1),
m_posLoc(-1),
m_texCordLoc(-1),
m_modelView_loc(-1),
m_project_loc(-1)
{

}

Curb1::~Curb1()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}


void Curb1::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	renderer->addCommand(&m_renderCommand);
	auto glp = getGLProgram();
	glp->use();
}

void Curb1::setShader(std::string v_vetx, std::string v_frag)
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


Curb1* Curb1::create()
{
	Curb1* rtn = new Curb1();
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

bool Curb1::init()
{
	if (!Node::init())
		return false;
	m_renderCommand.init(_globalZOrder);
	m_renderCommand.func = CC_CALLBACK_0(Curb1::onDraw, this);

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

void Curb1::generateBufferObject()
{
	GeometryGenerator gg;
	GeometryGenerator::MeshData ggm;
	gg.CreateBox(1.0f, 1.0f, 1.0f,ggm);
	Curb1Primative::Vertex *vertex;
	vertex = new Curb1Primative::Vertex[ggm.Vertices.size()];
	for (unsigned int i = 0; i < ggm.Vertices.size(); i++)
	{
		vertex[i].m_pos = ggm.Vertices[i].Position;
		vertex[i].m_texCoord = ggm.Vertices[i].TexC;
	}

	m_vertexNum = ggm.Vertices.size();
	m_indexNum = ggm.Indices.size();

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);

	//传顶点索引BUFF
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ggm.Indices.size() * sizeof(GLushort), (void*)(ggm.Indices.data()), GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//传顶点数据
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Curb1Primative::Vertex) * m_vertexNum, vertex, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] vertex;
	glClearColor(0.05f, 0.05f, 0.3f, 1.0f);
}

void Curb1::bindVertexArray()
{
	auto glp = getGLProgram();
	glp->use();
	m_posLoc = glp->getAttribLocation("in_position");
	m_texCordLoc = glp->getAttribLocation("in_Tex");
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glEnableVertexAttribArray(m_posLoc);
	glVertexAttribPointer(m_posLoc, 3, GL_FLOAT, false, sizeof(Curb1Primative::Vertex), VertexOffset(GLfloat,0));
	glEnableVertexAttribArray(m_texCordLoc);
	glVertexAttribPointer(m_texCordLoc, 2, GL_FLOAT, false, sizeof(Curb1Primative::Vertex), VertexOffset(GLfloat, 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Curb1::bindUniforms()
{
	auto glp = getGLProgram();
	glp->use();
	m_modelView_loc = glp->getUniformLocation("modelViewMatrix");
	m_project_loc = glp->getUniformLocation("projectMatrix");
	m_theta = 1.5f * 3.14f;
	m_phi = 0.25f * 3.14f;
	m_radium = 5.0f;
	updateMVP();
}

void Curb1::setTexture(const char *v_filePath)
{
	m_texture = Director::getInstance()->getTextureCache()->addImage(v_filePath);
	m_texture->retain();
}

void Curb1::onDraw()
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

void Curb1::updateMVP()
{
	auto glp = getGLProgram();
	glp->use();

	float x = m_radium*sinf(m_phi)*cosf(m_theta);
	float z = m_radium*sinf(m_phi)*sinf(m_theta);
	float y = m_radium*cosf(m_phi);

	Mat4::createLookAt(Vec3(x, y, z), Vec3(0, 0, 0), Vec3(0.0f, 1.0f, 0.0f), &m_modelViewMatrix);
	m_modelViewMatrix.scale(Vec3(2.0f, 2.0f, 2.0f));
	glp->setUniformLocationWithMatrix4fv(m_modelView_loc, m_modelViewMatrix.m, 1);
	

	Size winsize = Director::getInstance()->getWinSize();
	Mat4::createPerspective(0.25f * 180.0f, winsize.width / winsize.height, 0.1f, 1000, &m_projectMatrix);
	glp->setUniformLocationWithMatrix4fv(m_project_loc, m_projectMatrix.m, 1);
}

void Curb1::onMouseBegin(Point v_mp)
{
	m_last = v_mp;
}

static float XMConvertToRadians(float v_fDegrees)
{
	return MATH_DEG_TO_RAD(v_fDegrees);
}

void Curb1::onMouseMove(Point v_mp)
{
	float dx = XMConvertToRadians(0.25f*static_cast<float>(v_mp.x - m_last.x));
	float dy = XMConvertToRadians(0.25f*static_cast<float>(v_mp.y - m_last.y));

	m_theta += dx;
	m_phi += dy;
	m_phi = clampf(m_phi, 0.1f, 3.1415926f - 0.1f);
	updateMVP();
	m_last = v_mp;
}
void Curb1::onMouseEnd(Point v_mp)
{

}


