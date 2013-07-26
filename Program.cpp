#include <iostream>
#include <string>

#include <cocos2d.h>

#include "Application/Framework/AppDelegate.h"

USING_NS_CC;

int main(int argc, char **argv)
{
    AppDelegate app;

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(800, 480);

    return CCApplication::sharedApplication()->run();
}
