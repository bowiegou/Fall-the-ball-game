#ifndef CUP_CONTACT_H
#define CUP_CONTACT_H

#include "cocos2d.h"
#include <Box2D\Box2D.h>
//#include "HelloWorldScene.h"
#include "GameTimer.h"
#include "ArcadeMode.h"
class HelloStarter;
struct CupProfile;

using namespace cocos2d;
class CupContactListener : public b2ContactListener {

public:
	HelloStarter * _engine;
	//HelloWorld _baseView;

public:
	CupContactListener(HelloStarter * hl);
	~CupContactListener();
	static CupContactListener * create(HelloStarter * hl);
    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);

	void CupBeginContact(b2Fixture * fx);
	void CupEndContact(b2Fixture * fx);

public:
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
        B2_NOT_USED(contact);
        B2_NOT_USED(oldManifold);
    }
    virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
        B2_NOT_USED(contact);
        B2_NOT_USED(impulse);
    }
};

#endif