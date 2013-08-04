//
//  HelloWorldScene.cpp
//  jkj
//
//  Created by Robert Ignasiak on 30.07.2013.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "SimpleAudioEngine.h"
#include "PhysicsWorldScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define PTM_RATIO 32

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{

}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool PhysicsSprite::isDirty(void)
{
    return true;
}

void PhysicsSprite::update(float dt)
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
    b2Vec2 vec = m_pBody->GetLinearVelocity();
    //this->setRotation(-1*CC_RADIANS_TO_DEGREES(ccpToAngle(CCPointMake(vec.x, vec.y))));
    
}

void PhysicsSprite::setJoystick( Joystick *joystick )
{
    m_pJoystick = joystick;
}

void PhysicsSprite::kick()
{
    b2Vec2 force = b2Vec2(30,30);
    m_pBody->ApplyLinearImpulse(force,m_pBody->GetPosition());
}

void PhysicsSprite::stop()
{
    m_pBody->SetLinearVelocity(b2Vec2(0,0));
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
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



PsysicsWorld::PsysicsWorld()
{
    setTouchEnabled( true );
    setAccelerometerEnabled( true );

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    // init physics
    this->initPhysics();

    addNewSpriteAtPosition(ccp(s.width/2, s.height/2));

    scheduleUpdate();
    
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "button1_inactive.png",
                                                          "button1_inactive.png",
                                                          this,
                                                          menu_selector(PsysicsWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 50, 50) );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
}

PsysicsWorld::~PsysicsWorld()
{
    delete world;
    world = NULL;
    
    //delete m_debugDraw;
}

void PsysicsWorld::initPhysics()
{
    joy = Joystick::create();
    this->addChild(joy);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();

    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);
    world = new b2World(gravity);

    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    
    world->SetContinuousPhysics(true);
    
//     m_debugDraw = new GLESDebugDraw( PTM_RATIO );
//     world->SetDebugDraw(m_debugDraw);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    //m_debugDraw->SetFlags(flags);


    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner

    // Call the body factory which allocates memory for the ground body
    // from a pool and creates the ground box shape (also from a pool).
    // The body is also added to the world.
    b2Body* groundBody = world->CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2EdgeShape groundBox;

    // bottom

    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
}

void PsysicsWorld::draw()
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    world->DrawDebugData();

    kmGLPopMatrix();
}

void PsysicsWorld::addNewSpriteAtPosition(CCPoint p)
{
    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    
    CCSprite *image = CCSprite::create("0.png");
    m_pSpriteTexture = image->getTexture();
    sprite = new PhysicsSprite();
    sprite->initWithTexture(m_pSpriteTexture);
    
    sprite->autorelease();
    
    this->addChild(sprite);
    
    sprite->setPosition( CCPointMake( p.x, p.y) );
    
    // Define the dynamic body.
    //Set up a 1m squared box in the physics world
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    
    b2Body *body = world->CreateBody(&bodyDef);
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;    
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
    
    sprite->setPhysicsBody(body);
    sprite->setJoystick(joy);
    
    sprite->scheduleUpdate();
    
    
}

void PsysicsWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        sprite->stop();
    }
}

void PsysicsWorld::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, velocityIterations, positionIterations);
    
    //Iterate over the bodies in the physics world
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            //Synchronize the AtlasSprites position and rotation with the corresponding body
            CCSprite* myActor = (CCSprite*)b->GetUserData();
            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }    
    }
}

void PsysicsWorld::menuCloseCallback(CCObject* pSender)
{
    sprite->kick();
}

CCScene* PsysicsWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new PsysicsWorld();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
