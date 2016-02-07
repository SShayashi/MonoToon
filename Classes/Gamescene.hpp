//
//  Gamescene.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/07.
//
//

#ifndef Gamescene_hpp
#define Gamescene_hpp

#include <stdio.h>
#include "cocos2d.h"

class Gamescene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Gamescene);
};

#endif // __Gamescene_SCENE_H__


