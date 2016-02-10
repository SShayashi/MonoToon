//
//  HudLayer.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/10.
//
//

#ifndef HudLayer_hpp
#define HudLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Player.hpp"
#include "VirtualPad.hpp"
USING_NS_CC;
class HudLayer : public cocos2d::Layer
{
public:
    
    void updateControl(Player& player, float dt);
    
    /* VirutalPadの生成 */
    CC_SYNTHESIZE_RETAIN(VirtualPad *, _virPad, VirtualPad);

    /* タッチイベントリスナー */
    void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event) override;
    void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event) override;
    void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event) override;
    
    
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    void update(float dt)override;

    CREATE_FUNC(HudLayer);
};

#endif /* HudLayer_hpp */
