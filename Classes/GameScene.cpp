//
//  GameScene.cpp
//  Brave2048
//
//  Created by apple on 15/5/16.
//
//

#include "GameScene.h"
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
    createGameName(winSize,"Brave2048");
    //分割游戏画面为上下两个区域

    colorBack = createGameBack(winSize);
    //初始化4*4的移动块
    this->createNewMoveTiled();
   // this->createNewMoveTiled();
    //触摸的处理
    //设置触摸事件监听
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
//    auto touchListener = EventListenerTouchOneByOne::create();
//    touchListener->onTouchBegan = [this](Touch* tou,Event* eve){
//        m_x = tou->getLocation().x;
//        m_y = tou->getLocation().y;
//        m_startMove = true;
//        return true;
//    };
//    touchListener->onTouchMoved = [this](Touch* tou,Event* eve){
//        int x = tou->getLocation().x;
//        int y = tou->getLocation().y;
//        if (m_startMove&&(abs(m_x - x) > 10 || abs(m_y - y) > 10)) {
//            m_startMove =  false;
//            E_MOVE_DIR dir;
//            if (abs(m_x - x) > abs(m_y - y)) {
//                if (m_x < x) {
//                    dir = E_MOVE_DIR::RIGHT;
//                    if (doRight()) {
//                        createNewMoveTiled();
//                    }
//                }
//                else
//                {
//                    dir = E_MOVE_DIR::LEFT;
//                }
//            }
//            else
//            {
//                if (m_y < y) {
//                    dir = E_MOVE_DIR::UP;
//                    
//                    if (this->doUp()) {
//                        createNewMoveTiled();
//                    }
//                }
//                else
//                {
//                    dir = E_MOVE_DIR::DOWN;
//                }
//            }
//        }
//    };
 //   _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

bool GameScene::onTouchBegan(Touch* tou,Event* eve)
{
    m_x = tou->getLocation().x;
    m_y = tou->getLocation().y;
    m_startMove = true;
    return true;
}

void GameScene::onTouchMoved(Touch* tou,Event* eve)
{
    int x = tou->getLocation().x;
    int y = tou->getLocation().y;
    if (m_startMove&&(abs(m_x - x) > 10 || abs(m_y - y) > 10)) {
        m_startMove =  false;
        E_MOVE_DIR dir;
        if (abs(m_x - x) > abs(m_y - y)) {
            if (m_x < x) {
                dir = E_MOVE_DIR::RIGHT;
                if (doRight()) {
                    createNewMoveTiled();
                }
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
                
                if (this->doUp()) {
                    createNewMoveTiled();
                }
            }
            else
            {
                dir = E_MOVE_DIR::DOWN;
            }
        }
    }
}

LayerColor* GameScene::createGameBack(const Size& winSize)
{
    int colorBackWidth,colorBackHeight;
    int space = abs(winSize.width-winSize.height/2);
    //CCLOG("space:%d\n",space);
    if (winSize.width > winSize.height/2) {
        colorBackWidth = winSize.width-space;
        colorBackHeight = winSize.height/2;
    }
    else
    {
        colorBackWidth = winSize.width;
        colorBackHeight = winSize.height/2-space;
    }
    
    //CCLOG("colorBackWidth:%d\n",colorBackWidth);
    //CCLOG("colorBackHeight:%d\n",colorBackHeight);
    auto colorBack = LayerColor::create(Color4B(170, 170, 170, 255),
                                   colorBackWidth, colorBackHeight);
    colorBack->ignoreAnchorPointForPosition(false);
    colorBack->setAnchorPoint(Vec2(0.5,0.5));
    
    colorBack->setPosition(Vec2(winSize.width/2,winSize.height/4));
    this->addChild(colorBack);
    
    //添加数字网格槽
    int layerTiledWidth = (colorBackWidth - 2*5)/4;
    int layerTiledHeight = (colorBackHeight - 2*5)/4;
    //CCLOG("layerTiledWidth:%d\n",layerTiledWidth);
    //CCLOG("layerTiledHeight:%d\n",layerTiledHeight);
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            auto layerTiled = LayerColor::create(Color4B(70,70,70,255), layerTiledWidth, layerTiledHeight);
            layerTiled->setPosition(Vec2(layerTiledWidth*col+2*(col+1),layerTiledHeight*row+2*(row+1)));
            colorBack->addChild(layerTiled);
        }
    }
    return colorBack;
}
void GameScene::createNewMoveTiled()
{
    
}
void GameScene::createGameName(const cocos2d::Size& winSize,const std::string& str)
{
    auto gameName = Label::createWithBMFont("futura-48.fnt", str);
    gameName->setScale(0.5);
    gameName->setPosition(Vec2(gameName->getContentSize().width/4,
                               (winSize.height-(gameName->getContentSize().height/4))));
    
    this->addChild(gameName);
}

bool GameScene::doRight()
{
    
    return false;
}

bool GameScene::doUp()
{
      bool isMove = false;
//    for (int col = 0; col < 4; col++) {
//        for (int row = 3; row >= 0; row--) {
//            for (int row_t = row - 1; row_t >= 0; row_t--) {
//                if (map[row_t][col]->getNumber() > 0) {
//                    if (map[row][col]->getNumber() <= 0) {
//                        int temp = map[row_t][col]->getNumber();
//                        map[row][col]->setNumber(temp);
//                        map[row_t][col]->setNumber(0);
//                        colorBack->removeChild(map[row_t][col]);
//                        colorBack->addChild(map[row][col]);
//                        map[row][col]->moveTo(row, col);
//                        isMove = true;
//                        break;
//                    }
//                }
//            }
//        }
//    }
    return isMove;
}