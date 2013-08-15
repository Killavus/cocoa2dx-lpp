//
//  Option.h
//  studygame
//
//  Created by Robert Ignasiak on 04.08.2013.
//
//

#ifndef __studygame__Option__
#define __studygame__Option__

#include "cocos2d.h"

using namespace cocos2d;

class Option
{
    Option();
    public:
        void setOptions(CCObject *pObject, const std::string &key);
        CCDictionary* getOptions();
        CCDictionary* createOptions();
    private:
        CCDictionary* optionsDictionary;
};
#endif /* defined(__studygame__Option__) */
