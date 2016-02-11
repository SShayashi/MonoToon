//
//  StageLayer.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/11.
//
//

#include "StageLayer.hpp"
#define SHOT_INTERBAL 0.2
USING_NS_CC;

StageLayer::StageLayer():
_player(NULL),
_hudlayer(NULL),
_renderTexture(NULL)
{
    
}

StageLayer::~StageLayer(){
    CC_SAFE_RELEASE_NULL(_player);
    CC_SAFE_RELEASE_NULL(_hudlayer);
    CC_SAFE_RELEASE_NULL(_renderTexture);
}
bool StageLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    winSize = Director::getInstance()->getVisibleSize();
    
//    //レンダリング用のテクスチャの初期化
//    auto renderTexture = RenderTexture::create(winSize.width, winSize.height);
//    renderTexture->setClearColor(cocos2d::Color4F(0.5,0.5,1,0.5));
//    renderTexture->setPosition(Vec2(winSize.width/2, winSize.height/2));
//    _renderTexture = renderTexture;
//    addChild(_renderTexture);

    
    //操作用レイヤの追加
    auto hudlayer = HudLayer::create();
    _hudlayer = hudlayer;
    addChild(_hudlayer,10001);
    
    //プレイヤーの追加
    auto player = Player::create();
    player->setPosition(0,0);
    _player = player;
    addChild(_player,10000);
    
    time = 0;
    this->scheduleUpdate();
    return true;
}

void StageLayer::update(float dt)
{
    time+=dt;
    _hudlayer->updateControl(*_player, dt);
    if(_hudlayer->getbuttonTouchFlag()){
        if (time > SHOT_INTERBAL){
            shotInk(*_player);
            time = 0;
        }
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
        this->drawInk(sprite);
        this->removeShotInk(sprite);
        
    });
    
    //予め作っているアニメーションを連続で呼びだそうとするとエラーが出たので毎回作成する
    //キャラの向きによって射出する方向を変える
    auto shotVec = chara.getDirectionalVec()*60;
    auto anime = MoveBy::create(0.4, shotVec);
    auto sequence = Sequence::create(anime,remove_draw, NULL);
    ink->runAction(sequence);
}

//発射したインクの着地点にインクを塗る処理
void StageLayer::drawInk(cocos2d::Sprite *shotink){
    shotink->getTag();
    //タグから判別
    //床に同じ色のスプライトを貼る
//    オフスクリーンレンダリングを行うと画面が真っ黒になるバグがあるのでしない
//    _renderTexture->begin();
    auto tiledink = Sprite::create("ink/ink_brack.png");
    tiledink->setPosition(shotink->getPosition());
    addChild(tiledink);
//    tiledink->visit();
//    tiledink->retain();
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
