//
//  GameScene.cpp
//  Brave2048
//
//  Created by apple on 15/5/16.
//
//

#include "GameScene.h"
#include "MoveTiled.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    //初识化游戏标题
    auto winSize = Director::getInstance()->getWinSize();
    auto gameName = Label::createWithBMFont("futura-48.fnt", "Brave2048");
    //gameName->setAnchorPoint(Vec2(0,0));
    gameName->setScale(0.5);
    gameName->setPosition(Vec2(gameName->getContentSize().width/4,(winSize.height-(gameName->getContentSize().height/4))));
    
    this->addChild(gameName);
//    //分割游戏画面为上下两个区域
//    auto segLine = DrawNode::create();
//    segLine->drawLine(Vec2(0,winSize.height/2), Vec2(winSize.width,winSize.height/2), Color4F(1.0,1.0,1.0,1.0));
//    
//    CCLOG("width:%f\n",winSize.width);
//    CCLOG("height/2:%f\n",winSize.height/2);
//    this->addChild(segLine);
    //初识化游戏网格
    //int colorBackWidth = (winSize.width-2*5)/4;
    int colorBackWidth,colorBackHeight;
    int space = abs(winSize.width-winSize.height/2);
    CCLOG("space:%d\n",space);
    if (winSize.width > winSize.height/2) {
         colorBackWidth = winSize.width-space;
         colorBackHeight = winSize.height/2;
    }
    else
    {
         colorBackWidth = winSize.width;
         colorBackHeight = winSize.height/2-space;
    }

    CCLOG("colorBackWidth:%d\n",colorBackWidth);
    CCLOG("colorBackHeight:%d\n",colorBackHeight);
    colorBack = LayerColor::create(Color4B(170, 170, 170, 255),
                                        colorBackWidth, colorBackHeight);
    colorBack->ignoreAnchorPointForPosition(false);
    colorBack->setAnchorPoint(Vec2(0.5,0.5));
    
    colorBack->setPosition(Vec2(winSize.width/2,winSize.height/4));
    this->addChild(colorBack);
    //添加数字网格槽
    int layerTiledWidth = (colorBackWidth - 2*5)/4;
    int layerTiledHeight = (colorBackHeight - 2*5)/4;
    CCLOG("layerTiledWidth:%d\n",layerTiledWidth);
    CCLOG("layerTiledHeight:%d\n",layerTiledHeight);
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            auto layerTiled = LayerColor::create(Color4B(70,70,70,255), layerTiledWidth, layerTiledHeight);
            layerTiled->setPosition(Vec2(layerTiledWidth*col+2*(col+1),layerTiledHeight*row+2*(row+1)));
            colorBack->addChild(layerTiled);
        }
    }
    //初识化逻辑的网格数组
    for (int i=0; i<GAME_ROWS; i++) {
        for (int j=0; j<GAME_COLS; j++) {
            map[i][j] = -1;//空白
        }
    }
    //初识化数字块
    addNewTiled();
    //addNewTiled();
    //addNewTiled();
    //触摸的处理
    auto event = EventListenerTouchOneByOne::create();
    event->onTouchBegan = [this](Touch* tou,Event* eve){
        m_x = tou->getLocation().x;
        m_y = tou->getLocation().y;
        m_startMove = true;
        return true;
    };
    event->onTouchMoved = [this](Touch* tou,Event* eve){
        int x = tou->getLocation().x;
        int y = tou->getLocation().y;
        if (m_startMove&&(abs(m_x - x) > 10 || abs(m_y - y) > 10)) {
            m_startMove =  false;
            E_MOVE_DIR dir;
            if (abs(m_x - x) > abs(m_y - y)) {
                if (m_x < x) {
                    dir = E_MOVE_DIR::RIGHT;
                    if(doRight())
                    {
                        addNewTiled();
                    }
                }
                else
                {
                    dir = E_MOVE_DIR::LEFT;
                    if(doLeft())
                    {
                        addNewTiled();
                    }
                }
            }
            else
            {
                if (m_y < y) {
                    dir = E_MOVE_DIR::UP;
                    if(doUp())
                    {
                        addNewTiled();
                    }
                }
                else
                {
                    dir = E_MOVE_DIR::DOWN;
                    if(doDown())
                    {
                        addNewTiled();
                    }
                }
            }
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(event, this);
    return true;
}
void GameScene::addNewTiled(void)
{
    int i = CCRANDOM_0_1()*4;
    int j = CCRANDOM_0_1()*4;
    if(map[i][j] >= 0)
    {
        addNewTiled();
    }
    else{
        auto tiled = MoveTiled::create();
        tiled->setNumber(CCRANDOM_0_1()*10 < 1 ? 4 : 2);
        tiled->moveTo(i,j);
        m_allTiled.pushBack(tiled);
        map[i][j] = (int)m_allTiled.getIndex(tiled);
        colorBack->addChild(tiled);
    }
}

bool GameScene::doUp(void)
{
    bool isMove = false;
    for (int col = 0; col < 4; col++) {
        for (int row = 3; row >= 0; row--) {
            for (int row_t = row -1; row_t >= 0; row_t--) {
                if (map[row][col] < 0) {
                    if (map[row_t][col] >= 0) {
                        
                        m_allTiled.at(map[row_t][col])->moveTo(row, col);
                        map[row][col] = map[row_t][col];
                        map[row_t][col] = -1;
                        isMove = true;
                    }
                }
                else
                {
                    if (map[row_t][col] == -1) {
                        continue;
                    }
                    if (m_allTiled.at(map[row][col])->getNumber() != m_allTiled.at(map[row_t][col])->getNumber()) {
                        break;
                    }
                    else
                    {
                        m_allTiled.at(map[row][col])->doubleNumber();
                        m_allTiled.at(map[row_t][col])->removeFromParent();
                        m_allTiled.eraseObject(m_allTiled.at(map[row_t][col]));
                        int index = map[row_t][col];
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                if (map[i][j] > index) {
                                    map[i][j]--;
                                }
                            }
                        }
                        map[row_t][col] = -1;
                        isMove = true;
                    }
                }
            }
        }
    }
    return isMove;
}

