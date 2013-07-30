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
}


SEL_MenuHandler MainMenuScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject *pTarget, const char *pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pressedPlay:", MainMenuScene::pressedPlay);
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
        CCLog("PressedPlay");
        CCScene *gameScene = GameWorld::scene();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,gameScene));
    }
    else
    {
        CCLog("PressedPlay");
        CCScene *gameScene = NameWorld::scene();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,gameScene));    }

}



