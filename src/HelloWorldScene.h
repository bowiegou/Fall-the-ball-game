#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <Box2D\Box2D.h>
#include "extended\GLES-Render.h"


using namespace cocos2d;

class GameTimer;
class HelloWorld;
class HelloView;
class HelloStarter;
class CupContactListener;


struct DebugSettings
{
    DebugSettings() :
		debug(true),
        viewCenter(0.0f, 20.0f),
        hz(60.0f),
        velocityIterations(10),
        positionIterations(10),
        drawShapes(1),
        drawJoints(1),
        drawAABBs(0),
        drawPairs(0),
        drawContactPoints(0),
        drawContactNormals(0),
        drawContactForces(0),
        drawFrictionForces(0),
        drawCOMs(0),
        drawStats(0),
        drawProfile(0),
        enableWarmStarting(0),
        enableContinuous(1),
        enableSubStepping(0),
        pause(0),
        singleStep(0)
        {}

	bool debug;
    b2Vec2 viewCenter;
    float32 hz;
    int32 velocityIterations;
    int32 positionIterations;
    int32 drawShapes;
    int32 drawJoints;
    int32 drawAABBs;
    int32 drawPairs;
    int32 drawContactPoints;
    int32 drawContactNormals;
    int32 drawContactForces;
    int32 drawFrictionForces;
    int32 drawCOMs;
    int32 drawStats;
    int32 drawProfile;
    int32 enableWarmStarting;
    int32 enableContinuous;
    int32 enableSubStepping;
    int32 pause;
    int32 singleStep;
};



class HelloWorld : public cocos2d::CCLayer
{
private:
	HelloStarter * st;
	HelloView * hw;
	GameTimer * _timer;
	char score[200];
	cocos2d::CCRect * visiableRect;

	CCLabelTTF * _scoreBoard;


public:
	void setStep(HelloStarter * h);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	

	void Step(float dt);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	virtual void registerWithTouchDispatcher(void);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent * event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent * event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent * event);
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
	void scoreCallBack(char * str);
	void scoreCallBack(unsigned int str);
	//void setScore();
	cocos2d::CCRect * getVisiableRect();

	

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
