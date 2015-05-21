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
#include "GameDefine.h"
#include "MoveTiled.h"
class GameScene:public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameScene);
    bool init();
    void createMap();
    void createNewMoveTiled();
    
private:
    E_MOVE_DIR m_dir; //移动方向
    MoveTiled* m_map[GAME_ROWS][GAME_ROWS];
    cocos2d::LayerColor* colorBack;
    bool m_startMove;
    int m_x;
    int m_y;
};

#endif /* defined(__Brave2048__GameScene__) */
