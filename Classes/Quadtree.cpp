//
//  Quadtree.cpp
//  quadtree
//
//  Created by DONG on 15/4/24.
//
//

#include "Quadtree.h"


MoveObject::MoveObject()
{
    _pos = Vec2::ZERO;
    _size = Size::ZERO;
    _box = Rect::ZERO;
    updateBox();
    _userData = nullptr;
}

MoveObject::MoveObject(const Vec2& pos, const Size& size)
{
    _pos = pos;
    _size = size;
    updateBox();
    _userData = nullptr;
}

MoveObject::MoveObject(const Vec2& pos, const Size& size, void* userData)
{
    _pos = pos;
    _size = size;
    updateBox();
    _userData = userData;
}

void MoveObject::updateBox()
{
    _box.origin = Vec2(_pos.x - _size.width * 0.5f, _pos.y - _size.height * 0.5f);
    _box.size = _size;
}

const Vec2& MoveObject::getPos() const
{
    return _pos;
}

void MoveObject::setPos(const cocos2d::Vec2 &pos)
{
    _pos = pos;
    updateBox();
}

const Size& MoveObject::getSize() const
{
    return _size;
}

void MoveObject::setSize(const cocos2d::Size &size)
{
    _size = size;
    updateBox();
}

const Rect& MoveObject::getBox() const
{
    return _box;
}

bool MoveObject::intersect(const cocos2d::Rect &box)
{
    return _box.intersectsRect(box);
}

#pragma Quadtree

Quadtree::Quadtree()
{
    _box = Rect::ZERO;
    init();
}

Quadtree::Quadtree(int depth, const Rect& box)
{
    _depth = depth;
    _box = box;
    init();
}

void Quadtree::init()
{
    for (int i=0; i<4; ++i)
    {
        _node[i] = nullptr;
    }
    _halfSize = _box.size * 0.5f;
    _center = Vec2(_box.getMinX() + _box.getMaxX(), _box.getMinY() + _box.getMaxY()) * 0.5f;
    _maxDepth = 5;
    _maxObjects = 6;
}

int Quadtree::getIndex(const cocos2d::Rect &box)
{
    int index = -1;
    bool bTop = box.getMaxY() <= _box.getMaxY() && box.getMinY() >= _center.y;
    bool bBottom = box.getMaxY() <= _center.y && box.getMinY() >= _box.getMinY();
    bool bLeft = box.getMinX() >= _box.getMinX() && box.getMaxY() <= _center.x;
    bool bRight = box.getMinX() >= _center.x && box.getMaxY() <= _box.getMaxX();
    
    if (bTop)
    {
        if (bLeft)
        {
            index = 0;
        }
        else if (bRight)
        {
            index = 1;
        }

    }
    else if (bBottom)
    {
        if (bLeft)
        {
            index = 2;
        }
        else if (bRight)
        {
            index = 3;
        }
    }
    
    return index;
}

bool Quadtree::insert(MoveObject* node)
{
    if (_node[0] != nullptr)
    {
        int index = getIndex(node->getBox());
        if (index != -1)
        {
            _node[index]->insert(node);
        }
    }
    _objects.push_back(node);

    if (_objects.size() > _maxObjects && _depth < _maxDepth)
    {
        subdivide();
        int i = 0;
        while (i < _objects.size())
        {
            int index = getIndex(node->getBox());
            if (index != -1)
            {
                _node[index]->insert(_objects.back());
                _objects.pop_back();
            }
            else
            {
                ++i;
            }
        }
    }
    
    return true;
}

void Quadtree::query(std::vector<MoveObject*>& objs, const Rect& box)
{
    int index = getIndex(box);
    if (index != -1 && _node[0] != nullptr)
    {
        _node[index]->query(objs, box);
    }
    
    for (int i=0; i<_objects.size(); ++i)
    {
        objs.push_back(_objects[i]);
    }
}

void Quadtree::subdivide()
{
    Rect box;
    box.size = _halfSize;
    // left top
    box.origin = Vec2(_box.getMinX(), _center.y);
    _node[0] = new Quadtree(_depth +1, box);
    // right top
    box.origin = Vec2(_center.x, _center.y);
    _node[1] = new Quadtree(_depth +1, box);
    // left bottom
    box.origin = Vec2(_box.getMinX(), _box.getMinY());
    _node[2] = new Quadtree(_depth +1, box);
    // right bottom
    box.origin = Vec2(_center.x, _box.getMinY());
    _node[3] = new Quadtree(_depth +1, box);
}

void Quadtree::clear()
{
    for (int i=0; i<4; ++i)
    {
        _node[i]->clear();
        delete _node[i];
        _node[i] = nullptr;
    }
}