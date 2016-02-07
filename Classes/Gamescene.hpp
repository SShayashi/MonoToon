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
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Gamescene);
};

#endif // __Gamescene_SCENE_H__


