//
//  HomeScene.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/11.
//
//

#ifndef HomeScene_hpp
#define HomeScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameScene.hpp"

USING_NS_CC;
class HomeScene : public cocos2d::Layer
{
private:
    HomeScene();
    ~HomeScene();
public:
    static cocos2d::Scene* createScene();
    void update(float dt)override;
    virtual bool init()override;
    CREATE_FUNC(HomeScene);
};



#endif /* HomeScene_hpp */
