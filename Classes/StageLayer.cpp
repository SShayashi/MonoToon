//
//  StageLayer.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/11.
//
//

#include "StageLayer.hpp"

USING_NS_CC;

StageLayer::StageLayer():
_player(NULL),
_hudlayer(NULL){
    
}

StageLayer::~StageLayer(){
    CC_SAFE_RELEASE_NULL(_player);
    CC_SAFE_RELEASE_NULL(_hudlayer);
}
bool StageLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    //操作用レイヤの追加
    auto hudlayer = HudLayer::create();
    _hudlayer = hudlayer;
    addChild(_hudlayer);
    
    //プレイヤーの追加
    auto player = Player::create();
    player->setPosition(0,0);
    _player = player;
    addChild(_player);
    
    time = 0;
    this->scheduleUpdate();
    return true;
}

void StageLayer::update(float dt)
{
    time+=dt;
    _hudlayer->updateControl(*_player, dt);
    if(_hudlayer->getbuttonTouchFlag()){
        if (time > 1){
            shotInk(*_player);
            time = 0;
        }
    }else{
    }

}

//インクの発射処理
void StageLayer::shotInk(Character &chara){
    //画像の向きも決めるべき
    //タグから色を決定する

    //画像の作成
    auto ink = Sprite::create(chara.getInk()->getResourceName());
    ink->setPosition(chara.getPosition());
    this->addChild(ink);
    _shotInks.pushBack(ink);
    
    auto remove_draw = CallFuncN::create([this](Node *node){
       //NodeをSpriteにダウンキャスト
        auto sprite = dynamic_cast<Sprite*>(node);
        this->drawInk();
        this->removeShotInk(sprite);
        
    });
    //予め作っているアニメーションを連続で呼びだそうとするとエラーが出たので毎回作成する
 
    auto anime = MoveBy::create(0.5, Vec2(60,0));
    auto sequence = Sequence::create(anime,remove, NULL);
    ink->runAction(sequence);
}

//発射したインクの着地点にインクを塗る処理
void StageLayer::drawInk(){
    
}

//発射したinkを削除
bool StageLayer::removeShotInk(cocos2d::Sprite *shotink){
    if(_shotInks.contains(shotink))
    {
        shotink->removeFromParent();
        _shotInks.eraseObject(shotink);
        return true;
    }
    return false;
}
