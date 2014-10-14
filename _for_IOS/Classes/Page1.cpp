//
//  Page1.cpp
//  ebooktest
//
//  Created by imac07 on 2014/9/3.
//
//

#include "Page1.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;

#define PAGEPOINT ccp(384, 512)
#define BEFOREPAGEPOINT ccp(384, 700+1400)
#define NEXTPAGEPOINT ccp(384, 700-1400)
#define MINPAGE 0
#define TWORD "p%d_tw2.png"
#define CWORD "p%d_cn.png"
#define TSWORD "p%d_tw.png"
#define HorizontalBEFORE ccp(384-768, 700)
#define HorizontalNEXT ccp(384+768, 700)
#define HR fabsf(nowPage->getPositionX()-1152);
#define HL fabsf(nowPage->getPositionX()+384);
#define VN fabsf(nowPage->getPositionY()-1912);
#define VB fabsf(nowPage->getPositionY()+888);


CCScene* Page1::scene()
{
    CCScene *scene = CCScene::create();
    
    Page1 *layer = Page1::create();
    
    scene->addChild(layer);
    
    return scene;
}
bool Page1::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
	cache=CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("index.plist");
    
    
    
    for ( int n=0; n<=MAXPAGE; n++) {
        cache->addSpriteFramesWithFile(CCString::createWithFormat("Page%d.plist", n)->getCString());
        SimpleAudioEngine::sharedEngine()->preloadEffect(CCString::createWithFormat("Twosp%d.mp3", n)->getCString());
        SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(CCString::createWithFormat("BGM%d.mp3", n)->getCString());
       
    }
    switch (CCUserDefault::sharedUserDefault()->getIntegerForKey("Record_Language")) {
        case 0:
            wordStr=TSWORD;
            menuWordStr="set_bk_tw.png";
            offStr="set_btn_open.png";
            onStr="set_btn_close.png";
            VerticalStr="set_btn_vertical.png";
            HorizontalStr="set_btn_level.png";
            break;
            
        case 2:
            wordStr=TWORD;
            menuWordStr="set_bk_tw2.png";
            offStr="set_btn_open_tw.png";
            onStr="set_btn_close_tw.png";
            VerticalStr="set_btn_vertical_tw.png";
            HorizontalStr="set_btn_level_tw.png";
            break;
        default:
            wordStr=CWORD;
            menuWordStr="set_bk_cn.png";
            offStr="set_btn_open_cn.png";
            onStr="set_btn_close_cn.png";
            VerticalStr="set_btn_vertical_cn.png";
            HorizontalStr="set_btn_level_cn.png";
            break;
    }

    
    
    s = this->boundingBox().size;
    CCRect RectSize1 = CCRectMake(0, 0, 768, 1024);
    sceneSpr = CCSprite::create();
    sceneSpr->setTextureRect(RectSize1);
    sceneSpr->setOpacity(0);
    
    
    openMenu=false;
    isMove=false;
    playOSBool=true;
    touchBool=true;
    pageNum=0;
    
    
    
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCString::createWithFormat("BGM%d.mp3", pageNum)->getCString(), true);
    
    
    sceneSpr -> setPosition(ccp(s.width / 2, s.height / 2));
    addChild(sceneSpr);
    
    nowPage=CCSprite::createWithSpriteFrameName(CCString::createWithFormat("p%d.png", pageNum)->getCString());
    nowPage->cocos2d::CCNode::setPosition(PAGEPOINT);
    sceneSpr->addChild(nowPage);
    nowPageWord=CCSprite::createWithSpriteFrameName(CCString::createWithFormat(wordStr, pageNum)->getCString());
    nowPageWord->setAnchorPoint(ccp(0, 0));
    nowPage->addChild(nowPageWord);
    
    
    beforePage=CCSprite::createWithSpriteFrameName(CCString::createWithFormat("p%d.png", pageNum+1)->getCString());
    beforePage->setPosition(BEFOREPAGEPOINT);
    nowPage->addChild(beforePage);
    beforePageWord=CCSprite::createWithSpriteFrameName(CCString::createWithFormat(wordStr, pageNum+1)->getCString());
    beforePageWord->setAnchorPoint(ccp(0, 0));
    beforePage->addChild(beforePageWord);

    nextPage=CCSprite::createWithSpriteFrameName(CCString::createWithFormat("p%d.png", pageNum+1)->getCString());
    nextPage->setPosition(NEXTPAGEPOINT);
    nowPage->addChild(nextPage);
    nextPageWord=CCSprite::createWithSpriteFrameName(CCString::createWithFormat(wordStr, pageNum+1)->getCString());
    nextPageWord->setAnchorPoint(ccp(0, 0));
    nextPage->addChild(nextPageWord);
    
    upLine=CCSprite::createWithSpriteFrameName("line.png");
    upLine->cocos2d::CCNode::setPosition(384, 1400);
    nowPage->addChild(upLine);
    
    downLine=CCSprite::createWithSpriteFrameName("line.png");
    downLine->cocos2d::CCNode::setPosition(384, 0);
    nowPage->addChild(downLine);
    
    CCSprite *upLine2=CCSprite::createWithSpriteFrameName("line.png");
    upLine2->cocos2d::CCNode::setPosition(384, 1400+1400);
    nowPage->addChild(upLine2);
    
    CCSprite *downLine2=CCSprite::createWithSpriteFrameName("line.png");
    downLine2->cocos2d::CCNode::setPosition(384, 0-1400);
    nowPage->addChild(downLine2);
    
    
    menuSpr=TouchSprite::createBySpriteFrameName("set_bk.png");
    menuSpr->cocos2d::CCNode::setPosition(384, 1600);
    sceneSpr->addChild(menuSpr);
    menuWord=CCSprite::createWithSpriteFrameName(menuWordStr);
    menuWord->setAnchorPoint(ccp(0, 0));
    menuSpr->addChild(menuWord);
    
    
    EffectON=TouchSprite::createBySpriteFrameName(onStr);
    EffectON->cocos2d::CCNode::setPosition(381, 605);
    menuSpr->addChild(EffectON);
    EffectON->setTarget(this, menu_selector(Page1::EffectONFuction));
    EffectON->addGray(EffectON);
    EffectOFF=TouchSprite::createBySpriteFrameName(offStr);
    EffectOFF->cocos2d::CCNode::setPosition(523, 605);
    menuSpr->addChild(EffectOFF);
    EffectOFF->setTarget(this, menu_selector(Page1::EffectOFFFuction));
    EffectOFF->setTag(1);
    MusicON=TouchSprite::createBySpriteFrameName(onStr);
    MusicON->cocos2d::CCNode::setPosition(381, 502);
    menuSpr->addChild(MusicON);
    MusicON->addGray(MusicON);
    MusicON->setTarget(this, menu_selector(Page1::MusicONFuction));
    
    MusicOFF=TouchSprite::createBySpriteFrameName(offStr);
    MusicOFF->cocos2d::CCNode::setPosition(523, 502);
    menuSpr->addChild(MusicOFF);
    MusicOFF->setTarget(this, menu_selector(Page1::MusicOFFFuction));
    MusicOFF->setTag(1);
    HorizontalSpr=TouchSprite::createBySpriteFrameName(HorizontalStr);
    HorizontalSpr->cocos2d::CCNode::setPosition(381, 401);
    menuSpr->addChild(HorizontalSpr);
    HorizontalSpr->addGray(HorizontalSpr);
    HorizontalSpr->setTarget(this, menu_selector(Page1::HorizontalFuction));

    VerticalSpr=TouchSprite::createBySpriteFrameName(VerticalStr);
    VerticalSpr->cocos2d::CCNode::setPosition(523, 401);
    menuSpr->addChild(VerticalSpr);
    VerticalSpr->setTarget(this, menu_selector(Page1::VerticalFuction));
    VerticalSpr->setTag(1);
    
    Tbtn=TouchSprite::createBySpriteFrameName("set_btn_tw1.png");
    Tbtn->cocos2d::CCNode::setPosition(450, 285);
    menuSpr->addChild(Tbtn);
    Tbtn->setTarget(this, menu_selector(Page1::TbtnFuction));
    Tbtn->addGray(Tbtn);
    
    
    Cbtn=TouchSprite::createBySpriteFrameName("set_btn_cn3.png");
    Cbtn->cocos2d::CCNode::setPosition(450, 195);
    menuSpr->addChild(Cbtn);
    Cbtn->setTarget(this, menu_selector(Page1::CbtnFuction));
    Cbtn->addGray(Cbtn);
    
    TSbtn=TouchSprite::createBySpriteFrameName("set_btn_tw_tw2.png");
    TSbtn->cocos2d::CCNode::setPosition(450, 105);
    menuSpr->addChild(TSbtn);
    TSbtn->setTarget(this, menu_selector(Page1::TsbtnFuction));
    TSbtn->addGray(TSbtn);
    switch (CCUserDefault::sharedUserDefault()->getIntegerForKey("Record_Language")) {
        case 0:
            TSbtn->removeGray(TSbtn);
            break;
        case 2:
            Tbtn->removeGray(Tbtn);
            break;
        default:
            Cbtn->removeGray(Cbtn);
            break;
    }
    
    
    CCMenuItemSprite *menuItem=CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("tab0001.png"), NULL, this, menu_selector(Page1::menuFuction));
    menu=CCMenu::create(menuItem,NULL);
    menu->setPosition(s.width-47, s.height-56.5);
 
    
    addChild(menu);
    menu->setTag(1);
    
    
    CCMenuItemSprite *topItem=CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("tab0002.png"), NULL, this, menu_selector(Page1::topFuction));
    topmenu=CCMenu::create(topItem,NULL);
    float y=(1400-s.height)/2;
