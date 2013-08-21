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

    CCNodeLoaderLibrary* nodeLoaderLibrary;
    nodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    CCNode* optionNode = ccbReader->readNodeGraphFromFile("TopMenu.ccbi",this);
    optionNode->setTag(69);
    this->addChild(optionNode);
    
    std::string ret = CCUserDefault::sharedUserDefault()->getStringForKey("NazwaPostaci");
    nameLabel->setString(CCString::createWithFormat("%s",ret.c_str())->getCString());
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    isComplited=true;
    setView=true;
    
    //Player* Robcio = new Player("Robio","Student");
    return true;
}

SEL_MenuHandler GameWorld::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{

    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressedMenu:", GameWorld::menuCloseCallback);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressedBack:", GameWorld::pressedBack);

    return NULL;
}

SEL_CCControlHandler GameWorld::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

bool GameWorld::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}


bool GameWorld::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cNameLabel", CCLabelTTF*, nameLabel);
    return false;
}

void GameWorld::pressedBack(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}

void GameWorld::menuCloseCallback(CCObject* pSender)
{
    if( isComplited) {
        isComplited=false;
        if(setView){
            setView=false;
            this->removeChild(menuNode);
            CCNodeLoaderLibrary* nodeLoaderLibrary;
            nodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
            CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
            menuNode = ccbReader->readNodeGraphFromFile("Menu.ccbi",this);
            this->addChild(menuNode);
            animationManager = (CCBAnimationManager*)menuNode->getUserObject();
            animationManager->runAnimationsForSequenceNamed("Start");
            animationManager->setAnimationCompletedCallback(this, callfunc_selector(GameWorld::animationCompleteCallback));
        } else {
            setView=true;
            animationManager = (CCBAnimationManager*)menuNode->getUserObject();
            animationManager->runAnimationsForSequenceNamed("Stop");
            animationManager->setAnimationCompletedCallback(this, callfunc_selector(GameWorld::animationCompleteCallback));
        }
    }
}

void GameWorld::animationCompleteCallback(){
    isComplited=true;
}