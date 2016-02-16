//
//  GameScene.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/07.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "HudLayer.hpp"
#include "StageLayer.hpp"
#include "Helper.hpp"
#include "WinModal.hpp"
#include "LoseModal.hpp"

USING_NS_CC;
class GameScene : public cocos2d::Layer
{
private:
    GameScene();
    ~GameScene();
   public:
    Size winSize;
    enum class GameState
    {
        READY,
        PLAYING,
        PAUSE,
        SYURABA,
        ENDING,
        LOSE,
        CLEAR,
    };
    
    /* 制限時間用変数　*/
    CC_SYNTHESIZE(float, _second, Second);
    /* 現在のゲーム状態 */
    CC_SYNTHESIZE(GameState, _state, State);
    /* 制限時間用ラベル */
    CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _secondLabel, SecondLabel);
    
    CC_SYNTHESIZE_RETAIN(StageLayer*, _stagelayer, StageLayer);
    void onEnterTransitionDidFinish() override;
    void addReadyLabel();
    void onEnding();
    void onClear();
    void onLose();
    bool judgeGame();
    
    static cocos2d::Scene* createScene();
    void update(float dt)override;
    virtual bool init()override;
    CREATE_FUNC(GameScene);
};

#endif // __GameScene_SCENE_H__


