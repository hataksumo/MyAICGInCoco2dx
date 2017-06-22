#include "2dShaderNode.h"

using namespace cocos2d;
using namespace ZhiFa;

ShaderNode2D::ShaderNode2D():
m_VAO(0),
m_VBO(0),
m_EBO(0),
m_vertexChanged(true)
{

}

ShaderNode2D::~ShaderNode2D()
{
	if (Configuration::getInstance()->supportsShareableVAO())
		glDeleteVertexArrays(1,&m_VAO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);
	delete m_uniformManager;
}

bool ShaderNode2D::initShaderProgram(std::string v_vertPath, std::string v_fragPath)
{
	auto fileUtiles = FileUtils::getInstance();
	auto fragmentFilePath = fileUtiles->fullPathForFilename(v_fragPath);
	auto fragSource = fileUtiles->getStringFromFile(fragmentFilePath);
	std::string vertexFilePath = fileUtiles->fullPathForFilename(v_vertPath);
	auto vertSource = fileUtiles->getStringFromFile(vertexFilePath);
	return initShaderProgramByData(vertSource.c_str(), fragSource.c_str());
}

bool ShaderNode2D::initShaderProgramByData(const char *v_vert, const char *v_frag)
{
	auto glprogram = GLProgram::createWithByteArrays(v_vert, v_frag);
	auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
	setGLProgramState(glprogramstate);
	setGLProgram(glprogram);
	m_uniformManager = new ShaderUniformManager();
	//m_uniformManager->setProgramID(glp->getProgram());
	m_mvpMatrix = m_uniformManager->addUniformMat4("CC_MVPMatrix");
	addUniformToManager();
	m_uniformManager->getUniformLocations(glprogram);
	genBuffers();
	genAttributeLoc(glprogram);
	if (Configuration::getInstance()->supportsShareableVAO())
		GL::bindVAO(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	bindVertexLayout(glprogram);
	if (Configuration::getInstance()->supportsShareableVAO())
		GL::bindVAO(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return true;
}

bool ShaderNode2D::initShaderProgram(GLProgram *v_compiledGlp)
{
	auto glprogramstate = GLProgramState::getOrCreateWithGLProgram(v_compiledGlp);
	setGLProgramState(glprogramstate);
	setGLProgram(v_compiledGlp);
	m_uniformManager = new ShaderUniformManager();
	//m_uniformManager->setProgramID(glp->getProgram());

	m_mvpMatrix = m_uniformManager->addUniformMat4("CC_MVPMatrix");
	addUniformToManager();
	m_uniformManager->getUniformLocations(v_compiledGlp);
	return true;
}

void ShaderNode2D::initGeometry()
{
	GLProgram *glp = getGLProgram();
	glp->use();
	subUpdateVertexBuffer(glp);
}

void ShaderNode2D::genBuffers()
{
	if (Configuration::getInstance()->supportsShareableVAO())
		glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
}

void ShaderNode2D::subUpdateVertexBuffer(GLProgram *v_glp)
{
	if (m_vertexChanged)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		onSubUpdateVertexBuffer(v_glp);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	m_vertexChanged = false;
}

void ShaderNode2D::beginDraw()
{

}

void ShaderNode2D::drawTemplate(const Mat4& transform, uint32_t flags)
{
	GLProgram *glp = getGLProgram();
	glp->use();
    //glp->setUniformsForBuiltins(transform);
	Mat4 mvpMatrix = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION) * transform;
	m_mvpMatrix->setData(mvpMatrix);

	subUpdateVertexBuffer(glp);
    if(Configuration::getInstance()->supportsShareableVAO())
    {
		GL::bindVAO(m_VAO);
		beginDraw();
		m_uniformManager->updateUniforms();
        onDraw(glp);
		GL::bindVAO(0);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        bindVertexLayout(glp);
		beginDraw();
		m_uniformManager->updateUniforms();
        onDraw(glp);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void ShaderNode2D::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	m_renderCommand.init(_globalZOrder);
	m_renderCommand.func = CC_CALLBACK_0(ShaderNode2D::drawTemplate, this, transform, flags);
	renderer->addCommand(&m_renderCommand);
}

bool ShaderNode2D::init()
{
	auto glp = getGLProgram();
	genBuffers();
	//genLocs();
	bindVertexLayout(glp);
	return true;
}
