#include "NameWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* NameWorld::scene()
{
    CCScene *scene = CCScene::create();
    NameWorld *layer = NameWorld::create();
    scene->addChild(layer);

    return scene;
}

bool NameWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCLabelTTF* pLabel = CCLabelTTF::create("Podaj nazwe postaci", "Thonburi", 34);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
    addChild(pLabel, 1);

    CCScale9Sprite* textInputBackground = CCScale9Sprite::create("button1_inactive.png");
    textInputBackground->setContentSize(CCSize(200, 50));
    textInputBackground->setPosition(ccp(size.width / 2, size.height / 2));

    CCTextFieldTTF* textInput = CCTextFieldTTF::textFieldWithPlaceHolder("foo", "Tahoma", 16.0);
    textInput->setPosition(ccp(size.width / 2, size.height / 2)); 
    textInput->attachWithIME();

    addChild(textInputBackground, 1);
    addChild(textInput, 2);
  
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "button1_inactive.png",
                                                          "button1_inactive.png",
                                                          this,
                                                          menu_selector(NameWorld::menuNameCallback) );

    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
        
    return true;
}

void NameWorld::menuNameCallback(CCObject* pSender)
{
    CCLog("PressedPlay");
    CCScene *gameScene = GameWorld::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,gameScene));
}
