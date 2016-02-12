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

/* 制限時間 */
const float TIME_LIMIT_SECOND = 20;
USING_NS_CC;
using namespace cocostudio::timeline;
GameScene::GameScene():
_state(GameState::READY),
_secondLabel(NULL),
_second(TIME_LIMIT_SECOND)
{
    
}
GameScene::~GameScene(){
    CC_SAFE_RELEASE_NULL(_secondLabel);
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
    winSize = Director::getInstance()->getWinSize();
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
    
    auto stagelayer = StageLayer::create();
    _stagelayer = stagelayer;
    addChild(_stagelayer);
    
    int second = static_cast<int>(_second);
    _secondLabel = Label::createWithSystemFont(StringUtils::toString(second), "../fonts/misaki.ttf", 64);
    _secondLabel->setPosition(Vec2(winSize.width /2.0 , winSize.height -70));
    _secondLabel->setColor(Color3B::GRAY);
    addChild(_secondLabel);
    
    this->scheduleUpdate();
    return true;
}

void GameScene::onEnterTransitionDidFinish()
{
    _stagelayer->unscheduleUpdate();
    // シーン遷移が完了したとき
    Layer::onEnterTransitionDidFinish();
    this->addReadyLabel();
    
}
void GameScene::addReadyLabel()
{
    //プレイ状態をreadyに
    _state = GameState::READY;
    auto center = Vec2(winSize.width / 2.0, winSize.height / 2.0);
    
    // Readyの文字を定義する
    auto ready = Sprite::create("ready.png");
    ready->setScale(0); // 最初に大きさを0にしておく
    ready->setPosition(center);
    this->addChild(ready);
    
    // STARTの文字を定義する
    auto start = Sprite::create("start.png");
    start->runAction(Sequence::create(Spawn::create(EaseIn::create(ScaleTo::create(0.5, 5.0), 0.5),
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
        this->_stagelayer->scheduleUpdate();
        // BGMを鳴らす
    }),
                                      RemoveSelf::create(), // 自分を削除する
                                      NULL));
}


void GameScene::update(float dt){
    /* 残り時間を減らす */
    if(_state == GameState::PLAYING){
        _second -= dt;
    }else if (_state == GameState::READY){
        _second = TIME_LIMIT_SECOND;
    }else if(_state == GameState::ENDING){
        _second = 0;
        if(this->judgeGame()){
            this->onClear();
        }else{
            this->onLose();
        }
            
    }
    
    /* 表示の更新 */
    int second = static_cast<int>(_second);
    _secondLabel->setString(StringUtils::toString(second));
    
    if(_second <= 0 ){

        _state = GameState::ENDING;
    }

}


bool GameScene::judgeGame(){

    int players=0;
    int enemys =0;
    auto childs = _stagelayer->getChildren();
    for(auto node : childs){
        if(node->getTag() == (int)Helper::CHARA::PLAYER){
            players++;
        }else if(node->getTag() == (int)Helper::CHARA::ENEMY){
            enemys++;
        }else{
            
        }
    }
    
    if(players >= enemys)
        return true;
    else
        return false;
    
    return false;
}

void GameScene::onClear(){
    Helper::getInstance()->_gameLevel++;
}
void GameScene::onLose(){
    Helper::getInstance()->_gameLevel = 1;
}
