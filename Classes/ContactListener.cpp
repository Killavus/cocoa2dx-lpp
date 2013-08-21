//
//  Contact.cpp
//  HelloWorld
//
//  Created by Gavin Thornton on 11-08-18.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ContactListener.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
CContactListener::CContactListener(): _contacts(),
pEngine(NULL)
{
    pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
}

CContactListener::~CContactListener()
{
}

void CContactListener::BeginContact(b2Contact* contact) 
{
    // We need to copy out the data because the b2Contact passed in
    // is reused.
    

    b2Fixture* figure1 = contact->GetFixtureA();
    b2Fixture* figure2 = contact->GetFixtureB();
    CCLOG("%d, %d",figure1->GetType(),figure2->GetType());
    if (((CCSprite*)figure2->GetUserData())->getTag()==121){
        std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("hello.lua");
        pEngine->executeScriptFile(path.c_str());
    }
    ContactData Contact = { contact->GetFixtureA(), contact->GetFixtureB() };
    _contacts.push_back(Contact);
     
}

void CContactListener::EndContact(b2Contact* contact) 
{
    b2Fixture* figure1 = contact->GetFixtureA();
    b2Fixture* figure2 = contact->GetFixtureB();
    if (figure1->GetType()==figure2->GetType()){
    }
    ContactData Contact = { contact->GetFixtureA(), contact->GetFixtureB() };
    std::vector<ContactData>::iterator pos;
    pos = std::find(_contacts.begin(), _contacts.end(), Contact);
    if (pos != _contacts.end()) {
        _contacts.erase(pos);
    }
}

void CContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) 
{
}

void CContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) 
{
}