#ifndef _ZFUNIFORMMANAGER_H_
#define _ZFUNIFORMMANAGER_H_

#include "cocos2d.h"

namespace GLManageredUniformNS
{
	enum UniformType
	{
		Abstract,
		Boolean,
		Integer,
		Float,
		Vector2,
		Vector3,
		Vector4,
		Matrix4x4
	};

	struct UniformDesc
	{
		std::string Name;
		UniformType Type;
		UniformDesc(){}
		UniformDesc(std::string name, UniformType type)
		{
			Name = name;
			Type = type;
		}
	};
};

namespace ZhiFa
{
	class ShaderUniformManager;
	class ZFManageredUniform
	{
	public:
		//set the manager
		void setManager(ShaderUniformManager *v_manager);
		//setUnifromName
		void setName(std::string v_name);
		//get unifrom name
		std::string getName();
		//get the uniform type
		GLManageredUniformNS::UniformType getType();
		//set the unoform location
		void setLocation(GLint v_location);
		//update Uniform
		void submitUniform();
	protected:
		ZFManageredUniform();
		virtual ~ZFManageredUniform();
		bool init(ShaderUniformManager *v_manager, std::string v_name);
		virtual void updateUniform() = 0;
		//uniform是否更新过了
		bool m_updated;
		//uniform的名字
		std::string m_name;
		//uniform在shader中的layout
		GLint m_location;
		//uniform的管理员
		ShaderUniformManager *m_manager;
		//uniform的类型
		GLManageredUniformNS::UniformType m_uniformType;
	};

	class GLManageredUniformBool : public ZFManageredUniform
	{
	public:
		virtual ~GLManageredUniformBool();
		static GLManageredUniformBool* create(std::string v_name, ShaderUniformManager *v_manager, bool v_iniValue);
		bool setData(bool v_data);
		bool getData();
	protected:
		GLManageredUniformBool();
		virtual void updateUniform();
		bool m_data;
	};

	class GLManageredUniformi : public ZFManageredUniform
	{
	public:
		virtual ~GLManageredUniformi();
		static GLManageredUniformi* create(std::string v_name, ShaderUniformManager *v_manager, int v_iniValue);
		bool setData(int v_data);
		int getData();
	protected:
		GLManageredUniformi();
		virtual void updateUniform();
		int m_data;
	};

	class GLManageredUniformf : public ZFManageredUniform
	{
	public:
		virtual ~GLManageredUniformf();
		static GLManageredUniformf* create(std::string v_name, ShaderUniformManager *v_manager, float v_iniValue);
		bool setData(float v_data);
		float getData();
	protected:
		GLManageredUniformf();
		virtual void updateUniform();
		float m_data;
	};

	class GLManageredUniformVec2 : public ZFManageredUniform
	{
	public:
		virtual ~GLManageredUniformVec2();
		static GLManageredUniformVec2* create(std::string v_name, ShaderUniformManager *v_manager, cocos2d::Vec2 v_iniValue);
		bool setData(cocos2d::Vec2 v_data);
		cocos2d::Vec2 getData();
	protected:
		GLManageredUniformVec2();
		virtual void updateUniform();
		cocos2d::Vec2 m_data;
	};

	class GLManageredUniformVec3 : public ZFManageredUniform
	{
	public:
		virtual ~GLManageredUniformVec3();
		static GLManageredUniformVec3* create(std::string v_name, ShaderUniformManager *v_manager, cocos2d::Vec3 v_iniValue);
		bool setData(cocos2d::Vec3 v_data);
		cocos2d::Vec3 getData();
	protected:
		GLManageredUniformVec3();
		virtual void updateUniform();
		cocos2d::Vec3 m_data;
	};

	class GLManageredUniformVec4 : public ZFManageredUniform
	{
	public:
		virtual ~GLManageredUniformVec4();
		static GLManageredUniformVec4* create(std::string v_name, ShaderUniformManager *v_manager, cocos2d::Vec4 v_iniValue);
		bool setData(cocos2d::Vec4 v_data);
		cocos2d::Vec4 getData();
	protected:
		GLManageredUniformVec4();
		virtual void updateUniform();
		cocos2d::Vec4 m_data;
	};

	class GLManageredUniformMat4 : public ZFManageredUniform
	{
	public:
		virtual ~GLManageredUniformMat4();
		static GLManageredUniformMat4* create(std::string v_name, ShaderUniformManager *v_manager, cocos2d::Mat4 v_iniValue);
		bool setData(cocos2d::Mat4 v_data);
		cocos2d::Mat4 getData();
	protected:
		GLManageredUniformMat4();
		virtual void updateUniform();
		cocos2d::Mat4 m_data;
	};

	class ShaderUniformManager : public cocos2d::Ref
	{
	public:
		ShaderUniformManager();
		virtual ~ShaderUniformManager();
		//calling this method when some uniform under this manager has changed
		void uniformChanged();
		//void setProgramID(GLuint v_programID);
		ZFManageredUniform* addUniform(GLManageredUniformNS::UniformDesc v_desc);
		void addUniform(std::vector<GLManageredUniformNS::UniformDesc> &v_descArr);
		void addUniform(ZFManageredUniform *v_uniform);
		void getUniformLocations(cocos2d::GLProgram *v_program);
		void updateUniforms();

		GLManageredUniformBool* addUniformBool(std::string v_name);
		GLManageredUniformi* addUniformi(std::string v_name);
		GLManageredUniformf* addUniformf(std::string v_name);
		GLManageredUniformVec2* addUniformVec2(std::string v_name);
		GLManageredUniformVec3* addUniformVec3(std::string v_name);
		GLManageredUniformVec4* addUniformVec4(std::string v_name);
		GLManageredUniformMat4* addUniformMat4(std::string v_name);

		ZFManageredUniform* getUniform(std::string v_name);
		GLManageredUniformBool* getUniformBool(std::string v_name);
		GLManageredUniformi* getUniformi(std::string v_name);
		GLManageredUniformf* getUniformf(std::string v_name);
		GLManageredUniformVec2* getUniformVec2(std::string v_name);
		GLManageredUniformVec3* getUniformVec3(std::string v_name);
		GLManageredUniformVec4* getUniformVec4(std::string v_name);
		GLManageredUniformMat4* getUniformMat4(std::string v_name);


	protected:
		bool m_needUpdate;
		//GLuint m_programID;
		std::vector<ZFManageredUniform*> m_uniformsArray;
		std::map<std::string, int> m_uniformMap;
	};
};




#endif