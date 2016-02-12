//
//  Enemy.cpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/12.
//
//

#include "Enemy.hpp"
#define Enemy_SPEED_DEFAULT 0.5
#define ENEMY_SHOT_RATE 120
Enemy::Enemy()
{
    
}

Enemy::~Enemy(){
    
}



bool Enemy::init()
{
    if (!Sprite::initWithFile("character/enemy/picocassette_sozai_41.png")) {
        return false;
    }
    
    /* アニメーションの作成 */
    //    Vector<SpriteFrame *> frames;
    /* アニメ用のフレームを読み込む */
    //    fileName[128] = {0};
    //    for(int i = 1 ; i < FRAME_COUNT ; i++ ){
    //        sprintf(fileName, "character/futsuo_00%d.png", i);
    //        auto rect  = this->getTextureRect();
    //        auto frame = SpriteFrame::create(fileName,rect);
    //        _frames.pushBack(frame);
    //    }
    //    this->setAnimation();
    
    auto body = PhysicsBody::createCircle(this->getContentSize().width / 2.0);
    // 剛体の回転を無効にする
    body->setRotationEnable(false);
    //    // カテゴリをPLAYERにセットする
    //    body->setCategoryBitmask(static_cast<int>(Stage::TileType::PLAYER));
    // 全ての剛体と衝突する
    body->setCollisionBitmask(INT_MAX);
    // 全ての剛体の接触判定を行う
    body->setContactTestBitmask(INT_MAX);
    this->setPhysicsBody(body);
    
    setTag((int)Helper::CHARA::ENEMY);
    _shotRate = ENEMY_SHOT_RATE;
    setSpeed(Enemy_SPEED_DEFAULT);
    setShotDistance(60);
    //    setDirectionalVec(Vec2(0,-1));
    
    auto ink = Sprite::create("ink/jet.png");
    setInk(ink);
    
    auto move = MoveBy::create(2, Vec2(40, 0 ));
    auto sequence = Sequence::create(move, NULL);
    setShotMovement(sequence);
    
    this->scheduleUpdate();
    
    return true;
}
//void Enemy::setAnimation(){
//    /* スピードが変わったらアニメーションを入れる */
//    if(_speed != _oldSpeed){
//
//        if(_speed ==0){
//            this->stopAllActions();
//            /* 止まっているたびに元の画像読み出しているので遅い　TODO */
//            this->setTexture("character/futsuo_000.png");
//        }
//        if(_speed > 0 ){
//            auto animation = Animation::createWithSpriteFrames(_frames, 0.3f/getSpeed());
//            animation->setRestoreOriginalFrame(true);
//            this->runAction(RepeatForever::create(Animate::create(animation)));
//        }
//
//        this->setOldSpeed(_speed);
//    }
//}

void Enemy::update(float dt)
{
    //    CCLOG("Enemy Speed %d",this->getSpeed());
    //    this->setAnimation();
    
}