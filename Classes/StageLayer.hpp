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
#include "HudLayer.hpp"

USING_NS_CC;
class Stagelayer : public cocos2d::Layer
{
protected:
    Stagelayer();
    virtual ~Stagelayer();
    CC_SYNTHESIZE_RETAIN(Player*, _player, Player);
    CC_SYNTHESIZE_RETAIN(HudLayer*, _hudlayer, HudLayer);
public:

    static cocos2d::Scene* createScene();
    virtual bool init() override;
    void update(float dt) override;
    
    CREATE_FUNC(Stagelayer);
};


#endif /* StageLayer_hpp */
