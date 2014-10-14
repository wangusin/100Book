//
//  EStory003AppDelegate.cpp
//  EStory003
//
//  Created by imac07 on 2014/10/3.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Page1.h"

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
    ccLanguageType languagType=CCApplication::sharedApplication()->getCurrentLanguage();
    switch (languagType)
    {
        case cocos2d::kLanguageTraditional:
            CCLOG("繁");
            CCUserDefault::sharedUserDefault()->setIntegerForKey("Record_Language", 0);
            break;
        default:
            CCLOG("簡");
            CCUserDefault::sharedUserDefault()->setIntegerForKey("Record_Language", 1);
            break;
    }
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = Page1::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
    JniMethodInfo minfo;
    if(JniHelper::getStaticMethodInfo(minfo,
                                      "org/cocos2dx/lib/Cocos2dxActivity",
                                      "pauseVideo",
                                      "()V"))
    {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
    JniMethodInfo minfo;
    if(JniHelper::getStaticMethodInfo(minfo,
                                      "org/cocos2dx/lib/Cocos2dxActivity",
                                      "startVideo",
                                      "()V"))
    {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
    
#endif
}
