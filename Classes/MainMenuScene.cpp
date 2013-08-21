//
//  MainMenuScene.cpp
//  SpaceNote
//
//  Created by Robert Ignasiak on 05.07.2013.
//
//

#include "MainMenuScene.h"
#include "MainMenuSceneLoader.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* MainMenuScene::scene()
{
    CCScene* scene = CCScene::create();
    scene->addChild(MainMenuSceneLoader::load());
    return scene;
}

void MainMenuScene::onEnter()
{
    CCLayer::onEnter();
    this->scheduleUpdate();
    this->setTouchEnabled(true);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Music/background.mp3");
}


SEL_MenuHandler MainMenuScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressedPlay:", MainMenuScene::pressedPlay);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressedOption:", MainMenuScene::pressedOption);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressedOptionBack:", MainMenuScene::pressedOptionBack);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressedResetGame:", MainMenuScene::resetGame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "muteSound:", MainMenuScene::muteSound);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "setToPL:", MainMenuScene::setToPL);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "setToDE:", MainMenuScene::setToDE);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "setToGB:", MainMenuScene::setToGB);
    return NULL;
}

SEL_CCControlHandler MainMenuScene::onResolveCCBCCControlSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    return NULL;
}

bool MainMenuScene::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}


bool MainMenuScene::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cSoundItem", CCMenuItem*, soundItem);
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "cPlayLabel", CCLabelTTF*, playLabel);
    return false;
}


void MainMenuScene::update(float dt) {

}


void MainMenuScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

}

void MainMenuScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

}

void MainMenuScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

}

void MainMenuScene::pressedPlay(cocos2d::CCObject *pSender)
{
    bool firstGame = CCUserDefault::sharedUserDefault()->getBoolForKey("NowaGra");
    if (firstGame)
    {
        CCScene *gameScene = GameWorld::scene();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,gameScene));
    }
    else
    {
        CCScene *gameScene = NameWorld::scene();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,gameScene));    
    }
}

void MainMenuScene::pressedOption(cocos2d::CCObject *pSender)
{
    CCNodeLoaderLibrary* nodeLoaderLibrary;
    nodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    
    CCNode* optionNode = ccbReader->readNodeGraphFromFile("OptionScene.ccbi",this);
    optionNode->setTag(69);
    this->addChild(optionNode);
}

void MainMenuScene::pressedOptionBack(cocos2d::CCObject *pSender)
{
    this->removeChildByTag(69);
}

void MainMenuScene::resetGame(cocos2d::CCObject *pSender)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey("NowaGra", false);
}

void MainMenuScene::muteSound(cocos2d::CCObject *pSender)
{
    soundItem->setEnabled(false);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void MainMenuScene::setToPL(cocos2d::CCObject *pSender)
{
    CCUserDefault::sharedUserDefault()->setStringForKey("Language", "PL");
    Lang* text = new Lang();
    text->getText("Play");
}

void MainMenuScene::setToDE(cocos2d::CCObject *pSender)
{
    CCUserDefault::sharedUserDefault()->setStringForKey("Language", "DE");
}

void MainMenuScene::setToGB(cocos2d::CCObject *pSender)
{
    CCUserDefault::sharedUserDefault()->setStringForKey("Language", "GB");
}
