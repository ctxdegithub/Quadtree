#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Quadtree.h"
USING_NS_CC;

class Player;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void update(float delta);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    
private:
    Quadtree _quadtree;
    std::vector<Player*> _players;
    DrawNode* _drawNode;
};

#endif // __HELLOWORLD_SCENE_H__
