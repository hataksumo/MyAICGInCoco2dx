#include "cocos2d.h"
using namespace cocos2d;

namespace Curb1Primative
{
	class Vertex
	{
	public:
		Vec3 m_pos;
		Vec2 m_texCoord;
	};
};


class Curb1 : public cocos2d::Node
{
public:
	static Curb1* create();
	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags)override;
	void onDraw();
	void setShader(std::string v_vetx, std::string v_frag);
	void generateBufferObject();
	void bindVertexArray();
	void bindUniforms();
	void setTexture(const char *v_filePath);
	void onMouseBegin(Point v_mp);
	void onMouseMove(Point v_mp);
	void onMouseEnd(Point v_mp);
protected:
	Curb1();
	~Curb1();
	bool init()override;
	void updateMVP();
protected:
	CustomCommand m_renderCommand;
	GLuint m_VAO, m_VBO, m_EBO;

	GLint m_posLoc;
	GLint m_texCordLoc;
	Texture2D *m_texture;

	//GLuint m_texLoc;
	GLint m_modelView_loc;
	GLint m_project_loc;
	Mat4 m_modelViewMatrix, m_projectMatrix;

	GLint m_vertexNum, m_indexNum;

protected:
	Point m_last;
	float m_theta;
	float m_phi;
	float m_radium;
	std::string m_texFileName;
public:
	enum BufferName
	{
		VertexBufferName = 0,
		ElementBufferName = 1
	};
};