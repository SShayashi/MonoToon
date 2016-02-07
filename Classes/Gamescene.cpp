//
//  Gamescene.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/07.
//
//

#include "Gamescene.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* Gamescene::createScene()
{
    auto scene = Scene::create();
    auto layer = Gamescene::create();
    scene->addChild(layer);
    return scene;
}


bool Gamescene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);

    return true;
}
