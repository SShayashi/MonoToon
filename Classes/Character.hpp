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


class Character :public cocos2d::Sprite
{
protected:
    Character();
    virtual ~Character();
    char fileName[128] = {0};
    cocos2d::Rect rect;
    cocos2d::SpriteFrame *_frame;
    
    //インクの形と動きをキャラは持つことができる
    CC_SYNTHESIZE_RETAIN(cocos2d::Sequence*, _shotMovement,ShotMovement);
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _ink,Ink);
    
public:
    
    void doMove(cocos2d::Vec2 velocity);
    
    bool init() override;
//    void update(float dt) override;
    //    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, Acceleration);
    CC_SYNTHESIZE(float , _oldSpeed, OldSpeed);
    CC_SYNTHESIZE(float , _speed, Speed);

    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::SpriteFrame *> , _frames, Frames);
    CREATE_FUNC(Character);
};

#endif /* Character_hpp */
