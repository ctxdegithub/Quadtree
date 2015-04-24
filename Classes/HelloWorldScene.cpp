#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Player.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto size = Director::getInstance()->getWinSize();
    _quadtree.setBox(Rect(0, 0, size.width, size.height));
    for (int i=0; i<10; ++i)
    {
        auto player = Player::create();
        _players.push_back(player);
        player->setPosition(Vec2(CCRANDOM_0_1() * size.width, CCRANDOM_0_1() * size.height));
        addChild(player);
        _quadtree.insert(player);
    }
    
    _drawNode = DrawNode::create();
    addChild(_drawNode);
    _drawNode->drawRect(Vec2::ZERO, Vec2(100, 100), Color4F::GREEN);
    scheduleUpdate();

    return true;
}

void HelloWorld::update(float delta)
{
    for (int i=0; i<10; ++i)
    {
        _players[i]->setSelected(false);
    }
    
    std::vector<MoveObject*> players;
    Rect rc;
    rc.origin = _drawNode->getPosition();
    rc.size = Size(100, 100);
    _quadtree.query(players, rc);
    for (auto player : players)
    {
        ((Player*)player)->setSelected(true);
    }
    log("%.f, %.f, %d", _drawNode->getPositionX(), _drawNode->getPositionY(), players.size());
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}


void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    _drawNode->setPosition(_drawNode->getPosition() + touch->getLocation() - touch->getPreviousLocation());
}