//    topmenu->setPosition(s.width*0.5,s.height*0.06);
    topmenu->setPosition(384,0+y+62.5);
    nowPage->addChild(topmenu);
    topmenu->setVisible(false);
    
   
    
    
    
    if (EffectOFF->getTag()==2) {
        EffectONFuction();
    }
    if (MusicOFF->getTag()==2) {
        MusicONFuction();
    }
    if (VerticalSpr->getTag()==2) {
        HorizontalFuction();
    }
    
    playOS();
    
    CCRect RectSizeb = CCRectMake(0, 0, 768, 1400);
    blackSpr = CCSprite::create();
    blackSpr->setTextureRect(RectSizeb);
    blackSpr->setOpacity(0);
    blackSpr->setColor(ccBLACK);
    blackSpr->cocos2d::CCNode::setPosition(s.width/2, s.height/2);
    addChild(blackSpr);
    return true;
}
void Page1::playTWOS()
{
    PlayCardOS::createByMp3Name(CCString::createWithFormat("Twosp%d.mp3", pageNum)->getCString());
}
void Page1::playCNOS()
{
    PlayCardOS::createByMp3Name(CCString::createWithFormat("Cnosp%d.mp3", pageNum)->getCString());
}
void Page1::playOS()
{
   
    if (EffectOFF->getTag()==1) {
        playOSBool=true;
        if (Cbtn->getTag()==1)
        {
             std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(CCString::createWithFormat("Cnosp%d.mp3", pageNum)->getCString());
            if (fullPath.length()<=1)
            {
                playTWOS();
            }
            else
            {
                playCNOS();
            }
        }
        else
        {
            playTWOS();
        }
    }
}

