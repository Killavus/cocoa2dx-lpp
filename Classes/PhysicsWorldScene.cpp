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

PsysicsWorld::PsysicsWorld()
{
    setTouchEnabled( true );
    setAccelerometerEnabled( true );


    // init physics
    this->initPhysics();

    addNewSprite();

    scheduleUpdate();
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
    
     m_debugDraw = new GLESDebugDraw( PTM_RATIO );
     world->SetDebugDraw(m_debugDraw);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    //        flags += b2Draw::e_jointBit;
    //        flags += b2Draw::e_aabbBit;
    //        flags += b2Draw::e_pairBit;
    //        flags += b2Draw::e_centerOfMassBit;
    m_debugDraw->SetFlags(flags);

    /*
     
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
     
     */
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_kinematicBody;
    myBodyDef.position.Set(0, 0);
    b2Body* staticBody = world->CreateBody(&myBodyDef);
    
    //shape definition
    b2PolygonShape polygonShape;
    
    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    
    //add four walls to the static body
    polygonShape.SetAsBox( 20, 1, b2Vec2(0, 0), 0);//ground
    staticBody->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox( 20, 1, b2Vec2(0, 40), 0);//ceiling
    staticBody->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox( 1, 20, b2Vec2(-20, 20), 0);//left wall
    staticBody->CreateFixture(&myFixtureDef);
    polygonShape.SetAsBox( 1, 20, b2Vec2(20, 20), 0);//right wall
    staticBody->CreateFixture(&myFixtureDef);
    
    CContactListener* contactListener = new CContactListener();
    world->SetContactListener(contactListener);
    schedule( schedule_selector(PsysicsWorld::updateCamera), 1.0f );
}

void PsysicsWorld::updateCamera(CCTime dt)
{
    CCLog("updateCamera");

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

void PsysicsWorld::addNewSprite()
{
    image = CCSprite::create("0.png");
    m_pSpriteTexture = image->getTexture();
    hero = new Hero();
    hero->initWithTexture(m_pSpriteTexture);
    
    hero->autorelease();
    
    this->addChild(hero);
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    hero->setPosition( ccp(s.width/2, s.height/2) );
    hero->setWorld(world);
 
    hero->setJoystick(joy);
    
    hero->scheduleUpdate();
    
    npc = new Npc();
    npc->initWithTexture(m_pSpriteTexture);
    
    npc->autorelease();
    
    this->addChild(npc);
    
    npc->setPosition( ccp(s.width/2+200, s.height/2) );
    
    npc->setWorld(world);
    
    npc->scheduleUpdate();
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
        
        hero->stop();
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
