//
//  Option.cpp
//  studygame
//
//  Created by Robert Ignasiak on 04.08.2013.
//
//

#include "Option.h"

Option::Option()
{
    optionsDictionary = CCDictionary::createWithContentsOfFile("option.plist");
}

void Option::setOptions(CCObject *pObject, const std::string &key)
{

}

CCDictionary* Option::getOptions(){
    optionsDictionary = CCDictionary::createWithContentsOfFile("option.plist");
    return optionsDictionary;
}

CCDictionary* Option::createOptions(){
    optionsDictionary = CCDictionary::create();
    CCString* plLanguage = CCString::create("PL");
    optionsDictionary->setObject(plLanguage, "language");
    optionsDictionary->writeToFile("option.plist");
    return optionsDictionary;
}
