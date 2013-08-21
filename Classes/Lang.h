//
//  Language.h
//  studygame
//
//  Created by Robert Ignasiak on 21.08.2013.
//
//

#ifndef __studygame__Language__
#define __studygame__Language__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;

class Lang
{
    private:
        CCDictionary* polski;
        CCDictionary* niemiecki;
        CCDictionary* angielski;
        Lang()
        {
            polski = CCDictionary::createWithContentsOfFile("Polski.plist");
            niemiecki = CCDictionary::createWithContentsOfFile("Niemiecki.plist");
            angielski = CCDictionary::createWithContentsOfFile("Angielski.plist");
        }
    public:

    void setText(std::string Text);
    static void getText(std::string Text);
};
#endif /* defined(__studygame__Language__) */
