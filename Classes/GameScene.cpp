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
    auto gameName = Label::createWithBMFont("futura-48.fnt", "Brave2048");
    //gameName->setAnchorPoint(Vec2(0,0));
    gameName->setScale(0.5);
    gameName->setPosition(Vec2(gameName->getContentSize().width/4,(winSize.height-(gameName->getContentSize().height/4))));
    
    this->addChild(gameName);
    //分割游戏画面为上下两个区域
    auto segLine = DrawNode::create();
    segLine->drawLine(Vec2(0,winSize.height/2), Vec2(winSize.width,winSize.height/2), Color4F(1.0,1.0,1.0,1.0));
    
    CCLOG("width:%f\n",winSize.width);
    CCLOG("height:%f\n",winSize.height);
    this->addChild(segLine);
    //初识化游戏网格
    //int colorBackWidth = (winSize.width-2*5)/4;
    int colorBackWidth = winSize.width-20;
    int colorBackHeight = winSize.height/2-20;

    CCLOG("colorBackWidth:%d\n",colorBackWidth);
    auto colorBack = LayerColor::create(Color4B(170, 170, 170, 255),
                                        colorBackWidth, colorBackHeight);
    colorBack->setPosition(Vec2(10,10));
    this->addChild(colorBack);
    
    
    return true;
}