void Page1::topFuction()
{
    PlayCardOS::createStopMp3Name();
    pageNum=0;
    touchBool=false;
    menu->setVisible(false);
    topmenu->setVisible(false);
    CCFadeIn *fadIn=CCFadeIn::create(0.5);
    CCFadeOut *fadOut=CCFadeOut::create(0.5);
    CCCallFunc *call=CCCallFunc::create(this, callfunc_selector(Page1::changePage));
    blackSpr->runAction(CCSequence::create(fadIn,fadOut,call,NULL));
    scheduleOnce(schedule_selector(Page1::topFuction2), 0.5);
    
   
}
void Page1::topFuction2()
{
    
    touchBool=true;
    menu->setVisible(true);
    beforePage->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("p%d.png", 0)->getCString()));
    beforePageWord->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(wordStr, 0)->getCString()));
    
    nowPage->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("p%d.png", pageNum)->getCString()));
    nowPageWord->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(wordStr, pageNum)->getCString()));
    
    nextPage->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("p%d.png", pageNum+1)->getCString()));
    
    nextPageWord->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(wordStr, pageNum+1)->getCString()));
    
}
void Page1::menuFuction()
{
//    menu->setEnabled(false);
    menuSpr->stopAllActions();
    if (menu->getTag()==1) {
        menuSpr->runAction(CCMoveTo::create(0.3, ccp(384, 512)));
        menu->setTag(2);
        openMenu=true;
        PlayCardOS::createStopMp3Name();
    }
    else
    {
        menuSpr->runAction(CCMoveTo::create(0.3, ccp(384, 1600)));
        menu->setTag(1);
        openMenu=false;
        playOS();
    }
//    scheduleOnce(schedule_selector(Page1::openMenuFuction), 1);
}
void Page1::openMenuFuction()
{
    menu->setEnabled(true);
}
void Page1::EffectOFFFuction()
{
    EffectOFF->setTag(1);
    EffectOFF->removeGray(EffectOFF);
    EffectON->addGray(EffectON);
    CCUserDefault::sharedUserDefault()->setBoolForKey("EffectB", true);
}
void Page1::MusicOFFFuction()
{
    MusicOFF->setTag(1);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(100);
    MusicOFF->removeGray(MusicOFF);
    MusicON->addGray(MusicON);
    CCUserDefault::sharedUserDefault()->setBoolForKey("MusicB", true);
    
}
void Page1::EffectONFuction()
{
    
    EffectOFF->setTag(2);
    EffectON->removeGray(EffectON);
    EffectOFF->addGray(EffectOFF);
    CCUserDefault::sharedUserDefault()->setBoolForKey("EffectB", false);
}
void Page1::MusicONFuction()
{
    MusicOFF->setTag(2);
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
    MusicON->removeGray(MusicON);
    MusicOFF->addGray(MusicOFF);
    CCUserDefault::sharedUserDefault()->setBoolForKey("MusicB", false);
}

