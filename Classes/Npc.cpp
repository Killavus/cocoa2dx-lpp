//
//  Hero.cpp
//  studygame
//
//  Created by Robert Ignasiak on 04.08.2013.
//
//

#include "Npc.h"
using namespace cocos2d;

#define PTM_RATIO 32

Npc::Npc()
: m_pWorld(NULL)
{

}

void Npc::setWorld(b2World * world)
{
    m_pWorld = world;
    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    bodyDef.position.Set((s.width/2+200)/PTM_RATIO, s.height/2/PTM_RATIO);
    
    m_pBody = m_pWorld->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    m_pBody->CreateFixture(&fixtureDef);
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool Npc::isDirty(void)
{
    return true;
}

void Npc::update(float dt)
{
    //CCSize s = CCDirector::sharedDirector()->getWinSize();
    //float pForce = 10;
    //b2Vec2 forceDir = b2Vec2( ( (s.width/2+200)/PTM_RATIO - m_pBody->GetPosition().x ) * pForce  ,
    //                         ( s.height/2/PTM_RATIO - m_pBody->GetPosition().y ) * pForce );
    //m_pBody->ApplyForceToCenter(forceDir);
}

void Npc::kick()
{
    b2Vec2 force = b2Vec2(30,30);
    m_pBody->ApplyLinearImpulse(force,m_pBody->GetPosition());
}

void Npc::stop()
{
    m_pBody->SetLinearVelocity(b2Vec2(0,0));
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform Npc::nodeToParentTransform(void)
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