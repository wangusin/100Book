//
//  TouchSprite
//
//  CCSprite做觸碰判斷 , 點到非透明處才有作用
//

#ifndef __Cinderella_X__TouchSprite__
#define __Cinderella_X__TouchSprite__

#include "cocos2d.h"

using namespace cocos2d;

class TouchSprite : public CCSprite ,public CCTouchDelegate
{

public:
    // === create Function ===
    static TouchSprite* createBySpriteFrameName(const char *spName);
    
    void myInit();
    virtual ~TouchSprite();
    
    //======
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

    
    static void addGray(CCSprite* sp);
    static void removeGray(CCSprite* sp);
    
    //----
    // 檢查點擊是否在sprite範圍內.
    bool containsTouchLocation(CCTouch *touch);

    // 設定觸碰判斷通過時時要執行的callback    
    void setTarget(CCObject *rec, SEL_MenuHandler selector);
    
    //===

protected:
    CCObject*       m_pListener;
    SEL_MenuHandler    m_pfnSelector;
    
};

#endif /* defined(__Cinderella_X__TouchSprite__) */
