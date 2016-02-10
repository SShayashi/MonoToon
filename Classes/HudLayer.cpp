//
//  HudLayer.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/10.
//
//

#include "HudLayer.hpp"

USING_NS_CC;

HudLayer::HudLayer():
_buttonTouchFlag(false){
    
}

HudLayer::~HudLayer(){
    
}
bool HudLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    winSize = Director::getInstance()->getWinSize();

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
    
    auto uButton = ui::Button::create();
    uButton->setTouchEnabled(true);
    uButton->loadTextures("button/button.png", "button/button_touched.png", "");
    uButton->setPosition(Point(winSize.width * 4/5, winSize.height / 2) + Point(0, -100));
    
    //button をおした時の処理
    uButton->addTouchEventListener([this](Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                log("TOUCH_EVENT_BEGAN");
                _buttonTouchFlag = true;
                break;
            case ui::Widget::TouchEventType::MOVED:
                log("TOUCH_EVENT_MOVED");
                _buttonTouchFlag = true;
                break;
            case ui::Widget::TouchEventType::ENDED:
                log("TOUCH_EVENT_ENDED");
                _buttonTouchFlag = false;
                break;
            case ui::Widget::TouchEventType::CANCELED:
                log("TOUCH_EVENT_CANCELED");
                _buttonTouchFlag = false;
                break;
            default:
                break;
        }
    });

    addChild(uButton);

    
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





