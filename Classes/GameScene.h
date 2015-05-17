//
//  GameScene.h
//  Brave2048
//
//  Created by apple on 15/5/16.
//
//

#ifndef __Brave2048__GameScene__
#define __Brave2048__GameScene__

#include "cocos2d.h"

class GameScene:public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameScene);
    bool init();    
};

#endif /* defined(__Brave2048__GameScene__) */
