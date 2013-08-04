//
//  Hero.h
//  studygame
//
//  Created by Robert Ignasiak on 04.08.2013.
//
//

#ifndef __studygame__Hero__
#define __studygame__Hero__

#include "cocos2d.h"
#include "Box2D.h"
#include "Joystick.h"

class Hero : public cocos2d::CCSprite
{
public:
    Hero();
    void setWorld(b2World * world);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
    
    void update(float dt);
    void setJoystick( Joystick *joystick );
    void kick();
    void stop();
    
private:
    b2World* m_pWorld;    // strong ref
    Joystick* m_pJoystick;
    b2Body *m_pBody;
};


#endif /* defined(__studygame__Hero__) */
