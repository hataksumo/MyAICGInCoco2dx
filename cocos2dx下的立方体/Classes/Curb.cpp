//
//  Curb.cpp
//  openGLTest
//
//  Created by chuzy on 14-7-25.
//
//

#include "Curb.h"

using namespace cocos2d;


Curb::Curb():
m_radium(5.0f)
{
    
}

Curb::~Curb()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
}


void Curb::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	renderer->addCommand(&m_renderCommand);
}

void Curb::setShader(std::string v_vetx, std::string v_frag)
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


Curb* Curb::create()
{
    Curb* rtn = new Curb();
    if(rtn&&rtn->init())
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

bool Curb::init()
{
    if(!Node::init())
        return false;
	m_renderCommand.init(_globalZOrder);
	m_renderCommand.func = CC_CALLBACK_0(Curb::onDraw, this);

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

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	


	return true;
}

void Curb::generateBufferObject()
{

	Vertex vertices[] =
	{
		{ Vec3(-1.0f, -1.0f, -1.0f), Vec4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ Vec3(-1.0f, +1.0f, -1.0f), Vec4(0.0f, 0.0f, 0.0f, 1.0f)},
		{ Vec3(+1.0f, +1.0f, -1.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ Vec3(+1.0f, -1.0f, -1.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ Vec3(-1.0f, -1.0f, +1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ Vec3(-1.0f, +1.0f, +1.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ Vec3(+1.0f, +1.0f, +1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ Vec3(+1.0f, -1.0f, +1.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f) }
	};

	GLushort indices[] = {
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
	};
	m_idNum = sizeof(indices) / sizeof(GLushort);

	auto glps = getGLProgramState();
	auto glp = getGLProgram();
	m_posLoc = glp->getAttribLocation("vPosition");
	m_colorLoc = glp->getAttribLocation("vColor");
	m_model_matrix_loc = glp->getUniformLocation("model_matrix");
	m_projection_matrix_loc = glp->getUniformLocation("projection_matrix");


	//glp->use();


	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//传入顶点BUFF
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//传顶点索引BUFF
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STREAM_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(m_VAO);
	//绑定顶点BUFF

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glEnableVertexAttribArray(m_posLoc);
	glVertexAttribPointer(m_posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
	glEnableVertexAttribArray(m_colorLoc);
	glVertexAttribPointer(m_colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vec3)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	m_theta = 1.5f * 3.14f;
	m_phi = 0.25f * 3.14f;
	m_radium = 5.0f;

	updateMVP();
	//Mat4::createLookAt(Vec3(0, 0, 1), Vec3(0, 0, 0), Vec3(0, 1, 0), &m_modelView);
	//m_modelView.translate(0, 0, -5);

	//glps->setUniformMat4(m_model_matrix_loc, m_modelView);

	//glps->setUniformMat4(m_projection_matrix_loc, m_projection);
	glClearColor(0.5f, 0.2f, 0.1f, 1.0f);
	//glEnable(GL_DEPTH);
}

void Curb::onDraw()
{
	auto glp = getGLProgram();
	glp->use();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(m_VAO);
	//glEnable(GL_DEPTH_BUFFER);
	//glEnable(GL_DEPTH_TEST);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glDrawElements(GL_TRIANGLES, m_idNum, GL_UNSIGNED_SHORT,(GLvoid*)0);
	//glDisable(GL_DEPTH_TEST);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

void Curb::updateMVP()
{
	auto glp = getGLProgram();
	glp->use();

	float x = m_radium*sinf(m_phi)*cosf(m_theta);
	float z = m_radium*sinf(m_phi)*sinf(m_theta);
	float y = m_radium*cosf(m_phi);

	//CCLog("x = %f, y = %f, z = %f", x, y, z);

	Mat4::createLookAt(Vec3(x, y, z), Vec3(0, 0, 0), Vec3(0.0f, 1.0f, 0.0f), &m_modelView);
	glp->setUniformLocationWithMatrix4fv(m_model_matrix_loc, m_modelView.m, 1);

	Mat4 projection;
	Size winsize = Director::getInstance()->getWinSize();
	Mat4::createPerspective(0.25f * 180.0f, winsize.width / winsize.height, 0.1, 1000, &m_projection);
	glp->setUniformLocationWithMatrix4fv(m_projection_matrix_loc, m_projection.m, 1);
}

void Curb::onMouseBegin(Point v_mp)
{
	m_last = v_mp;
}

static float XMConvertToRadians(float v_fDegrees)
{
	return v_fDegrees / 180.0f * 3.1415926;
}

void Curb::onMouseMove(Point v_mp)
{
	float dx = XMConvertToRadians(0.25f*static_cast<float>(v_mp.x - m_last.x));
	float dy = XMConvertToRadians(0.25f*static_cast<float>(v_mp.y - m_last.y));

	m_theta += dx;
	m_phi += dy;
	m_phi = clampf(m_phi, 0.1f, 3.1415926 - 0.1f);
	updateMVP();
	m_last = v_mp;
}
void Curb::onMouseEnd(Point v_mp)
{
	
}

void Curb::setTexture(std::string v_imgPath)
{
	m_texture = TextureCache::getInstance()->addImage(v_imgPath);
}
