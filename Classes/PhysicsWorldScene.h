//
//  HelloWorldScene.h
//  jkj
//
//  Created by Robert Ignasiak on 30.07.2013.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//


// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "Joystick.h"
#include "Hero.h"
#include "Npc.h"
#include "ContactListener.h"
#include "GLES-Render.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class PsysicsWorld : public cocos2d::CCLayer {
public:
    ~PsysicsWorld();
    PsysicsWorld();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    void initPhysics();
    // adds a new sprite at a given coordinate
    void addNewSprite();

    void updateCamera(CCTime dt);
    virtual void draw();
    void update(float dt);
    void menuCloseCallback(CCObject* pSender);
    void ccTouchesEnded(CCSet* touches, CCEvent* event);
    void animationCompleteCallback();

private:
    bool isComplited;
    bool setView;
    CCNode* menuNode;
    CCBAnimationManager* animationManager;
    b2World* world;
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref
    Joystick* joy;
    Hero *hero;
    Npc* npc;
    CContactListener* contactListener;
    GLESDebugDraw *m_debugDraw;
    CCSprite *image;

};

