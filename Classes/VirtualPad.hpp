//
//  VirtualPad.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/07.
//
//
#ifndef CocosProjectTest1_VirtualPad_h
#define CocosProjectTest1_VirtualPad_h

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

/**
 *VirtualPadクラス.
 */
class VirtualPad :public::Layer {
private:
    /*コンストラクタ*/
    VirtualPad();
    /*デストラクタ*/
    ~VirtualPad();
    //表示フラグ
    bool touchFlag;
    //Padの初期位置
    float init_x;
    float init_y;
    //現在位置
    float now_x;
    float now_y;
    //移動量
    float d_x;
    float d_y;
    //移動sin,cos
    float way_x;
    float way_y;
    //最大半径
    float max_r;
    //現在の半径
    float now_r;
    //角度
    float angle;
    //角度テーブル
    float fsin[360];
    float fcos[360];
    //タッチID
    int touchID;
    
public:
    //Pad下地
    CC_SYNTHESIZE_RETAIN(Sprite*, _padBack, PadBack);
    //Pad
    CC_SYNTHESIZE_RETAIN(Sprite*, _padFront, PadFront);
    void update(float dt)override;
    CREATE_FUNC(VirtualPad);
    bool init() override;
    
    void startPad(int x,int y,int touch_id);
    void endPad(int touch_id);
    void update(int x,int y,int touch_id);
    float getCosX();
    float getSinY();
    bool isTouch();
    int get4Way();
    int get8Way();
    int getSpeed();
    Vec2 getMovent();
    Sprite* getPadBack();
    
};

#endif
