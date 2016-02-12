//
//  HomeScene.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/11.
//
//

#include "HomeScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
HomeScene::HomeScene()
{
    
}
HomeScene::~HomeScene(){
}

Scene* HomeScene::createScene()
{
    /* 物理エンジンを有効にしたシーンを作成 */
    auto scene = Scene::create();
    auto layer = HomeScene::create();
    scene->addChild(layer);
    return scene;
}


bool HomeScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("TitleScene.csb");
    rootNode -> setName("NODE");
    addChild(rootNode);




    // 画面をタッチしたときにgame画面へ遷移
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        //点滅する処理を追加
        auto* start_text = dynamic_cast<cocos2d::ui::Text*>(this->getChildByName("NODE")->getChildByName("touch_to_start"));
        auto blink = Blink::create(1,10);
        start_text->runAction(blink);
        this->getEventDispatcher()->removeAllEventListeners();
        this->runAction(Sequence::create(DelayTime::create(1.0),
                                         CallFunc::create([this] {
            auto game = GameScene::createScene();
            //キャスト治すTODO
            auto transition = TransitionCrossFade::create(0.5, (Scene*)game);
            
            Director::getInstance()->replaceScene(transition);
        }), NULL));
        
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void HomeScene::update(float dt){
}
