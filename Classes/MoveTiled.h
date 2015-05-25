//
//  MoveTiled.h
//  Brave2048
//
//  Created by apple on 15/5/17.
//
//

#ifndef __Brave2048__MoveTiled__
#define __Brave2048__MoveTiled__

#include "cocos2d.h"

class MoveTiled:public cocos2d::Node
{
public:
    void showAt(int r, int c);//在某个位置显示某个块
    void moveTo(int r, int c);//移动到r行，c列
    CREATE_FUNC(MoveTiled);
    bool init();
    int getNumber(void)const;
    void setNumber(int n);
    void setBkColor(const cocos2d::Color3B& color);
    
private:
    int m_number;
    cocos2d::Label* label;
    cocos2d::LayerColor* bk;
  
};

#endif /* defined(__Brave2048__MoveTiled__) */
