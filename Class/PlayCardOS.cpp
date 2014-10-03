//
//  PlayCardOS.cpp
//  EStory001
//
//  Created by imac07 on 2014/8/4.
//
//

#include "PlayCardOS.h"
using namespace cocos2d;
using namespace CocosDenshion;


PlayCardOS* PlayCardOS::createByMp3Name(const char *spName){
    PlayCardOS *pobSprite = new PlayCardOS();
    
    if (pobSprite && pobSprite!=NULL)
    {
        pobSprite->playos(spName);
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    
    return NULL;
}
PlayCardOS* PlayCardOS::createStopMp3Name(){
    PlayCardOS *pobSprite = new PlayCardOS();
    
    if (pobSprite && pobSprite!=NULL)
    {
        pobSprite->stopos();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    
    return NULL;
}

void PlayCardOS::playos(const char *pszFilePath)
{
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android
    JniMethodInfo minfo;
    if(JniHelper::getStaticMethodInfo(minfo,
                                      "tw/com/b_a/EStory001/EStory001",
                                      "playVideo",
                                      "(Ljava/lang/String;)V"))
    {
        jstring StringArg1 = minfo.env->NewStringUTF(pszFilePath);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
        minfo.env->DeleteLocalRef(StringArg1);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
    
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //IOS
    SimpleAudioEngine::sharedEngine()->playEffect(pszFilePath);
#endif
    
    
}
void PlayCardOS::stopos()
{
    
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //Android
    JniMethodInfo minfo;
    if(JniHelper::getStaticMethodInfo(minfo,
                                      "tw/com/b_a/EStory001/EStory001",
                                      "stopVideo",
                                      "()V"))
    {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
#endif
}