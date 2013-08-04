//
//  Hero.h
//  studygame
//
//  Created by Robert Ignasiak on 04.08.2013.
//
//


#include "cocos2d.h"
#include "Box2D.h"
#include "Joystick.h"

class Npc : public cocos2d::CCSprite
{
public:
    Npc();
    void setWorld(b2World * world);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
    
    void update(float dt);
    void kick();
    void stop();
    
private:
    b2World* m_pWorld;    // strong ref
    b2Body *m_pBody;
};

