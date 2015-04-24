//
//  Player.cpp
//  granny
//
//  Created by DONG on 15/4/23.
//
//

#include "Player.h"

void Player::setPosition(const cocos2d::Vec2 &position)
{
    Node::setPosition(position);
    _pos = position;
    _box.origin = _pos - _size * 0.5f;
}

bool Player::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    _sprite = Sprite::create("rect.png");
    addChild(_sprite);
    
    _size = _sprite->getContentSize();
    _box.size = _size;
    setPosition(Vec2::ZERO);
    return true;
}

void Player::setSelected(bool bSel)
{
    if (bSel)
    {
        _sprite->setColor(Color3B::RED);
    }
    else
    {
        _sprite->setColor(Color3B::WHITE);
    }
}