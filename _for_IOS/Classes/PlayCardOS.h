//
//  PlayCardOS.h
//  EStory001
//
//  Created by imac07 on 2014/8/4.
//
//

#ifndef __EStory001__PlayCardOS__
#define __EStory001__PlayCardOS__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//Android
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

USING_NS_CC;
USING_NS_CC_EXT;

class PlayCardOS : public CocosDenshion::SimpleAudioEngine
{
public:
    static PlayCardOS* createByMp3Name(const char *spName);
    static PlayCardOS* createStopMp3Name();
    void playos(const char* pszFilePath);
    void stopos();
};


#endif /* defined(__EStory001__PlayCardOS__) */
