#include "cocos2d.h"
#include <CCControlButton.h>
#include <CCEditBox.h>
#include "GameWorldScene.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class NameWorld : public cocos2d::CCLayer
{
private:
    CCTextFieldTTF* textInput;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(NameWorld);
    
    void menuNameCallback(CCObject* pSender);    
};
