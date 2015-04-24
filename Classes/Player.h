//
//  Player.h
//  granny
//
//  Created by DONG on 15/4/23.
//
//

#ifndef __granny__Player__
#define __granny__Player__

#include "Quadtree.h"
#include "cocos2d.h"
USING_NS_CC;

class Player : public MoveObject, public Node
{
public:
    CREATE_FUNC(Player);
    bool init();
    virtual void setPosition(const Vec2 &position);
    void setSelected(bool bSel);
    
private:
    Sprite* _sprite;
};

#endif /* defined(__granny__Player__) */
