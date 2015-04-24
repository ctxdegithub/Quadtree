//
//  Quadtree.h
//  quadtree
//
//  Created by DONG on 15/4/24.
//
//

#ifndef __quadtree__Quadtree__
#define __quadtree__Quadtree__

#include "cocos2d.h"
USING_NS_CC;

class MoveObject
{
public:
    MoveObject();
    MoveObject(const Vec2& pos, const Size& size);
    MoveObject(const Vec2& pos, const Size& size, void* userData);
    bool intersect(const Rect& box);
    const Vec2& getPos() const;
    void setPos(const Vec2& pos);
    
    const Size& getSize() const;
    void setSize(const Size& size);
    
    const Rect& getBox() const;
    
protected:
    void updateBox();
    
protected:
    Rect _box;
    Vec2 _pos;
    Size _size;
    CC_SYNTHESIZE(void*, _userData, UserData);
};

#pragma QuadTree

class Quadtree
{
public:
    Quadtree();
    Quadtree(int depth, const Rect& box);
    
    bool insert(MoveObject* node);
    void query(std::vector<MoveObject*>& objs, const Rect& box);
    void clear();
    
private:
    void subdivide();
    void init();
    int getIndex(const Rect& box);
    
private:
    CC_SYNTHESIZE(Rect, _box, Box);
    CC_SYNTHESIZE(Size, _halfSize, HalfSize);
    CC_SYNTHESIZE(Vec2, _center, Center);
    int _depth;
    int _maxDepth;
    int _maxObjects;
    std::vector<MoveObject*> _objects;
    Quadtree* _node[4]; // 0 left top, 1 right top, 2 left bottom, 3 right bottom
};

#endif /* defined(__quadtree__Quadtree__) */
