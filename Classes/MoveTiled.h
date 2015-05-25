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
    int m_row;
    int m_col;
    int m_number;
    void showAt(int r, int c);//在某个位置显示某个块
    void moveTo(int r, int c);//移动到r行，c列
    CREATE_FUNC(MoveTiled);
    bool init();
};

#endif /* defined(__Brave2048__MoveTiled__) */