bool GameScene::doDown(void)
{
    bool isMove = false;
    for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++) {
            for (int row_t = row + 1; row_t < 4; row_t++) {
                if (map[row][col] < 0) {
                    if (map[row_t][col] >= 0) {
                        
                        m_allTiled.at(map[row_t][col])->moveTo(row, col);
                        map[row][col] = map[row_t][col];
                        map[row_t][col] = -1;
                        isMove = true;
                    }
                }
                else
                {
                    if (map[row_t][col] == -1) {
                        continue;
                    }
                    if(m_allTiled.at(map[row][col])->getNumber() != m_allTiled.at(map[row_t][col])->getNumber())
                    {
                        break;
                    }
                    else
                    {
                        m_allTiled.at(map[row][col])->doubleNumber();
                        m_allTiled.at(map[row_t][col])->removeFromParent();
                        m_allTiled.eraseObject(m_allTiled.at(map[row_t][col]));
                        int index = map[row_t][col];
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                if (map[i][j] > index) {
                                    map[i][j]--;
                                }
                            }
                        }
                        map[row_t][col] = -1;
                        isMove = true;
                    }
                }
            }
        }
    }
    return isMove;
}

bool GameScene::doRight()
{
    bool isMove = false;
    for (int row = 0; row < 4; row++) {
        for (int col = 3; col >= 0; col--) {
            for (int col_t = col -1; col_t >= 0; col_t--) {
                if (map[row][col] < 0) {
                    if (map[row][col_t] >= 0) {
                        
                        m_allTiled.at(map[row][col_t])->moveTo(row, col);
                        map[row][col] = map[row][col_t];
                        map[row][col_t] = -1;
                        isMove = true;
                    }
                }
                else
                {
                    if (map[row][col_t] == -1) {
                        continue;
                    }
                    if (m_allTiled.at(map[row][col])->getNumber() != m_allTiled.at(map[row][col_t])->getNumber()) {
                        break;
                    }
                    else
                    {
                        m_allTiled.at(map[row][col])->doubleNumber();
                        m_allTiled.at(map[row][col_t])->removeFromParent();
                        m_allTiled.eraseObject(m_allTiled.at(map[row][col_t]));
                        int index = map[row][col_t];
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                if (map[i][j] > index) {
                                    map[i][j]--;
                                }
                            }
                        }
                        map[row][col_t] = -1;
                        isMove = true;
                    }
                }
            }
        }
    }
    return isMove;
}

bool GameScene::doLeft()
{
    bool isMove = false;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            for (int col_t = col + 1; col_t < 4; col_t++) {
                if (map[row][col] < 0) {
                    if (map[row][col_t] >= 0) {
                        
                        m_allTiled.at(map[row][col_t])->moveTo(row, col);
                        map[row][col] = map[row][col_t];
                        map[row][col_t] = -1;
                        isMove = true;
                    }
                }
                else
                {
                    if (map[row][col_t] == -1) {
                        continue;
                    }
                    if (m_allTiled.at(map[row][col])->getNumber() != m_allTiled.at(map[row][col_t])->getNumber()) {
                        break;
                    }
                    else
                    {
                        m_allTiled.at(map[row][col])->doubleNumber();
                        m_allTiled.at(map[row][col_t])->removeFromParent();
                        m_allTiled.eraseObject(m_allTiled.at(map[row][col_t]));
                        int index = map[row][col_t];
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                if (map[i][j] > index) {
                                    map[i][j]--;
                                }
                            }
                        }
                        map[row][col_t] = -1;
                        isMove = true;
                    }
                }
            }
        }
    }
    return isMove;
}