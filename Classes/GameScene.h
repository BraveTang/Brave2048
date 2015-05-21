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
    void moveAllTiled(E_MOVE_DIR dir);  //移动所有块
    void newMoveTiled();//产生一个新块
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();
private:
    E_MOVE_DIR m_dir; //移动方向
    int m_map[GAME_ROWS][GAME_ROWS];
    cocos2d::Vector<MoveTiled*> m_allTiled;//保存所有块
    cocos2d::LayerColor* colorBack;
    bool m_startMove;
    int m_x;
    int m_y;
};

#endif /* defined(__Brave2048__GameScene__) */
