#include "NameWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* NameWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    NameWorld *layer = NameWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NameWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCLabelTTF* pLabel = CCLabelTTF::create("Podaj nazwe postaci", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    CCEditBox* editBox = CCEditBox::create(CCSize(300, 100), CCScale9Sprite::create("button1_inactive.png"));
    editBox->setPosition( ccp(size.width / 2, size.height - 150) );
    editBox->setFontColor(ccRED);
    editBox->setPlaceHolder("...");
    editBox->setReturnType(kKeyboardReturnTypeDone);
    editBox->setDelegate(this);
    addChild(editBox);
    
    
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

void NameWorld::menuNameCallback()
{
    CCLog("PressedPlay");
    CCScene *gameScene = GameWorld::scene();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,gameScene));
}

void NameWorld::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("%p ", editBox);
}

void NameWorld::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{
    CCLog("%p", editBox);
}

void NameWorld::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{
    CCLog("%p  %s ", editBox, text.c_str());
}

void NameWorld::editBoxReturn(CCEditBox* editBox)
{
    CCLog("%p",editBox);

}