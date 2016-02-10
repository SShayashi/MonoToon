//
//  StageLayer.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/11.
//
//

#include "StageLayer.hpp"

USING_NS_CC;

bool Stagelayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    this->scheduleUpdate();
    return true;
}

void Stagelayer::update(float dt)
{
    
}