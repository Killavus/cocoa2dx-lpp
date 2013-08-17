//
//  SpaceNoteAppDelegate.cpp
//  SpaceNote
//
//  Created by Robert Ignasiak on 04.07.2013.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

#include "../platform/CCFileUtils.h"


USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    // turn on display FPS
    pDirector->setDisplayStats(false);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCSize designSize = CCSizeMake(480, 320);
    CCSize resourceSize = CCSizeMake(480, 320);
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    std::vector<std::string> searchPaths;
    std::vector<std::string> resDirOrders;
    
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone || platform == kTargetIpad)
    {
        searchPaths.push_back("Published-iOS"); // Resources/Published-iOS
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        
        if (screenSize.width > 1536)
        {
            designSize = CCSizeMake(2048, 1536);
            resourceSize = CCSizeMake(2048, 1536);
            resDirOrders.push_back("resources-ipadhd");
            std::cout << "Resources ipadhd";
            pDirector->setContentScaleFactor(4);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/4, designSize.height/4, kResolutionShowAll);
        }
        else if (screenSize.width > 1136)
        {
            designSize = CCSizeMake(1536, 768);
            resourceSize = CCSizeMake(1536, 768);
            resDirOrders.push_back("resources-ipad");
            std::cout << "Resources ipad";
            pDirector->setContentScaleFactor(2);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/2, designSize.height/2, kResolutionShowAll);
        }
        else if (screenSize.width > 960)
        {
            designSize = CCSizeMake(1136, 640);
            resourceSize = CCSizeMake(1136, 640);
            resDirOrders.push_back("resources-iphonehd");
            std::cout << "Resources iPhonehd";
            pDirector->setContentScaleFactor(2);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/2, designSize.height/2, kResolutionShowAll);
        }
        else if (screenSize.width > 480)
        {
            designSize = CCSizeMake(960, 640);
            resourceSize = CCSizeMake(960, 640);
            resDirOrders.push_back("resources-iphonehd");
            std::cout << "Resources iPhonehd";
            pDirector->setContentScaleFactor(2);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/2, designSize.height/2, kResolutionShowAll);
        }
        else
        {
            resDirOrders.push_back("resources-iphone");
            std::cout << "Resources iPhone";
            pDirector->setContentScaleFactor(1);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/1, designSize.height/1, kResolutionShowAll);
        }
        
        CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
    }
    else if (platform == kTargetAndroid)
    {   
        if (screenSize.width > 960)
        {
            designSize = CCSizeMake(screenSize.width, screenSize.height);
            resourceSize = CCSizeMake(screenSize.width, screenSize.height);
            resDirOrders.push_back("resources-large");
            pDirector->setContentScaleFactor(4);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/4, designSize.height/4, kResolutionShowAll);
        }
        else if (screenSize.width > 480)
            
        {
            designSize = CCSizeMake(screenSize.width, screenSize.height);
            resourceSize = CCSizeMake(screenSize.width, screenSize.height);
            resDirOrders.push_back("resources-medium");
            pDirector->setContentScaleFactor(2);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/2, designSize.height/2, kResolutionShowAll);
        }
        else
        {
            designSize = CCSizeMake(screenSize.width, screenSize.height);
            resourceSize = CCSizeMake(screenSize.width, screenSize.height);
            resDirOrders.push_back("resources-small");
            pDirector->setContentScaleFactor(1);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/1, designSize.height/1, kResolutionShowAll);
        }
        
        CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
    }
	else if (platform == kTargetLinux || platform == kTargetWindows) {
        searchPaths.push_back("Published-iOS"); // Resources/Published-iOS
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        
        if (screenSize.width > 1536)
        {
            designSize = CCSizeMake(2048, 1536);
            resourceSize = CCSizeMake(2048, 1536);
            resDirOrders.push_back("resources-ipadhd");
            std::cout << "Resources ipadhd";
            pDirector->setContentScaleFactor(4);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/4, designSize.height/4, kResolutionShowAll);
        }
        else if (screenSize.width > 1136)
        {
            designSize = CCSizeMake(1536, 768);
            resourceSize = CCSizeMake(1536, 768);
            resDirOrders.push_back("resources-ipad");
            std::cout << "Resources ipad";
            pDirector->setContentScaleFactor(2);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/2, designSize.height/2, kResolutionShowAll);
        }
        else if (screenSize.width > 960)
        {
            designSize = CCSizeMake(1136, 640);
            resourceSize = CCSizeMake(1136, 640);
            resDirOrders.push_back("resources-iphonehd");
            std::cout << "Resources iPhonehd";
            pDirector->setContentScaleFactor(2);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/2, designSize.height/2, kResolutionShowAll);
        }
        else if (screenSize.width > 480)
        {
            designSize = CCSizeMake(960, 640);
            resourceSize = CCSizeMake(960, 640);
            resDirOrders.push_back("resources-iphonehd");
            std::cout << "Resources iPhonehd";
            pDirector->setContentScaleFactor(2);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/2, designSize.height/2, kResolutionShowAll);
        }
        else
        {
            resDirOrders.push_back("resources-iphone");
            std::cout << "Resources iPhone";
            pDirector->setContentScaleFactor(1);
            CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width/1, designSize.height/1, kResolutionShowAll);
        }
        
        CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
    }
    
    // create a scene. it's an autorelease object
	CCScene *pScene = MainMenuScene::scene();
    
    // run
    pDirector->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
