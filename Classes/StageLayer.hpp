//
//  StageLayer.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/11.
//
//

#ifndef StageLayer_hpp
#define StageLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Player.hpp"
#include "HudLayer.hpp"
#include "Character.hpp"
#include "Enemy.hpp"

USING_NS_CC;
class StageLayer : public cocos2d::Layer
{
private:
    float time;
    Size winSize;
private:
    StageLayer();
    virtual ~StageLayer();
    CC_SYNTHESIZE_RETAIN(Player*, _player, Player);
    CC_SYNTHESIZE_RETAIN(HudLayer*, _hudlayer, HudLayer);
    CC_SYNTHESIZE_RETAIN(cocos2d::RenderTexture*, _renderTexture, RenderTexture);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _shotInks, ShotInks);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _drawedInks, DrawedInks);
    CC_SYNTHESIZE(cocos2d::Vector<Enemy *>, _enemys, Enemys);

public:
    
    //発射されたインクに関する関数
    void shotInk(Character& chara);
    void detectHitShotInk();
    void hitShotInk(Sprite *ink, Node *node);
    bool removeShotInk(cocos2d::Sprite *ink);
    
    //床に塗られたインクに関する関数
    void drawInk(cocos2d::Sprite *shotink);
    void detectContactDrawedInk();
    void contactDrawedInk(Sprite *drawedink,Node *node);
    void removeSamePositionDrawedInk(Vec2* position);
    
    //敵の追加処理
    void addEnemy();
    void moveEnemy();
    void shotEnemy();
    
    virtual bool init() override;
    void update(float dt) override;
    
    CREATE_FUNC(StageLayer);
    
};


#endif /* StageLayer_hpp */
