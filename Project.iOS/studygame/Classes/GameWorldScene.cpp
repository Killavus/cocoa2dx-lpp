#include "GameWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameWorld *layer = GameWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameWorld::init()
{

    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->addChild(PsysicsWorld::scene());

    CCLabelTTF* pLabel = CCLabelTTF::create("", "Thonburi", 34);
    std::string ret = CCUserDefault::sharedUserDefault()->getStringForKey("NazwaPostaci");
    pLabel->setString(CCString::createWithFormat("Witaj %s",ret.c_str())->getCString());
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    this->addChild(pLabel, 1);
    
    return true;
}


