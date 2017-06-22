#include "ColoredTriangles.h"
#include "GeometryGenerator.h"
using namespace cocos2d;
using namespace ColoredTrianglePrimative;


ColoredTrangle::ColoredTrangle():
m_positionLoc(-1)
{

}
ColoredTrangle::~ColoredTrangle()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
	iniUniforms();
}
ColoredTrangle* ColoredTrangle::create()
{
	ColoredTrangle *rtn = new ColoredTrangle();
	if (rtn&&rtn->init())
	{
		rtn->autorelease();
		return rtn;
	}
	CC_SAFE_DELETE(rtn);
	return NULL;
}

bool ColoredTrangle::init()
{
	if (!Node::init())
		return false;
	initShader();
	generateBuffers();
	iniUniforms();
	return true;
}
void ColoredTrangle::initShader()
{
	const std::string vertexPath = "shaders/triangle2.vsh";
	const std::string fragPath = "shaders/triangle2.fsh";
	auto fileUtiles = FileUtils::getInstance();
	// frag
	std::string fragmentFilePath = fileUtiles->fullPathForFilename(fragPath);
	std::string fragSource = fileUtiles->getStringFromFile(fragmentFilePath);
	// vert
	std::string vertexFilePath = fileUtiles->fullPathForFilename(vertexPath);
	std::string vertSource = fileUtiles->getStringFromFile(vertexFilePath);

	GLProgram* glprogram = GLProgram::createWithByteArrays(vertSource.c_str(), fragSource.c_str());
	GLProgramState* glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
	setGLProgramState(glprogramstate);
}
void ColoredTrangle::generateBuffers()
{
	auto glp = getGLProgram();
	glp->use();
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	Vertex vertices[] = {
		{ Vec2(-0.90f, -0.90f), Vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ Vec2(0.85f, -0.90f), Vec4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ Vec2(-0.90f, 0.85f), Vec4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ Vec2(0.90f, -0.85f), Vec4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ Vec2(0.90f, 0.90f), Vec4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ Vec2(-0.85f, 0.90f), Vec4(1.0f, 0.0f, 1.0f, 1.0f) }
	};

	m_positionLoc = glp->getAttribLocation("position");
	m_colorLoc = glp->getAttribLocation("color");

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(m_positionLoc);
	glVertexAttribPointer(m_positionLoc, 2, GL_FLOAT, false, sizeof(Vertex), VertexOffset(GLfloat, 0));
	glEnableVertexAttribArray(m_colorLoc);
	glVertexAttribPointer(m_colorLoc, 4, GL_FLOAT, false, sizeof(Vertex), VertexOffset(GLfloat, 2));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ColoredTrangle::iniUniforms()
{
	auto glp = getGLProgram();
	glp->use();
	m_vmatrixLoc = glp->getUniformLocation("vmatrix");
	m_cmatrixLoc = glp->getUniformLocation("cmatrix");
	m_vmatrix.setIdentity();
	m_vmatrix.scale(Vec3(0.5, 0.5, 0.5));
	m_vmatrix.rotateZ(45.0f);
	glp->setUniformLocationWithMatrix4fv(m_vmatrixLoc, m_vmatrix.m, 1);

	m_cmatrix.setIdentity();
	m_cmatrix.rotate(Vec3(1, 1, 1), 37);

	glp->setUniformLocationWithMatrix4fv(m_cmatrixLoc, m_cmatrix.m, 1);
}

void ColoredTrangle::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
	m_customCommand.init(_globalZOrder);
	m_customCommand.func = CC_CALLBACK_0(ColoredTrangle::onDraw, this);
	renderer->addCommand(&m_customCommand);
}
void ColoredTrangle::onDraw()
{
	auto glp = getGLProgram();
	glp->use();
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glBindVertexArray(0);
}