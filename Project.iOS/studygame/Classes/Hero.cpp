//
//  Hero.cpp
//  studygame
//
//  Created by Robert Ignasiak on 04.08.2013.
//
//

#include "Hero.h"
using namespace cocos2d;

#define PTM_RATIO 32

Hero::Hero()
: m_pWorld(NULL)
{

}

void Hero::setWorld(b2World * world)
{
    m_pWorld = world;
    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    bodyDef.position.Set(s.width/2/PTM_RATIO, s.height/2/PTM_RATIO);
    
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.isSensor = true;
    m_pBody->CreateFixture(&fixtureDef);
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool Hero::isDirty(void)
{
    return true;
}

void Hero::update(float dt)
{
    float vx = m_pJoystick->getVelocity().x;
    float vy = m_pJoystick->getVelocity().y;
    
    // set ball velocity by Joystick
    if(vx<0) {
        this->setFlipX(true);
    } else if(vx>0) {
        this->setFlipX(false);
    }
    m_pBody->SetLinearVelocity(b2Vec2(vx,vy)+m_pBody->GetLinearVelocity());
    
    // rotation ball by direction
    // b2Vec2 vec = m_pBody->GetLinearVelocity();
    //this->setRotation(-1*CC_RADIANS_TO_DEGREES(ccpToAngle(CCPointMake(vec.x, vec.y))));

}

void Hero::setJoystick( Joystick *joystick )
{
    m_pJoystick = joystick;
}

void Hero::kick()
{
    b2Vec2 force = b2Vec2(30,30);
    m_pBody->ApplyLinearImpulse(force,m_pBody->GetPosition());
}

void Hero::stop()
{
    m_pBody->SetLinearVelocity(b2Vec2(0,0));
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform Hero::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();
    
    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;
    
    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }
    
    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);
    
    if( ! m_obAnchorPointInPoints.equals(CCPointZero) ){
        x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
        y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
    }
    
    // Rot, Translate Matrix
    m_sTransform = CCAffineTransformMake( c,  s,
                                         -s,    c,
                                         x,    y );
    
    return m_sTransform;
}