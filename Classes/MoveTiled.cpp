//
//  MoveTiled.cpp
//  Brave2048
//
//  Created by apple on 15/5/17.
//
//

#include "MoveTiled.h"

USING_NS_CC;

void MoveTiled::showAt(int r, int c)//在某个位置显示某个块
{

}
void MoveTiled::moveTo(int r, int c)//移动到r行，c列
{
    this->m_row = r;
    this->m_col = c;
    auto winSize = Director::getInstance()->getWinSize();
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
    int layerTiledWidth = (colorBackWidth - 2*5)/4;
    int layerTiledHeight = (colorBackHeight - 2*5)/4;
    
    this->setPosition(layerTiledWidth*c+2*(c+1),layerTiledHeight*r+2*(r+1));
 
}
bool MoveTiled::init()
{
    if (!Node::init()) {
        return false;
    }
    
    //背景层
    auto winSize = Director::getInstance()->getWinSize();
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
    int layerTiledWidth = (colorBackWidth - 2*5)/4;
    int layerTiledHeight = (colorBackHeight - 2*5)/4;
    
    auto bk = LayerColor::create(Color4B(200,200,200,255),layerTiledWidth, layerTiledHeight);
    this->addChild(bk);
    //数字层
    int n = rand()%10;
    this->m_number = n>0?2:4;
    lable = Label::createWithSystemFont(StringUtils::format("%d",this->m_number), "宋体", 80);
    lable->setPosition(Vec2(bk->getContentSize().width/2,bk->getContentSize().height/2));
    lable->setColor(Color3B::BLACK);
    bk->addChild(lable);
    return true;
}

const int MoveTiled::getNumber(void)const
{
    return m_number;
}

void MoveTiled::setNumber(int n)
{
    m_number = n;
    lable->setString(StringUtils::format("%d",this->m_number));
}
void MoveTiled::doubleNumber(void)
{
    m_number *= 2;
    lable->setString(StringUtils::format("%d",this->m_number));
}