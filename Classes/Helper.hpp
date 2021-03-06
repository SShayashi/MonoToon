//
//  Helper.hpp
//  SyuraApp
//
//  Created by 林　真史 on 2016/01/24.
//
//

#ifndef Helper_hpp
#define Helper_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;


class Helper
{
private:
    Helper();
    static Helper* mHelper;
public:
    //ゲーム内で利用する共用体
    
    //キャラの種類
    enum class CHARA{
        PLAYER,
        ENEMY,
        ENEMY_PLAYER,
        COUNT
    };
    
    /** 方向
     *789
     *456
     *123
     */
    enum class ANGLE8{
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT,
        MIDDLE_LEFT,
        MIDDLE_CENTER,
        MIDDLE_RIGHT,
        TOPLEFT,
        TOPCENTERM,
        TOPRIGHT
    };

    
    //インクの種類
    enum class ShotInkType
    {
        PLAYER,
        ENEMY,
        COUNT
    };
    
    //床に塗るインクの種類
    enum class DrawInkType
    {
        GUN,
        ROLLER,
        CHARGER,
        COUNT
    };
    
    //床に塗られたインクの種類
    enum class TiledInkType{
        PLAYER,
        ENEMY,
        NONE,
        COUNT
    };
    
    static Helper* getInstance();
    
    // ゲーム全体で使用したい変数
    int _gameLevel;
    // 値の初期化
    void initialize();
    
    // メソッド
};
#endif /* Helper_hpp */
