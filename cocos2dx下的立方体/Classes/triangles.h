#ifndef _TRIANGLES_H_
#define _TRIANGLES_H_
#include "cocos2d.h"
class TwoTrangle : public cocos2d::Node
{
public:
	TwoTrangle();
	~TwoTrangle();
	static TwoTrangle* create();
	void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags)override;
	void onDraw();
protected:
	bool init();
	void initShader();
	void generateBuffers();
	GLuint m_VAO, m_VBO, m_EBO;
	GLint m_positionLoc;
	cocos2d::CustomCommand m_customCommand;
};

#endif