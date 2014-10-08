//
//  TouchSprite
//

#include "TouchSprite.h"

#define AnimationSpeed 1.0f/12.0f

using namespace cocos2d;

TouchSprite* TouchSprite::createBySpriteFrameName(const char *spName){
    TouchSprite *pobSprite = new TouchSprite();

    if (pobSprite && pobSprite->initWithSpriteFrameName(spName))
    {
        pobSprite->myInit();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    
    return NULL;
}
void TouchSprite::myInit(){
//    CCLOG("TouchSprite init");
    
    m_pListener = NULL;
    m_pfnSelector = NULL;
}

TouchSprite::~TouchSprite(){
//    CCLOG("~TouchSprite ");
    
    m_pListener = NULL;
    m_pfnSelector = NULL;
}



void TouchSprite::onEnter(){
    //因為CCMenu的priority是 -128
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -130, true);
    
    CCNode::onEnter();
}

void TouchSprite::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    CCNode::onExit();
}

bool TouchSprite::ccTouchBegan(CCTouch* touch, CCEvent* event){
//    
//    CCLOG("觸碰到 %d",this->getTag());
//    CCPoint tToW = this->convertTouchToNodeSpace(touch);
//    CCLOG("convertTouchToNodeSpace : %f , %f",tToW.x,tToW.y);
//    CCPoint touchLocation = touch->getLocationInView();
//    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
//    CCLOG("Touch Location : %f, %f",touchLocation.x, touchLocation.y);
//    CCPoint cToN = this->convertToNodeSpace(touchLocation);
//    CCLOG("convertToNodeSpace : %f , %f",cToN.x,cToN.y);
//    CCPoint cTow = this->convertToWorldSpace(touchLocation);
//    CCLOG("convertToWorldSpace : %f , %f",cTow.x,cTow.y);
    
    
    if (this->containsTouchLocation(touch)) {
        
        
        return true;
    }
    
    return false;
}

void TouchSprite::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    if (m_pListener && m_pfnSelector)
    {
        (m_pListener->*m_pfnSelector)(this);
    }
}

#pragma mark -




bool TouchSprite::containsTouchLocation(CCTouch *touch){
    
    CCPoint nodeLocation = this->convertTouchToNodeSpace(touch);
    
    CCRect thisRect = CCRectMake(0,0,getContentSize().width, getContentSize().height);

    bool isTouched = thisRect.containsPoint(nodeLocation);

    if (isTouched) {
        //取得圖片該點的RGBA 做判斷.

        //-----
        u_int8_t data[4];
        CCRenderTexture *renderTexture = CCRenderTexture::create(getContentSize().width, getContentSize().height);
        
        renderTexture->begin();

        this->draw();
        
        glReadPixels(nodeLocation.x, nodeLocation.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        renderTexture->end();
        
//        CCSprite *aaa = CCSprite::createWithTexture(renderTexture->getSprite()->getTexture());
//        aaa->setPosition(ccp(200, 300));
//        this->getParent()->addChild(aaa,50);
        
        renderTexture->release();
        
        int alpha = data[3];
        
        if (alpha < 85) {
            // alpha 小於 85 當做透明.
            //不處理點擊觸碰.
            
            return false;
        }
    }
    
    return isTouched;
}

void TouchSprite::addGray(CCSprite* sp)
{
    do
    {
        GLchar* pszFragSource =
        "#ifdef GL_ES \n \
        precision mediump float; \n \
#endif \n \
        uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
            // Convert to greyscale using NTSC weightings \n \
            vec4 col = texture2D(u_texture, v_texCoord); \n \
            float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114)); \n \
            gl_FragColor = vec4(grey, grey, grey, col.a); \n \
        }";
        CCGLProgram* pProgram = new CCGLProgram();
        pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pszFragSource);
        sp->setShaderProgram(pProgram);
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        sp->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        sp->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->link();
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
    } while (0);
}


void TouchSprite::removeGray(CCSprite* sp)
{
    do
    {
        CCGLProgram* pProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor);
        sp->setShaderProgram(pProgram);
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        sp->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
        sp->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->link();
        CHECK_GL_ERROR_DEBUG();
        
        sp->getShaderProgram()->updateUniforms();
        CHECK_GL_ERROR_DEBUG();
    } while (0);
}



void TouchSprite::setTarget(CCObject *rec, SEL_MenuHandler selector){
    m_pListener = rec;
    m_pfnSelector = selector;
}