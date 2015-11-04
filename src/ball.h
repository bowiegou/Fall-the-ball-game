#ifndef BALL_H
#define BALL_H

#include "cocos2d.h"
#include <Box2D/Box2D.h>

using namespace cocos2d;

typedef struct BallDef 
{
    CCPoint velocity;
	CCSize size;
	CCPoint position;
} ballDef; 

class Ball : public CCSprite
{
	ballDef b_def;

public:
	Ball(void);
	virtual ~Ball(void);

	//CCRect rect();

	//bool createWithImage(const char * file);
	static Ball * Ball::createWithTexture(CCTexture2D * txt);
	virtual void onEnter();
	virtual void onExit();


	void move(float dt);
    //bool containsTouchLocation(CCTouch* touch);
    //virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    //virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    //virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);


public:
    void setVelocity(CCPoint velocity){b_def.velocity = velocity;}
	BallDef * getBallDef() { return &b_def;}

};

#endif BALL_H

