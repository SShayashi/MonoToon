//
//  GameScene.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/07.
//
//

#include "GameScene.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
GameScene::GameScene():
_state(GameState::READY),
 _secondLabel(NULL)
{
    
}
GameScene::~GameScene(){
}

Scene* GameScene::createScene()
{
    /* 物理エンジンを有効にしたシーンを作成 */
    auto scene = Scene::createWithPhysics();
    auto world = scene->getPhysicsWorld();
    world->setGravity(Vec2::ZERO);
    /* デバッグビルドのとき */
    /* 物理空間にデバッグ用の表示を追加する */
    world -> setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}


bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
    
    auto stagelayer = StageLayer::create();
    _stagelayer = stagelayer;
    addChild(_stagelayer);
    
    this->scheduleUpdate();
    
    return true;
}

void GameScene::onEnterTransitionDidFinish()
{
    _stagelayer->unscheduleUpdate();
    // シーン遷移が完了したとき
    Layer::onEnterTransitionDidFinish();
    
    // 2秒後にラムダ式を実行
    this->runAction(Sequence::create(DelayTime::create(1),CallFunc::create([this](){
        _stagelayer->scheduleUpdate();
    }), NULL));
    
    addReadyLabel();


    
}
void GameScene::addReadyLabel()
{
    auto winSize = Director::getInstance()->getWinSize();
    auto center = Vec2(winSize.width / 2.0, winSize.height / 2.0);
    
    // Readyの文字を定義する
    auto ready = Sprite::create("ready.png");
    ready->setScale(0); // 最初に大きさを0にしておく
    ready->setPosition(center);
    this->addChild(ready);
    
    // STARTの文字を定義する
    auto start = Sprite::create("start.png");
    start->runAction(Sequence::create(CCSpawn::create(EaseIn::create(ScaleTo::create(0.5, 5.0), 0.5),
                                                      FadeOut::create(0.5),
                                                      NULL), // 0.5秒かけて拡大とフェードアウトを同時に行う
                                      RemoveSelf::create(), // 自分を削除する
                                      NULL));
    start->setPosition(center);
    
    // READYにアニメーションを追加する
    ready->runAction(Sequence::create(ScaleTo::create(0.25, 1), // 0.25秒かけて等倍に拡大される
                                      DelayTime::create(1.0), // 1.0秒待つ
                                      CallFunc::create([this, start] { // ラムダの中でthisとstart変数を使っているのでキャプチャに加える
        this->addChild(start); // 「スタート」のラベルを追加する（この時点でスタートのアニメーションが始まる）
        _state = GameState::PLAYING; // ゲーム状態をPLAYINGに切り替える
        // BGMを鳴らす
    }),
                                      RemoveSelf::create(), // 自分を削除する
                                      NULL));
}


void GameScene::update(float dt){
}
