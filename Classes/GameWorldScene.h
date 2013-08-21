#ifndef __GAMEWORLD_SCENE_H__
#define __GAMEWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Joystick.h"
#include "PhysicsWorldScene.h"
//#include "Logic/Player.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class GameWorld : public cocos2d::CCLayer,public cocos2d::extension::CCBMemberVariableAssigner, public cocos2d::extension::CCBSelectorResolver
{
private:
    bool isComplited;
    bool setView;
    CCLabelTTF* nameLabel;
    CCBAnimationManager* animationManager;
    CCNode* menuNode;

public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameWorld);
    
    void menuCloseCallback(CCObject* pSender);
    void pressedBack(CCObject* pSender);

    void animationCompleteCallback();
};

#endif // __GAMEWORLD_SCENE_H__
