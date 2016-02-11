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
#include "Character.hpp"

USING_NS_CC;
class StageLayer : public cocos2d::Layer
{
private:
    float time;
private:
    StageLayer();
    virtual ~StageLayer();
    CC_SYNTHESIZE_RETAIN(Player*, _player, Player);
    CC_SYNTHESIZE_RETAIN(HudLayer*, _hudlayer, HudLayer);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _shotInks, ShotInks);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _drawedInks, DrawedInks);
public:

    void shotInk(Character& chara);
    void drawInk();
    bool removeShotInk(cocos2d::Sprite *ink);
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    void update(float dt) override;
    
    CREATE_FUNC(StageLayer);
};


#endif /* StageLayer_hpp */
