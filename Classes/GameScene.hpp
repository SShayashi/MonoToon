//
//  GameScene.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/07.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "HudLayer.hpp"
#include "StageLayer.hpp"

USING_NS_CC;
class GameScene : public cocos2d::Layer
{
private:
    GameScene();
    ~GameScene();
    CC_SYNTHESIZE_RETAIN(StageLayer*, _stagelayer, StageLayer);
public:
    

    
    static cocos2d::Scene* createScene();
    void update(float dt)override;
    virtual bool init()override;
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__


