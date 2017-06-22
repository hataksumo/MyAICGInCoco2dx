//
//  Curb.h
//  openGLTest
//
//  Created by chuzy on 14-7-25.
//
//

#ifndef __openGLTest__Curb__
#define __openGLTest__Curb__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;


class CurbFace
{
public:
    Vec3 points[4];
    Vec3 color;
};

struct Vertex
{
	Vec3 Pos;
	Vec4 Color;
};



class Curb : public cocos2d::Node
{
public:
    static Curb* create();
	void draw(Renderer *renderer, const Mat4& transform, uint32_t flags)override;
	void onDraw();
	void setShader(std::string v_vetx, std::string v_frag);
	void setTexture(std::string v_imgPath);
	void generateBufferObject();
	void onMouseBegin(Point v_mp);
	void onMouseMove(Point v_mp);
	void onMouseEnd(Point v_mp);
protected:
    Curb();
    ~Curb();
    bool init()override;
	void updateMVP();
protected:
	CustomCommand m_renderCommand;
	GLuint m_VAO, m_VBO,m_EBO;
	//sCurbFace m_face[6];
	Vec3 m_center;
	float m_size;
	GLuint m_posLoc;
	GLuint m_colorLoc; 
	GLuint m_model_matrix_loc;
	GLuint m_projection_matrix_loc;
	Mat4 m_modelView, m_projection;
	GLsizei m_idNum;
	Texture2D *m_texture;
protected:
	Point m_last;
	float m_theta;
	float m_phi;
	float m_radium;
public:
	enum BufferName
	{
		VertexBufferName = 0,
		ElementBufferName = 1
	};
};


#endif /* defined(__openGLTest__Curb__) */
