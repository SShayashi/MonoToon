//
//  HudLayer.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/10.
//
//

#include "HudLayer.hpp"

USING_NS_CC;

Scene* HudLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = HudLayer::create();
    scene->addChild(layer);
    return scene;
}


bool HudLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    /* マルチタップリスナーの設置 */
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->setEnabled(true);
    listener->onTouchesBegan = CC_CALLBACK_2(HudLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(HudLayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(HudLayer::onTouchesEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto virPad = VirtualPad::create();
    _virPad = virPad;
    addChild(_virPad);
    
    this->scheduleUpdate();
    
    return true;
}

/**
 *タッチ開始
 *@param touches
 *@param event
 */
void HudLayer::onTouchesBegan(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
        /* Padの画像範囲 */
        auto padBackRect = _virPad->getPadBack()->getBoundingBox();
        
        /* VirtualPadは、最初は画像の中をタッチしないと反応しない*/
        if(padBackRect.containsPoint(location)){
            _virPad->startPad((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
            _virPad->update((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
        }

        
        iterator++;
    }
    return;
}

/**
 *タッチ移動
 *@param touches
 *@param event
 */
void HudLayer::onTouchesMoved(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
        /*バーチャルパッド移動中*/
        _virPad->update((int)touch->getLocation().x,(int)touch->getLocation().y,touch->getID());
        
        iterator++;
    }
    return;
}

/**
 *タッチ終了
 *@param touches
 *@param event
 */
void HudLayer::onTouchesEnded(const std::vector<Touch *> &touches, cocos2d::Event *unused_event){
    std::vector<cocos2d::Touch*>::const_iterator iterator = touches.begin();
    while (iterator != touches.end()) {
        Touch* touch = (Touch*)(*iterator);
        auto location = touch->getLocation();
        
        /* バーチャルパッドを離す */
        _virPad->endPad(touch->getID());
        iterator++;
    }
    return;
}

void HudLayer::updateControl(Player& player ,float dt){
    Vec2 velocity = _virPad->getMovent();
    velocity = _virPad->getMovent() * player.getSpeed();
    player.doMove(velocity);

}





