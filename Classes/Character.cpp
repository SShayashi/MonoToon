//
//  Character.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/10.
//
//

#include "Character.hpp"
USING_NS_CC;

Character::Character()
:_speed(NULL)
,_oldSpeed(NULL)
,_speedOnIka(NULL)
,_inkAmount(NULL)
,_maxInkAmount(NULL)
,_shotDistance(NULL)
,_shotDistanceError(NULL)
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