//
//  SplashScene.h
//  Brave2048
//
//  Created by apple on 15/5/16.
//
//

#ifndef __Brave2048__SplashScene__
#define __Brave2048__SplashScene__

#include "cocos2d.h"
class SplashScene:public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(SplashScene);
    bool init();
    void jumpToGame();
};
#endif /* defined(__Brave2048__SplashScene__) */
