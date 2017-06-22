#ifndef _ZFVERTEXARRAYMANAGER_H_
#define _ZFVERTEXARRAYMANAGER_H_
#include "cocos2d.h"
namespace ZhiFa
{
	class VertexLayout
	{
	public:
		GLint m_loc;
		std::string m_Name;
		int m_offset;
	};

	class VertexArrayManager
	{
	public:
		VertexArrayManager();
		virtual ~VertexArrayManager();
	protected:
		GLuint m_VAO;

	};
};

#endif