void Page1::onEnter()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
    CCNode::onEnter();
}
void Page1::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}
bool Page1::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    if (openMenu) {
        menu->setTag(2);
        menuFuction();
        
        return false;
    }
    
    if (touchBool) {
        return true;
    }
    
    return false;
}
void Page1::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
    CCPoint startLocation = touch->getLocationInView();
//    startLocation = CCDirector::sharedDirector()->convertToGL(startLocation);
    
    CCPoint endLocation = touch->getPreviousLocationInView();
//    endLocation = CCDirector::sharedDirector()->convertToGL(endLocation);
    if (VerticalSpr->getTag()==1) {
        float y=endLocation.y-startLocation.y;
        
        if (fabs(y)>1) {
            isMove=true;
        }
        if (pageNum==MINPAGE) {
            if (y<0) {
                return;
            }
        }
        if (pageNum==MAXPAGE) {
            if (y>0) {
                return;
            }
        }
        
        nowPage->runAction(CCMoveBy::create(0.1, ccp(0, y)));
    }
    else
    {
        float x=startLocation.x-endLocation.x;
        
        if (fabs(x)>1) {
            isMove=true;
        }
        if (pageNum==MINPAGE) {
            if (x>0) {
                return;
            }
        }
        if (pageNum==MAXPAGE) {
            if (x<0) {
                return;
            }
        }
        
        nowPage->runAction(CCMoveBy::create(0.1, ccp(x, 0)));
    }
    
}
void Page1::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    
    nowPage->stopAllActions();
    if (isMove) {
        changePageFuction();
    }
    else
    {
        if (playOSBool) {
            PlayCardOS::createStopMp3Name();
            playOSBool=false;
        }
        else
        {
            
            playOS();
        }
    }
    isMove=false;
}
void Page1::changePageFuction()
{
    
    if (VerticalSpr->getTag()==1) {
        if (nowPage->getPositionY()>768) {
            nextPageFuction();
        }
        else if (nowPage->getPositionY()<256)
        {
            beforePageFuction();
        }
        else
        {
            
            nowPage->runAction(CCMoveTo::create(0.5, PAGEPOINT));
        }
    }
    else
    {
        if (nowPage->getPositionX()<192+50) {
            nextPageFuction();
        }
        else if (nowPage->getPositionX()>576-50)
        {
            beforePageFuction();
        }
        else
        {
            
            nowPage->runAction(CCMoveTo::create(0.5, PAGEPOINT));
        }
    }
}
void Page1::nextPageFuction()
{
    touchBool=false;
    pageNum++;
    if (pageNum==MAXPAGE)
    {
        pageNum=MAXPAGE;
    }
    
    
  
    float d;
    float ss;
    
    int moveX;
    int moveY;
    if (VerticalSpr->getTag()==1) {
        d=VN
        ss=d/1400;
        moveX=384;
        moveY=512+1400;
        
    }
    else
    {
        d=HL;
        ss=d/768;
        moveX=384-768;
        moveY=512;
    }
    sec=ss*0.6;
    PlayCardOS::createStopMp3Name();
    playOSBool=true;
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCMoveTo *move=CCMoveTo::create(sec, ccp(moveX,moveY));
    CCCallFunc *call=CCCallFunc::create(this, callfunc_selector(Page1::changePage));
    nowPage->runAction(CCSequence::create(move,call,NULL));
    
    
}
void Page1::beforePageFuction()
{
    
    float d;
    float ss;
    int moveX;
    int moveY;
    if (VerticalSpr->getTag()==1) {
        d=VB
        ss=d/1400;
        moveX=384;
        moveY=512-1400;
    }
    else
    {
        d=HR;
        ss=d/768;
        moveX=384+768;
        moveY=512;
    }

    
    touchBool=false;
    playOSBool=true;
    PlayCardOS::createStopMp3Name();
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    pageNum--;
    if (pageNum<1) {
        pageNum=0;
    }
    CCMoveTo *move=CCMoveTo::create(sec, ccp(moveX, moveY));
    CCCallFunc *call=CCCallFunc::create(this, callfunc_selector(Page1::changePage));
    nowPage->runAction(CCSequence::create(move,call,NULL));
    
}
void Page1::changePage()
{
    
    scheduleOnce(schedule_selector(Page1::changePage2), 0.1);
}
void Page1::changePage2()
{
    if (pageNum==MAXPAGE) {
        topmenu->setVisible(true);
    }
    else
    {
        topmenu->setVisible(false);
    }
    touchBool=true;
    int beforeNum=pageNum-1;
    
    if (beforeNum<=0) {
        beforeNum=0;
    }
    
    int nextNum=pageNum+1;
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCString::createWithFormat("BGM%d.mp3", pageNum)->getCString(), true);
    if (openMenu==false) {
        playOS();
    }
    
    if (nextNum>MAXPAGE)
    {
        nextNum=MAXPAGE;
    }
    beforePage->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("p%d.png", beforeNum)->getCString()));
    beforePageWord->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(wordStr, beforeNum)->getCString()));
    
    nowPage->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("p%d.png", pageNum)->getCString()));
    nowPageWord->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(wordStr, pageNum)->getCString()));
    
    nextPage->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat("p%d.png", nextNum)->getCString()));
 
    nextPageWord->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(CCString::createWithFormat(wordStr, nextNum)->getCString()));
    nowPage->cocos2d::CCNode::setPosition(PAGEPOINT);

}
void Page1::menuChang()
{
    menuWord->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(menuWordStr));
    EffectOFF->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(offStr));
    MusicOFF->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(offStr));
    EffectON->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(onStr));
    MusicON->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(onStr));
    VerticalSpr->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(VerticalStr));
    HorizontalSpr->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(HorizontalStr));
    if (EffectOFF->getTag()==1) {
        EffectON->addGray(EffectON);
        EffectOFF->removeGray(EffectOFF);
    }
    else
    {
        EffectON->removeGray(EffectON);
        EffectOFF->addGray(EffectOFF);
    }
    
    
    if (MusicOFF->getTag()==1) {
        MusicON->addGray(MusicON);
        MusicOFF->removeGray(MusicOFF);
    }
    else
    {
        MusicON->removeGray(MusicON);
        MusicOFF->addGray(MusicOFF);
    }
    if (VerticalSpr->getTag()==1) {
        VerticalSpr->removeGray(VerticalSpr);
        HorizontalSpr->addGray(HorizontalSpr);
    }
    else
    {
        VerticalSpr->addGray(VerticalSpr);
        HorizontalSpr->removeGray(HorizontalSpr);
    }
}
void Page1::TbtnFuction()
{
    menuFuction();
    wordStr=TWORD;
    menuWordStr="set_bk_tw2.png";
    offStr="set_btn_open_tw.png";
    onStr="set_btn_close_tw.png";
    VerticalStr="set_btn_vertical_tw.png";
    HorizontalStr="set_btn_level_tw.png";
    PlayCardOS::createStopMp3Name();
//    menu->setTag(1);
    changePage();
    
    Tbtn->removeGray(Tbtn);
    Cbtn->addGray(Cbtn);
    TSbtn->addGray(TSbtn);
    
    Cbtn->setTag(2);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Record_Language", 2);
    menuChang();
    
}
void Page1::CbtnFuction()
{
    menuFuction();
    wordStr=CWORD;
    menuWordStr="set_bk_cn.png";
    offStr="set_btn_open_cn.png";
    onStr="set_btn_close_cn.png";
    VerticalStr="set_btn_vertical_cn.png";
    HorizontalStr="set_btn_level_cn.png";
    PlayCardOS::createStopMp3Name();
//    menu->setTag(2);
    changePage();
    Cbtn->setTag(1);
    Tbtn->addGray(Tbtn);
    Cbtn->removeGray(Cbtn);
    TSbtn->addGray(TSbtn);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Record_Language", 1);
    
    menuChang();
}
void Page1::TsbtnFuction()
{
    menuFuction();
    wordStr=TSWORD;
    menuWordStr="set_bk_tw.png";
    offStr="set_btn_open.png";
    onStr="set_btn_close.png";
    VerticalStr="set_btn_vertical.png";
    HorizontalStr="set_btn_level.png";
    PlayCardOS::createStopMp3Name();
//    menu->setTag(2);
    changePage();
    Cbtn->setTag(2);
    
    Tbtn->addGray(Tbtn);
    Cbtn->addGray(Cbtn);
    TSbtn->removeGray(TSbtn);
   CCUserDefault::sharedUserDefault()->setIntegerForKey("Record_Language", 0);
    
    menuChang();
}
void Page1::VerticalFuction()
{
    upLine->setOpacity(255);
    downLine->setOpacity(255);
    
    beforePage->setPosition(BEFOREPAGEPOINT);
    nextPage->setPosition(NEXTPAGEPOINT);
   
    VerticalSpr->removeGray(VerticalSpr);
    HorizontalSpr->addGray(HorizontalSpr);
    VerticalSpr->setTag(1);
    CCUserDefault::sharedUserDefault()->setBoolForKey("VerticalB", true);
}
void Page1::HorizontalFuction()
{
    upLine->setOpacity(0);
    downLine->setOpacity(0);
    
    beforePage->setPosition(HorizontalBEFORE);
    nextPage->setPosition(HorizontalNEXT);
    
    VerticalSpr->addGray(VerticalSpr);
    HorizontalSpr->removeGray(HorizontalSpr);
    VerticalSpr->setTag(2);
    CCUserDefault::sharedUserDefault()->setBoolForKey("VerticalB", false);
}

void Page1::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}