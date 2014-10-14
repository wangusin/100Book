//
//  Page1.h
//  ebooktest
//
//  Created by imac07 on 2014/9/3.
//
//

#ifndef __ebooktest__Page1__
#define __ebooktest__Page1__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "PlayCardOS.h"
#include "TouchSprite.h"
#include "SetPageNum.h"
#include "CCFileUtils.h"
USING_NS_CC;
USING_NS_CC_EXT;
class Page1 : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(Page1);
    
	CCSpriteFrameCache *cache;
    CCSize s;
	CCSprite *backGround;
	CCSprite *sceneSpr;
    int pageNum;
    float sec;
    CCSprite *nowPage;
    CCSprite *beforePage;
    CCSprite *nextPage;
    
    
    CCSprite *nowPageWord;
    CCSprite *beforePageWord;
    CCSprite *nextPageWord;
    
    TouchSprite *menuSpr;
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch* touch,CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    
    void openMenuFuction();
    void addPagePlist();
    void changePageFuction();
    void changePage2();
    void changePage();
    
    void nextPageFuction();
    void beforePageFuction();
    
    bool touchBool;
    bool isMove;
    bool playOSBool;
    
    TouchSprite *EffectOFF;
    TouchSprite *MusicOFF;
    TouchSprite *EffectON;
    TouchSprite *MusicON;
    TouchSprite *VerticalSpr;
    TouchSprite *HorizontalSpr;
    TouchSprite *Tbtn;
    TouchSprite *Cbtn;
    TouchSprite *TSbtn;
    
    void playTWOS();
    void playCNOS();
    
    void EffectOFFFuction();
    void MusicOFFFuction();
    void EffectONFuction();
    void MusicONFuction();
    
    void menuFuction();
    
    void VerticalFuction();
    void HorizontalFuction();
    void TbtnFuction();
    void CbtnFuction();
    void TsbtnFuction();
    CCSprite *menuWord;
    
    CCMenu *menu;
    
    
    bool openMenu;
    
    const char *wordStr;
    const char *menuWordStr;
    
    
    const char *offStr;
    const char *onStr;
    const char *tStr;
    const char *cffStr;
    const char *tsffStr;
    
    const char *VerticalStr;
    const char *HorizontalStr;
    CCSprite *upLine;
    CCSprite *downLine;
    void topFuction();
    void topFuction2();
    CCMenu *topmenu;
    void menuChang();
   
    void playOS();
    CCSprite *blackSpr;
};
#endif /* defined(__ebooktest__Page1__) */
