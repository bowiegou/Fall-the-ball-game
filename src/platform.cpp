#include "platform.h"


Platform::Platform(void)
{

}


Platform::~Platform(void)
{

}



Platform * Platform::createWithTexture(CCTexture2D * texture){
	Platform * ball = new Platform();
	if(ball->initWithTexture(texture)){
		ball->autorelease();
		return ball;
	}
	ball->release();
	return NULL;
}

bool Platform::initWithTexture(CCTexture2D * txt) {
	this->p_state = sUngrabbed;
	return CCSprite::initWithTexture(txt);

}


void Platform::onEnter() {
	CCDirector * director = CCDirector::sharedDirector();
	director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();

}

void Platform::onExit() {
	CCDirector * director = CCDirector::sharedDirector();
	director->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}
bool Platform::ccTouchBegan(CCTouch* touch, CCEvent* event){
	if(p_state == sGrabbed) return false;
	p_state = sGrabbed;
	return true;
}
void Platform::ccTouchMoved(CCTouch* touch, CCEvent* event){
	if(p_state == sGrabbed) {
		CCPoint location = touch->getLocation();
		this->setPosition(ccp(location.x,getPositionY()));
	}
}
void Platform::ccTouchEnded(CCTouch* touch, CCEvent* event){
	p_state = sUngrabbed;
}
