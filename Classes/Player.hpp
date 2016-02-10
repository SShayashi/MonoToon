//
//  Player.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/10.
//
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Character.hpp"


class Player :public Character
{
protected:
    Player();
    virtual ~Player();
    char fileName[128] = {0};
    cocos2d::Rect rect;
    cocos2d::SpriteFrame *frame;
    
public:
    bool init() override;
    void update(float dt) override;
    void setAnimation();
    //    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, Acceleration);
    
    CREATE_FUNC(Player);
};
#endif /* Player_hpp */
