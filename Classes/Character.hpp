//
//  Character.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/10.
//
//

#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Helper.hpp"

class Character :public cocos2d::Sprite
{
protected:
    Character();
    virtual ~Character();
    //以下メンバ変数
    
    //キャラのアニメーション用メンバ
    char fileName[128] = {0};
    cocos2d::Rect rect;
    cocos2d::SpriteFrame *_frame;
    
    //インクの形と動きをキャラは持つことができる
    CC_SYNTHESIZE_RETAIN(cocos2d::Sequence*, _shotMovement,ShotMovement);
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _ink,Ink);
    
    //角度・スピード
    CC_SYNTHESIZE(Vec2, _directionalVec, DirectionalVec);
    CC_SYNTHESIZE(float , _oldSpeed, OldSpeed);
    CC_SYNTHESIZE(float , _speed, Speed);
    CC_SYNTHESIZE(float, _speedOnIka, SpeedOnIka);
    CC_SYNTHESIZE(float, _shotDistance, ShotDistance);
    CC_SYNTHESIZE(float, _shotDistanceError, ShotDistanceError);
    CC_SYNTHESIZE(float, _inkAmount, InkAmount);
    CC_SYNTHESIZE(float, _maxInkAmount, MaxInkAmount);

    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *> , _frames, Frames);

public:
    
    void doMove(cocos2d::Vec2 velocity);
    
    bool init() override;
//    void update(float dt) override;
    //    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, Acceleration);
    CREATE_FUNC(Character);
};

#endif /* Character_hpp */
