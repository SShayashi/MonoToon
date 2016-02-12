//
//  LoseModal.hpp
//  MonoToon
//
//  Created by 林　真史 on 2016/02/12.
//
//

#ifndef LoseModal_hpp
#define LoseModal_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/cocosGUI.h"
#include "GameScene.hpp"
class LoseModal : public cocos2d::Layer
{
public:
    
    virtual bool init();
    
    
    
    void menuCloseCallback(Ref* pSender);
    
    void pushMenu01(Ref *pSender);
    
    // create()を使えるようにしている。
    CREATE_FUNC(LoseModal);
};



#endif /* LoseModal_hpp */
