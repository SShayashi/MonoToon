//
//  Enemy.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/12.
//
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Character.hpp"


class Enemy :public Character
{
protected:
    Enemy();
    virtual ~Enemy();
    CC_SYNTHESIZE(int , _shotRate, ShotRate);
public:
    bool init() override;
    void update(float dt) override;
    void setAnimation();
    //    CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _acceleration, Acceleration);
    
    CREATE_FUNC(Enemy);
};

#endif /* Enemy_hpp */
