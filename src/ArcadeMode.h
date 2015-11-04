#ifndef ARCADE_H
#define ARCADE_H
#include <Box2D\Box2D.h>
#include "cocos2d.h"


using namespace cocos2d;



class GameTimer;
class HelloWorld;
class HelloView;
class HelloStarter;
class CupContactListener;
struct DebugSettings;
class GLESDebugDraw;

struct CupProfile {
	CupProfile() {
		_ball_num = 0;
	}
	int _ball_num;
};

class HelloView : public cocos2d::CCLayer {
public:
	HelloStarter * _engine;

public:
	static HelloView * viewCreate();
	bool initView();
	virtual void registerWithTouchDispatcher(void);
	void HelloView::draw();
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent * event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent * event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent * event);



	
};

class HelloStarter : public b2DestructionListener , public b2ContactListener {
	struct CAP
	{
		

		b2Body * body;
		b2Fixture * left;
		b2Fixture * right;
		b2EdgeShape * leftClose;
		b2EdgeShape * rightClose;
		b2EdgeShape * leftOpen;
		b2EdgeShape * rightOpen;
		bool open;
	};

	struct CUP
	{
		enum _action {
			up,
			down,
			left,
			right,
			out
		} action;

		b2Body * body;
		float transX;
		float transY;
		//b2Position iniPositon;
		float iniX;
		float iniY;

		b2Body * poly;
		CupProfile * pf;

		bool roll;
		//b2RevoluteJoint * ro;

	};

	
public:
	int ball_num;
	int gener_ball_num;
	int jumper;


	
	int32 _processStep;

	b2CircleShape _shape;
	b2PolygonShape _cupShape;
	b2BodyDef ball_def;
	int ball_left;
	int ball_right;


	b2World * _world;
	b2Vec2 * _gravity;
	b2Body * _mainBody;
	b2Body * BallArray[1000];
	b2MouseJoint * _mouseJoint;
	//b2BodyDef * _mainBodyDef;
	GLESDebugDraw  * _debugView;



	DebugSettings * _setting;
	CupContactListener * _contactListener;
	GameTimer * _timer;
	HelloWorld * _baseView;

	//caps
	b2Body * _platform;
	CAP _cap;

	//cups
	CUP * _cupArray[10];
	int _cupNum;
	int _cupGenerated;
	float _cup_speed;


	//levels and scores

	int _lvl;
	int _score;
public:

	HelloStarter();
	~HelloStarter();
	static HelloStarter * create() {
		return new HelloStarter();
	}
	void start();
	//b2DestructionListener virtual functions  **CallBacks
	void SayGoodbye(b2Joint * jt);
	void SayGoodbye(b2Fixture * ft);

	//b2ContactListener virtual functions   **CallBacks


	virtual void JointDestroyed(b2Joint* joint) { B2_NOT_USED(joint); }

	void setUpGame();
	void ballGo();
	void ballStop();
	
	virtual void Step(DebugSettings * dbset,float dt);
    virtual bool MouseDown(const b2Vec2& p);
    virtual void MouseUp(const b2Vec2& p);
    void MouseMove(const b2Vec2& p);

	void moveCup(CUP * cup);



	//virtual void BeginContact(b2Contact* contact){}
	//virtual void EndContact(b2Contact* contact) {}
 //   virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	//{
 //       B2_NOT_USED(contact);
 //       B2_NOT_USED(oldManifold);
 //   }
 //   virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
 //   {
 //       B2_NOT_USED(contact);
 //       B2_NOT_USED(impulse);
 //   }
	//void 


public:
	CUP * newCup(float x, float y) {
		CUP * cup = new CUP();
		
		if(x == 26 && y <= 87 && y > 10)
			cup->action = cup->down;
		else if(x == -26 && y >= 10 && y < 87)
			cup->action = cup->up;
		else if(y == 10 && x > -26 && x <= 26)
			cup->action = cup->left;
		else if(y == 87 && x >= -26 && x < 26)
			cup->action = cup->right;
		else {
			free(cup);
			return NULL;
		}

		b2Vec2 vec[4];
	
		vec[0] = b2Vec2(-4.5f, 5.0f);
		vec[1] = b2Vec2(-3.0f,-5.0f);
		vec[2] = b2Vec2(3.0f,-5.0f);
		vec[3] = b2Vec2(4.5f,5.0f);
		b2BodyDef df;
		df.type = b2_kinematicBody;
		df.position.Set(x,y);
		b2Body * body = _world->CreateBody(&df);
		cup->body = body;
		b2MassData md;
		md.center= b2Vec2(x,y);
		body->SetMassData(&md);
		b2EdgeShape shape;
		shape.Set(vec[0],vec[1]);
		body->CreateFixture(&shape,0.0f);
		shape.Set(vec[1],vec[2]);
		body->CreateFixture(&shape,0.0f);
		shape.Set(vec[2],vec[3]);
		body->CreateFixture(&shape,0.0f);
//		CUP * cup = new CUP();
		//cup->body = body;
		cup->iniX = x;
		cup->iniY = y;
		cup->transX = 0.0f;
		cup->transY = 0.0f;

		cup->roll = true;
		_cupShape.Set(vec, 4);
		
		b2BodyDef dff;
		dff.type = b2_kinematicBody;
		dff.position.Set(x,y);
		
		cup->poly = _world->CreateBody(&dff);
		b2Fixture * fx = cup->poly->CreateFixture(&_cupShape,0.0f);
		fx->SetUserData(new CupProfile());
		cup->pf = (CupProfile *) fx->GetUserData();
		fx->SetSensor(true);
		//b2Filter filter;
		//filter.maskBits = 0x0002;
		//filter.categoryBits = 0x0002;
		//fx->SetFilterData(filter);

		//b2RevoluteJointDef rdf;
		//rdf.bodyA = cup->poly;
		//rdf.bodyB = body;
		//rdf.collideConnected = false;
		//rdf.localAnchorA.Set(0.0f,0.0f);
		//rdf.localAnchorB.Set(0.0f,0.0f);
		//rdf.motorSpeed = 1.0f * b2_pi;

		//cup->ro = (b2RevoluteJoint *) _world->CreateJoint(&rdf);
		

		if( cup->action == cup->right) {
			cup->body->SetLinearVelocity(b2Vec2(10.0f,0.0f));
			cup->poly->SetLinearVelocity(b2Vec2(10.0f,0.0f));

		}
		return cup;
	}


	
	void setBaseView(void * view) {
		this->_baseView = (HelloWorld *)view;
	}
};

#endif