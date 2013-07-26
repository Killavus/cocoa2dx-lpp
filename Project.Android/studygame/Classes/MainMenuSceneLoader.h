//
//  MainMenuSceneLoader.h
//  SpaceNote
//
//  Created by Robert Ignasiak on 05.07.2013.
//
//

#ifndef __SpaceNote__MainMenuSceneLoader__
#define __SpaceNote__MainMenuSceneLoader__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "MainMenuScene.h"

class MainMenuSceneLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainMenuSceneLoader, loader);
    static MainMenuScene* load();
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainMenuScene);
    
};

#endif /* defined(__SpaceNote__MainMenuSceneLoader__) */
