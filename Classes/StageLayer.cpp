//
//  StageLayer.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/11.
//
//

#include "StageLayer.hpp"
#define SHOT_INTERBAL 0.2
#define ADD_ENEMEY_RATE 120
#define PI 3.141592653589793
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
    //レンダリング用のテクスチャの初期化
    auto renderTexture = RenderTexture::create(winSize.width, winSize.height);
//    renderTexture->setClearColor(cocos2d::Color4F(0,0,1,0.5));
    renderTexture->setPosition(Vec2(winSize.width/2, winSize.height/2));
    _renderTexture = renderTexture;
    addChild(_renderTexture);

    
    //操作用レイヤの追加
    auto hudlayer = HudLayer::create();
    _hudlayer = hudlayer;
    addChild(_hudlayer,10001);
    
    //プレイヤーの追加
    auto player = Player::create();
    player->setPosition(0,0);
    _player = player;
    addChild(_player,10000);
    
    
    //デバッグ用に敵キャラの追加
    auto enemy = Enemy::create();
    enemy->setTag((int)Helper::CHARA::ENEMY);
    enemy->setTexture("character/enemy/picocassette_sozai_41.png");
    enemy->setPosition(Vec2(500,500));
    addChild(enemy);
    _enemys.pushBack(enemy);
    
    time = 0;
    this->scheduleUpdate();
    return true;
}

void StageLayer::update(float dt){
    time+=dt;
    //hudlayerからの入力をキャラに伝える
    _hudlayer->updateControl(*_player, dt);
    if(_hudlayer->getbuttonTouchFlag()){
        if (time > SHOT_INTERBAL){
            shotInk(*_player);
            time = 0;
        }
    }
    //インクの当たり判定
    this->detectHitShotInk();
    this->detectContactDrawedInk();
    
    //敵の動き
    if(rand() % (ADD_ENEMEY_RATE-Helper::getInstance()->_gameLevel*5) == 0){
        this->addEnemy();
    }
    this->moveEnemy();
    this->shotEnemy();
    
    //インクが全く同じ位置に重なっているものは削除していく
}

//インクの発射処理
void StageLayer::shotInk(Character &chara){
    
    //画像の作成
    auto ink = Sprite::create(chara.getInk()->getResourceName());
    ink->setTag(chara.getTag());
    ink->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    ink->setPosition(chara.getPosition());
    
    //ベクトルの差分で角度を取ると、より小さい角度で取得するので、キャラの方向から、どちらに回転させるか決めている
    auto digree = Vec2::angle(chara.getDirectionalVec(), Vec2(1,0)) *180/PI;
//    CCLOG("Digree : %f",digree);
    if(chara.getDirectionalVec().y >= 0 ){
        ink->setRotation(-digree);
    }else{
        ink->setRotation(digree);
    }

    this->addChild(ink);
    _shotInks.pushBack(ink);
    
    //アニメーションの追加
    auto remove_draw = CallFuncN::create([this](Node *node){
       //NodeをSpriteにダウンキャスト
        auto sprite = dynamic_cast<Sprite*>(node);
        this->drawInk(sprite);
        this->removeShotInk(sprite);
        
    });
    
    /*予め作っているアニメーションを連続で呼びだそうとするとエラーが出たので毎回作成する
     *キャラの向きによって射出する方向を変える
     */
    auto shotVec = chara.getDirectionalVec()*chara.getShotDistance();
    auto anime = MoveBy::create(0.4, shotVec);
    auto sequence = Sequence::create(anime,remove_draw, NULL);
    ink->runAction(sequence);
}

