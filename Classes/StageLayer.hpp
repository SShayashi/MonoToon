//
//  StageLayer.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/11.
//
//

#ifndef StageLayer_hpp
#define StageLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Player.hpp"

USING_NS_CC;
class Stagelayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init() override;
    void update(float dt) override;
    
    CREATE_FUNC(Stagelayer);
};


#endif /* StageLayer_hpp */
