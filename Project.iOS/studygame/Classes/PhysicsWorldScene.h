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

class PhysicsSprite : public cocos2d::CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);

    void update(float dt);
    void setJoystick( Joystick *joystick );
    
private:
    b2Body* m_pBody;    // strong ref
    Joystick* m_pJoystick;
};

class PsysicsWorld : public cocos2d::CCLayer {
public:
    ~PsysicsWorld();
    PsysicsWorld();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    void initPhysics();
    // adds a new sprite at a given coordinate
    void addNewSpriteAtPosition(cocos2d::CCPoint p);

    virtual void draw();
    void update(float dt);
    
private:
    b2World* world;
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref
    Joystick* joy;
};

