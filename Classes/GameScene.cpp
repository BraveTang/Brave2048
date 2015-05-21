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
    for (int i=0; i<4; i++) {
        for (int j=0; j<4 ; j++) {
            m_map[i][j] = 0;//空白
        }
    }
    //初识化数字块
    newMoveTiled();
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
                }
                else
                {
                    dir = E_MOVE_DIR::LEFT;
                }
            }
            else
            {
                if (m_y < y) {
                    dir = E_MOVE_DIR::UP;
                }
                else
                {
                    dir = E_MOVE_DIR::DOWN;
                }
            }
            moveAllTiled(dir);//移动可移动的元素块
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);
    return true;
}

void GameScene::moveAllTiled(E_MOVE_DIR dir)
{
    switch (dir) {
        case E_MOVE_DIR::UP:
            if(moveUp())
            {
                //产生新的块
                newMoveTiled();
            }
            break;
        case E_MOVE_DIR::DOWN:
            if(moveDown())
            {
                //产生新的块
                newMoveTiled();
            }
            break;
        case E_MOVE_DIR::LEFT:
            if(moveLeft())
            {
                //产生新的块
                newMoveTiled();
            }
            break;
        case E_MOVE_DIR::RIGHT:
            if(moveRight())
            {
                //产生新的块
                newMoveTiled();
            }
            break;
        default:
            break;
    }
}

void GameScene::newMoveTiled()
{
//    int i = CCRANDOM_0_1()*4;
//    int j = CCRANDOM_0_1()*4;
//    if (m_map[i][j] > 0) {
//        newMoveTiled();
//    }
//    else
//    {
//        auto tiled = MoveTiled::create();
//        //                    tiled->moveTo(i, j);
//        //                    m_allTiled.pushBack(tiled);
//        //                    m_map[i][j] = (int)m_allTiled.getIndex(tiled)+1;
//           colorBack->addChild(tiled);
//    }
    CCLOG("test NEW\n");
    long freeCount = 15 - m_allTiled.size();
    if (freeCount == 0) {
        return;
    }
    int num = rand()%freeCount;
    CCLOG("num = %d\n",num);
    int count=0;
    bool isfind = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (m_map[i][j] <= 0) {
                count++;
                if (count == num) {
                    auto tiled = MoveTiled::create();
                    tiled->moveTo(i, j);
                    m_allTiled.pushBack(tiled);
                    m_map[i][j] = (int)m_allTiled.getIndex(tiled)+1;
                    colorBack->addChild(tiled);
                    isfind = true;
                    CCLOG("New Tiled:%d,%d\n",i,j);
                    break;
                }
            }
        }
        if (isfind == true) {
            break;
        }
    }
    
}
bool GameScene::moveUp()
{
    bool isMove = false;
    for (int col = 0; col < 4; col++) {
        for (int row = 3; row >= 0; row--) {
            for (int t_row = row - 1; t_row >= 0; t_row--) {
                if (m_map[t_row][col] > 0) {
                    if (m_map[row][col] <= 0) {
                        m_allTiled.at(m_map[t_row][col]-1)->moveTo(row, col);
                        m_map[row][col] = m_map[t_row][col];
                        m_map[t_row][col] = 0;
                        CCLOG("move1\n");
                        isMove = true;
                    }
                    else if(m_map[row][col] > 0)
                    {
                        if (m_allTiled.at(m_map[t_row][col]-1)->getNumber() == m_allTiled.at(m_map[row][col]-1)->getNumber()) {
                            m_allTiled.at(m_map[t_row][col]-1)->moveTo(row, col);
                            m_allTiled.at(m_map[t_row][col]-1)->setNumber(m_allTiled.at(m_map[t_row][col]-1)->getNumber() * 2);
                            m_allTiled.at(m_map[t_row][col]-1)->setBackGroud(m_allTiled.at(m_map[t_row][col]-1)->getNumber() * 2);
                            m_allTiled.at(m_map[t_row][col]-1)->removeFromParent();
                            m_allTiled.erase(m_allTiled.begin()+m_map[row][col]-1);
                            
                            //m_map[row][col] = m_map[t_row][col];
                            //m_map[t_row][col] = 0;
                            int index = m_map[t_row][col];
                            for (int r = 0; <#condition#>; <#increment#>) {
                                <#statements#>
                            }
                            CCLOG("move2:%d\n",index);
                            isMove = true;
                        }

                    }
                    break;
                }
            }
        }
    }
    return isMove;
}
bool GameScene::moveDown()
{
    bool isMove = false;
    
    return isMove;
}
bool GameScene::moveLeft()
{
    bool isMove = false;
    return isMove;
}
bool GameScene::moveRight()
{
    bool isMove = false;
    return isMove;
}