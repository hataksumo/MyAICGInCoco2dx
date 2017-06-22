#include "cocos2d.h"
using namespace cocos2d;

namespace Curb2Primative
{
	class Vertex
	{
	public:
		Vec3 m_pos;
		Vec3 m_norm;
		Vec2 m_texCoord;
	};

	class DirectLight
	{
	public:
		Vec3 m_direction;
		Vec3 m_difuseInstence;
		Vec3 m_specularInstence;
		float m_shiness;
	};

	class PointLight
	{
	public:
		Vec3 m_position;
		Vec3 m_difuseInstence;
		Vec3 m_specularInstence;
		float m_shiness;
	};

};


class Curb2 : public cocos2d::Node
{
public:
	static Curb2* create();
	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags)override;
	void onDraw();
	void setShader(std::string v_vetx, std::string v_frag);
	void generateBufferObject();
	void bindVertexArray();
	void bindUniforms();
	void setTexture(const char *v_filePath);
	void iniLight();
	void onMouseBegin(Point v_mp);
	void onMouseMove(Point v_mp);
	void onMouseEnd(Point v_mp);
protected:
	Curb2();
	~Curb2();
	bool init()override;
	void updateMVP();
protected:
	CustomCommand m_renderCommand;
	GLuint m_VAO, m_VBO, m_EBO;

	GLint m_posLoc;
	GLint m_texCordLoc;
	GLint m_normLoc;

	Texture2D *m_texture;

	//GLuint m_texLoc;
	GLint m_model_loc;
    GLint m_modelInv_loc;
	GLint m_view_loc;
	GLint m_project_loc;
	Mat4 m_modelMatrix,m_modelInverseMatrix,m_viewMatrix, m_projectMatrix;
	GLint m_vertexNum, m_indexNum;
protected:
	Point m_last;
	float m_theta;
	float m_phi;
	float m_radium;
	std::string m_texFileName;
protected:
	GLint m_ambientIntenseLoc;
	Vec3 m_ambientIntense;

	GLint m_directionLoc1;
	GLint m_difuseInstenceLoc1;
	GLint m_specularInstenceLoc1;
	GLint m_shinessLoc1;
	Vec3 m_direction1;
	Vec3 m_difuseInstence1;
	Vec3 m_specularInstence1;
	float m_shiness1;

	GLint m_positionLoc2;
	GLint m_difuseInstenceLoc2;
	GLint m_specularInstenceLoc2;
	GLint m_shinessLoc2;
	GLint m_pointLightAttrLoc;
	Vec3 m_position2;
	Vec3 m_difuseInstence2;
	Vec3 m_specularInstence2;
	float m_shiness2;
	Vec3 m_pointLightAttr;

	GLint m_eyePositionLoc;
    Vec3 m_eyePos;
public:
	enum BufferName
	{
		VertexBufferName = 0,
		ElementBufferName = 1
	};
};