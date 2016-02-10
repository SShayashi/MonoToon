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
GameScene::GameScene()
{
    
}
GameScene::~GameScene(){
}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
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
    
    auto stagelayer = Stagelayer::create();
    _stagelayer = stagelayer;
    addChild(_stagelayer);
    
    this->scheduleUpdate();
    
    return true;
}

void GameScene::update(float dt){
}
