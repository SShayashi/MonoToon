//
//  Character.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/10.
//
//

#include "Character.hpp"
USING_NS_CC;
int FRAME_COUNT=3;

Character::Character()
:_speed(NULL)
,_oldSpeed(NULL)
,_shotMovement(NULL)
,_ink(NULL)
{
    
}

Character::~Character(){
    CC_SAFE_RELEASE_NULL(_shotMovement);
    CC_SAFE_RELEASE_NULL(_ink);
}

bool Character::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    /* アニメーションの作成 */
    //    Vector<SpriteFrame *> frames;
    /* アニメ用のフレームを読み込む */
    //    fileName[128] = {0};
//    for(int i = 1 ; i < FRAME_COUNT ; i++ ){
//        sprintf(fileName, "character/futsuo_00%d.png", i);
//        auto rect  = this->getTextureRect();
//        auto frame = SpriteFrame::create(fileName,rect);
//        _frames.pushBack(frame);
//    }
////    this->setAnimation();
//    this->scheduleUpdate();
//    setAngle(Helper::ANGLE8::BOTTOM_CENTER);
    
    
    setDirectionalVec(Vec2(0, -1));
    setShotDistance(60);
    return true;
}

/** 移動量からキャラを動かす
 */
void Character::doMove(Vec2 velocity){
    auto winSize = Director::getInstance()->getWinSize();
    Point newPosition = this->getPosition()+velocity;
    this->setPosition(newPosition.getClampPoint(Vec2(0,0), Vec2(winSize.width, winSize.height)));
}