#ifndef PLATFORM_H
#define PLATFORM_H

#include "cocos2d.h"

using namespace cocos2d;

typedef enum tagState 
{
    sGrabbed,
    sUngrabbed
} PlatformState; 

class Platform :
	public CCSprite, public CCTargetedTouchDelegate
{
	PlatformState p_state;

public:
	Platform(void);
	virtual ~Platform(void);

	CCRect rect();

	//bool createWithImage(const char * file);
	static Platform * createWithTexture(CCTexture2D * texture);
	bool Platform::initWithTexture(CCTexture2D * txt);
	virtual void onEnter();
	virtual void onExit();
    bool containsTouchLocation(CCTouch* touch);
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
};

#endif PLATFORM_H

