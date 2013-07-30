//
//  MainMenuScene.h
//  SpaceNote
//
//  Created by Robert Ignasiak on 05.07.2013.
//
//

#ifndef __SpaceNote__MainMenuScene__
#define __SpaceNote__MainMenuScene__

#define ccsf(...) CCString::createWithFormat(__VA_ARGS__)->getCString()

#include "cocos2d.h"
#include "cocos-ext.h"
#include "NameWorldScene.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class MainMenuScene : public cocos2d::CCLayer,public cocos2d::extension::CCBMemberVariableAssigner, public cocos2d::extension::CCBSelectorResolver
{
private:
    
public:
    static CCScene* scene();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainMenuScene, create);
    
    virtual void onEnter();
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    
    void update(float dt);
    void pressedPlay(cocos2d::CCObject *pSender);

};

#endif /* defined(__SpaceNote__MainMenuScene__) */