//発射したインクの着地点にインクを塗る処理
void StageLayer::drawInk(cocos2d::Sprite *shotink){

    //タグから判別
    //床に同じ色のスプライトを貼る
//    オフスクリーンレンダリングを行うと画面が真っ黒になるバグがあるのでしない
    _renderTexture->begin();
 
    //auto polygonでやるにはphisicsbodyを使う必要がある。
    //auto pinfo = AutoPolygon::generatePolygon("ink/ink_brack.png");
    Sprite* tiledink;
    if(shotink->getTag() == (int)Helper::CHARA::PLAYER)
        tiledink = Sprite::create("ink/ink_brack.png");
    else if(shotink->getTag() == (int)Helper::CHARA::ENEMY)
        tiledink = Sprite::create("ink/ink_white.png");
    auto pos = shotink->getPosition();
    this->removeSamePositionDrawedInk(&pos);
    tiledink->setPosition(shotink->getPosition());
    
    _drawedInks.pushBack(tiledink);
    tiledink->visit();
    _renderTexture->end();
    tiledink->retain();
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

/** 発射中のinkの当たり判定
 *
 */
void StageLayer::detectHitShotInk(){
    for(auto& shotink : _shotInks){
        //インクのタグから当たり判定を取る画像を取得して、当てるものだけ
        auto tag = shotink->getTag();
        auto boundingbox = shotink->getBoundingBox();
        auto childs = this->getChildren();
        
        for(auto& node : childs){
            //nodeをcharaにダウンキャストして、chara以外を弾く
            auto chara = dynamic_cast<Character*>(node);
            if(chara  && tag != node->getTag()){
                auto chararect = chara->getBoundingBox();
                bool isHit = chararect.intersectsRect(boundingbox);
                if(isHit)
                    this->hitShotInk(shotink , node);
            }
        }
    }
}

/** 床に塗られたinkの当たり判定
 *
 */
void StageLayer::detectContactDrawedInk(){
    for(auto& drawedink :_drawedInks){
        auto tag = drawedink->getTag();
        auto boundingbox = drawedink->getBoundingBox();
        auto childs = this->getChildren();
        
        for(auto& node: childs){
            //nodeをcharaにダウンキャストして、chara以外を弾く
            auto chara = dynamic_cast<Character*>(node);
            if(chara  && tag != node->getTag()){
                auto chararect = chara->getBoundingBox();
                bool isHit = chararect.intersectsRect(boundingbox);
                if(isHit)
                    this->contactDrawedInk(drawedink , node);
            }
        }
    }
}

/** インクがあたった時の処理
 * @param ink :当てたink
 * @param node :inkにあたったchara
 */
void StageLayer::hitShotInk(cocos2d::Sprite *ink,Node *node){
    //
    this->removeShotInk(ink);
}

void StageLayer::contactDrawedInk(cocos2d::Sprite *drawedink, cocos2d::Node *node){
    CCLOG("ON DRAWED INK");
}

void StageLayer::addEnemy(){
    auto enemy = Enemy::create();
    auto pos = rand() % (int)winSize.height;
    
    //とりあえず画面の右端に敵を追加していく
    enemy->setPosition(Vec2(winSize.width,pos));
    addChild(enemy);
    _enemys.pushBack(enemy);
}

//敵を動かす
void StageLayer::moveEnemy(){
    for(auto &enemy: _enemys){
        
        auto e_pos = enemy->getPosition();
        auto p_pos = _player->getPosition();
        auto delt = p_pos - e_pos;
        delt.normalize();
        enemy->doMove(delt * enemy->getSpeed());
        enemy->setDirectionalVec(delt);
        
    }
}

void StageLayer::shotEnemy(){
    for(auto &enemy: _enemys){
        auto shotrate = rand() % (int)enemy->getShotRate();
        if(shotrate == 0){
            this->shotInk(*enemy);
        }
    }
}

//位置が全く同じインクは削除
void StageLayer::removeSamePositionDrawedInk(cocos2d::Vec2 *position){
    for(auto &drawedink: _drawedInks){
        if(drawedink->getPosition() == *position){
            _drawedInks.eraseObject(drawedink);
            drawedink->removeFromParent();
        }
    }
}