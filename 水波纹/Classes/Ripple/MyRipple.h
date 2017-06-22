#ifndef _MYRIPPLE_H_
#define _MYRIPPLE_H_
#include "GridSprite.h"
namespace ZhiFa
{
	class MyRipple : public GridSprite
	{
	public:
		MyRipple();
		~MyRipple();
		static MyRipple* create(std::string v_path);
        static MyRipple* create(cocos2d::Texture2D *v_tex);
        static MyRipple* create(cocos2d::SpriteFrame *v_spf);
        
        bool init(cocos2d::Texture2D *v_tex);
        virtual void setAnchorPoint(const cocos2d::Vec2& anchorPoint)override;
        virtual void setContentSize(const cocos2d::Size& size)override;
        
		//玩家触碰水波
		void doTouch(const cocos2d::Vec2 &touchPoint, float depth, float r);
		//水波更新
		void updateOnce();
		void update(float dt)override;
        void setRippleStrenth(float v_rippleStrenth);
	protected:
        //初始化顶点
		virtual void initVertex()override;
        //提交更改顶点
		virtual void onSubUpdateVertexBuffer(cocos2d::GLProgram *v_glp)override;
        //干扰后的顶点数组
		std::vector<Position2TexCoord2> m_pertubedVertexes;
		//水波纹的衰减系数，越大衰减越慢
		float m_rippleStrength;
		//用于计算水波纹的动归滚动数组
		std::vector<std::vector<float>> m_dp[2];
		//滚动数组的下标
		int m_backDpInx, m_curDpIdx;
		//时间
		float m_time;
	};
};



#endif