//
//  Helper.cpp
//  SyuraApp
//
//  Created by 林　真史 on 2016/01/24.
//
//

#include "Helper.hpp"
USING_NS_CC;

Helper* Helper::mHelper = NULL;

Helper::Helper()
{
    
}

Helper* Helper::getInstance()
{
    if(mHelper == NULL)
    {
        mHelper = new Helper();
        mHelper->initialize();
    }
    
    return mHelper;
}

// 値の初期化
void Helper::initialize()
{
    
}
