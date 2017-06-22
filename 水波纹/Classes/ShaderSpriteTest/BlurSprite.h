#ifndef _BLURSPRITE_H_
#define _BLURSPRITE_H_
#include "../ShaderHelper/2dShaderSprite.h"

namespace ZhiFa
{
	enum class BlurSpriteEnum
	{
		XBlur,
		YBlur
	};

	class BlurSpriteXY : public ShaderSprite2d
	{
	public:
		BlurSpriteXY();
		virtual ~BlurSpriteXY();
		static BlurSpriteXY* create(cocos2d::Texture2D *v_tex, BlurSpriteEnum v_blurType);
		void setBlurSize(int v_size);
		void setAddFactor(cocos2d::Vec4 v_addFactor);
		void setMulFactor(cocos2d::Vec4 v_mulFactor);
		void initWeights();
	protected:
		bool init(cocos2d::Texture2D *v_tex);
		bool initShader(BlurSpriteEnum v_blurType);
		virtual void addUniformToManager()override;
		virtual void beginDraw()override;
		int m_blurSize;
		cocos2d::Vec2 m_pixelSize;
		float m_simga;
		BlurSpriteEnum m_blurType;
		GLManageredUniformi *m_uRadius;
		GLManageredUniformVec2 *m_uPixelSize;

		GLManageredUniformVec4 *u_mulFactor;
		GLManageredUniformVec4 *u_addFactor;

		std::vector<float> m_weights;
		bool m_weightNeedInit;
	};

	class BlurSprite : public cocos2d::Sprite
	{
	public:
		BlurSprite();
		virtual ~BlurSprite();
		virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
		static BlurSprite* create(std::string v_fpath);
		void setBlurSize(int v_blurSize);
	protected:
		bool init(std::string v_fPath);
		void setBlurTexture(float v_dt);
		BlurSpriteXY *m_xBlur, *m_yBlur;
		cocos2d::Texture2D *m_tex;
		int m_blurSize;
		cocos2d::RenderTexture *m_rttX, *m_rttY;
	};
};





#endif