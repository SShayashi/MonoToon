//
//  StageLayer.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/11.
//
//

#include "StageLayer.hpp"

USING_NS_CC;

Stagelayer::Stagelayer():
_player(NULL),
_hudlayer(NULL){
    
}

Stagelayer::~Stagelayer(){
    CC_SAFE_RELEASE_NULL(_player);
    CC_SAFE_RELEASE_NULL(_hudlayer);
}
bool Stagelayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto hudlayer = HudLayer::create();
    _hudlayer = hudlayer;
    addChild(_hudlayer);
    
    auto player = Player::create();
    player->setPosition(0,0);
    _player = player;
    addChild(_player);
    
    this->scheduleUpdate();
    return true;
}

void Stagelayer::update(float dt)
{
    _hudlayer->updateControl(*_player, dt);
}