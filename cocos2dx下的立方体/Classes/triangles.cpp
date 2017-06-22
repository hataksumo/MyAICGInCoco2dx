#include "triangles.h"
#include "GeometryGenerator.h"
using namespace cocos2d;


TwoTrangle::TwoTrangle():
m_positionLoc(-1)
{

}
TwoTrangle::~TwoTrangle()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
}
TwoTrangle* TwoTrangle::create()
{
	TwoTrangle *rtn = new TwoTrangle();
	if (rtn&&rtn->init())
	{
		rtn->autorelease();
		return rtn;
	}
	CC_SAFE_DELETE(rtn);
	return NULL;
}

bool TwoTrangle::init()
{
	if (!Node::init())
		return false;
	initShader();
	generateBuffers();
	return true;
}
void TwoTrangle::initShader()
{
	const std::string vertexPath = "shaders/triangle.vsh";
	const std::string fragPath = "shaders/triangle.fsh";
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
void TwoTrangle::generateBuffers()
{
	auto glp = getGLProgram();
	glp->use();
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	//glGenBuffers(1, &m_EBO);
	GLfloat vertices[6][2] = {
		{ -0.90f, -0.90f }, // Triangle 1
		{ 0.85f, -0.90f },
		{ -0.90f, 0.85f },
		{ 0.90f, -0.85f }, // Triangle 2
		{ 0.90f, 0.90f },
		{ -0.85f, 0.90f }
	};
	m_positionLoc = glp->getAttribLocation("position");
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(m_positionLoc);
	glVertexAttribPointer(m_positionLoc, 2, GL_FLOAT, false, 0, VertexOffset(GLfloat, 0));
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void TwoTrangle::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)
{
	m_customCommand.init(_globalZOrder);
	m_customCommand.func = CC_CALLBACK_0(TwoTrangle::onDraw, this);
	renderer->addCommand(&m_customCommand);
}
void TwoTrangle::onDraw()
{
	auto glp = getGLProgram();
	glp->use();
	glBindVertexArray(m_VAO);
	glDrawArrays(GL_TRIANGLES, 0, 12);
	glBindVertexArray(0);
}