//
//  WinModal.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/12.
//
//

#include "WinModal.hpp"
#include "Helper.hpp"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
//#include "ui/CocosGUI.h"

USING_NS_CC;



bool WinModal::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto Node = CSLoader::createNode("WinModal.csb");
    Node -> setName("NODE");
    this -> addChild(Node);
    
    /* コミックリストボタンを押した時の処理 */
    auto* retryBotton = dynamic_cast<cocos2d::ui::Button*>(this->getChildByName("NODE")->getChildByName("retry_button"));
    retryBotton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        
        //touch
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("リトライボタンが押されました");
            // 遷移先の画面のインスタンス
            Scene *pScene = GameScene::createScene();
            TransitionFade* transition = TransitionFade::create(1.0f, pScene);
            Director::getInstance()->replaceScene(transition);
            
            //好きな処理
//            this->menuCloseCallback(pSender);
        }
    });
    
    // モーダル処理
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](Touch *oneTouch,Event*event)->bool{
        return true;
    };
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

// menuCloseCallback WinModalオブジェクトの削除 sender
void WinModal::menuCloseCallback(Ref* pSender)
{
    // WinModalオブジェクトの削除
    this->removeFromParentAndCleanup(true);
}
