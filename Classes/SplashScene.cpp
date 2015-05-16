//
//  SplashScene.cpp
//  Brave2048
//
//  Created by apple on 15/5/16.
//
//

#include "SplashScene.h"
#include "GameDefine.h"
USING_NS_CC;

Scene* SplashScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
    //显示游戏名称
    auto winSize = Director::getInstance()->getWinSize();
    auto labelGame = Label::createWithBMFont("futura-48.fnt", "Brave2048");
    labelGame->setPosition(Point(winSize.width/2,winSize.height/2));
    labelGame->setScale(2.0f);
    this->addChild(labelGame);
    //显示作者信息
    auto labelGameAuthor = Label::createWithBMFont("futura-48.fnt","BraveTang");
    labelGameAuthor->setPosition(Point(winSize.width/2,winSize.height/4));
    this->addChild(labelGameAuthor);
    //计划任务实现3秒钟后自动跳转到游戏场景
    this->scheduleOnce(schedule_selector(<#_SELECTOR#>), 3.0f);
    return true;
}

