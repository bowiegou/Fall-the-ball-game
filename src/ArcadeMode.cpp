#include "ArcadeMode.h"
#include "HelloWorldScene.h"
#include "ContactListener.h"
#include "GameTimer.h"
#include "query.h"
#define random(x) (rand()%(x-1) + 1)

USING_NS_CC;


////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
//
// ** HelloView
// Holds the engine and debugView of engine
//
//
//
//


HelloView * HelloView::viewCreate() {
	HelloView * hw = new HelloView();
	hw->initView();
	hw->autorelease();
	return hw;
}
bool HelloView::initView() {
	setTouchEnabled(true);
	CCLayer::init();
	return true;
}
void HelloView::draw()
{
    CCLayer::draw();

	 ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	  kmGLPushMatrix();

	(_engine->_world)->DrawDebugData();

    kmGLPopMatrix();

    CHECK_GL_ERROR_DEBUG();
}
bool HelloView::ccTouchBegan(CCTouch* touch, CCEvent * event){
	CCPoint touchLocation = touch->getLocation();    

    CCPoint nodePosition = convertToNodeSpace( touchLocation );
	//CCLOG("pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);

	return _engine->MouseDown(b2Vec2(nodePosition.x,nodePosition.y)); 
}
void HelloView::ccTouchMoved(CCTouch* touch, CCEvent * event){
	CCPoint touchLocation = touch->getLocation();    
    CCPoint nodePosition = convertToNodeSpace( touchLocation );
    
    _engine->MouseMove(b2Vec2(nodePosition.x,nodePosition.y));   
}
void HelloView::ccTouchEnded(CCTouch* touch, CCEvent * event){
    CCPoint touchLocation = touch->getLocation();    
    CCPoint nodePosition = convertToNodeSpace( touchLocation );
    
    _engine->MouseUp(b2Vec2(nodePosition.x,nodePosition.y));
}
void HelloView::registerWithTouchDispatcher(){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}


////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
//
// ** HelloStarter
// the game physical engine
//
//
//
//


HelloStarter::HelloStarter() {
	//this->_baseView = hw;
	gener_ball_num = 120;
	_processStep = 0;
	ball_num = 0;
	jumper = 1;
	_shape.m_radius = 1.0f;

	ball_left = 269;
	ball_right = 539;


	_score = 0;

	_cap.rightClose = new b2EdgeShape();
	_cap.rightOpen = new b2EdgeShape();
	_cap.leftClose = new b2EdgeShape();
	_cap.leftOpen = new b2EdgeShape();
}
HelloStarter::~HelloStarter() {
}

void HelloStarter::SayGoodbye(b2Joint * bt) {

    if (_mouseJoint == bt)
    {
        _mouseJoint = NULL;
    }
    else
    {
        JointDestroyed(bt);
    }

}
void HelloStarter::SayGoodbye(b2Fixture * ft) {
}
//初始化引擎
void HelloStarter::start() {
	///create world and set gravity
	_debugView = new GLESDebugDraw();
	_mouseJoint = NULL;
	_gravity = new b2Vec2();
	_gravity->Set(0.0f,-50.0f);
	_world = new b2World(*_gravity);
	_setting = new DebugSettings();
	
	_contactListener = CupContactListener::create(this);
	///settings
	_world->SetDebugDraw(_debugView);
	_world->SetDestructionListener(this);
	_world->SetContactListener(_contactListener);

	b2BodyDef df;
	_mainBody = _world->CreateBody(&df);

	//_debugView.DrawString(5,5,"sjdlfjlsjdfjklsjdklfjsljdfkl");
	setUpGame();



	//this->schedule(schedule_selector
}

void HelloStarter::setUpGame(){

	b2BodyDef bdf;
	b2Body * ground = _world->CreateBody(&bdf);

	//Setting up boundary
	b2EdgeShape shapel;
    shapel.Set(b2Vec2(-32.0f, 0.0f), b2Vec2(32.0f, 0.0f));
    b2Fixture * groundFix = ground->CreateFixture(&shapel, 0.0f);
	shapel.Set(b2Vec2(-32.0f, 96.0f), b2Vec2(32.0f, 96.0f));
    ground->CreateFixture(&shapel, 0.0f);
	//shapel.Set(b2Vec2(-32.0f, 96.0f), b2Vec2(-32.0f, 0.0f));
	//ground->CreateFixture(&shapel, 0.0f);
	//shapel.Set(b2Vec2(32.0f, 96.0f), b2Vec2(32.0f, 0.0f));
	//ground->CreateFixture(&shapel, 0.0f);
	//setting up game table
	//setting up ball stage


	_platform = _world->CreateBody(&bdf);

	shapel.Set(b2Vec2(6.5f, 46.0f), b2Vec2(20.0f, 48.0f));
	_platform->CreateFixture(&shapel, 0.0f);
	shapel.Set(b2Vec2(-6.5f, 46.0f), b2Vec2(-20.0f, 48.0f));
	_platform->CreateFixture(&shapel, 0.0f);
	shapel.Set(b2Vec2(-6.5f, 46.0f), b2Vec2(-3.0f, 40.0f));
	_platform->CreateFixture(&shapel, 0.0f);
	shapel.Set(b2Vec2(6.5f, 46.0f), b2Vec2(3.0f, 40.0f));
	_platform->CreateFixture(&shapel, 0.0f);
	shapel.Set(b2Vec2(20.0f, 80.0f), b2Vec2(20.0f, 48.0f));
	_platform->CreateFixture(&shapel, 0.0f);
	shapel.Set(b2Vec2(-20.0f, 80.0f), b2Vec2(-20.0f, 48.0f));
	_platform->CreateFixture(&shapel, 0.0f);

	shapel.Set(b2Vec2(20.0f, 80.0f), b2Vec2(11.9f, 80.0f));
	_platform->CreateFixture(&shapel, 0.0f);
	shapel.Set(b2Vec2(-20.0f, 80.0f), b2Vec2(-11.9f, 80.0f));
	_platform->CreateFixture(&shapel, 0.0f);
	shapel.Set(b2Vec2(11.9f, 60.0f), b2Vec2(11.9f, 80.0f));
	_platform->CreateFixture(&shapel, 0.0f);
	shapel.Set(b2Vec2(-11.9f, 60.0f), b2Vec2(-11.9f, 80.0f));
	_platform->CreateFixture(&shapel, 0.0f);



	//cap
	_cap.body = _world->CreateBody(&bdf);

	_cap.leftOpen->Set(b2Vec2(-3.0f, 37.0f), b2Vec2(-3.0f, 40.0f));
	_cap.rightClose->Set(b2Vec2(0.0f, 40.0f), b2Vec2(3.0f, 40.0f));
	_cap.rightOpen->Set(b2Vec2(3.0f, 37.0f), b2Vec2(3.0f, 40.0f));
	_cap.leftClose->Set(b2Vec2(0.0f, 40.0f), b2Vec2(-3.0f, 40.0f));
	
	
	_cap.right = _cap.body->CreateFixture(_cap.rightClose,0.0f);
	shapel.Set(b2Vec2(0.0f, 43.0f), b2Vec2(-3.0f, 43.0f));
	_cap.left = _cap.body->CreateFixture(_cap.leftClose,0.0f);
	_cap.open = false;


	ball_def.allowSleep = true;
	ball_def.type = b2_dynamicBody;
	ball_def.gravityScale = 0.0f;
	ball_def.fixedRotation = false;


	//cups
	//_cupArray[0] = newCup(0, 10);
	_cup_speed = 15.0f;
	_cupNum = 7;
	_cupGenerated = 0;
	//_cupArray[1] = newCup(-25, 10);

	//_cupArray[2] = newCup( 25, 10);

	//_cupArray[3] = newCup(26, 34);

	//_cupArray[4] = newCup(26, 59);
	//balls

	/*b2PolygonShape ps;
	ps.SetAsBox(1.0,1.0);*/
	for(int c = -1; c < 2; c= 2 + c){
		float yPix = 80.0 - 1.0;
		for(int col = 0; col < 10; col++) {
			float xPix = (20.0 - 1.0) * c ;
			for(int row = 0; row < 4; row++){
				ball_def.position.Set(xPix,yPix);
				xPix -= 2.01 * c;
				b2Body * ballBody = _world->CreateBody(&ball_def);
				b2MassData ns;
				ns.mass = 10000.0f;
				ns.center = b2Vec2_zero;
				ns.I = 2.0f;
				//ballBody->SetBullet(true);
				ballBody->SetMassData(&ns);
				BallArray[ball_num++] = ballBody;
				//ballBody->SetAwake(false);
				b2Fixture * fx = ballBody->CreateFixture(&_shape,0.5f);
				fx->SetRestitution(0.3f);
				//ball_num;
			}
			yPix -= 2.1f ;
		}
	}


	ball_left = 39 ;
	ball_right = 79;


	
	//cup->SetTransform(b2Vec2(0.0f, 0.0f),0.0f);


	//CupsArray[0] = cup;
	//_cupArray[0].body = cup;
	


	//shapel.Set(b2Vec2(-3.0f, 43.0f), b2Vec2(-1.0f, 41.0f));
	//platform->CreateFixture(&shapel, 0.0f);
	//shapel.Set(b2Vec2(3.0f, 43.0f), b2Vec2(1.0f, 41.0f));
	//platform->CreateFixture(&shapel, 0.0f);

////********************************************
	// ＴＥＳＴ　ＲＯＶＯＬＴＥ　ＪＯＩＮＴ

	//b2RevoluteJoint * re_array[3];
	//for(int i = 1; i < 4;i++){
	//b2BodyDef df;
	//df.type = b2_dynamicBody;
	//df.allowSleep = true;
	//
	//df.position.Set(5.0f * i,0.0f);

	//b2Body * testBody = _world->CreateBody(&df);

	//b2CircleShape shape;
	//shape.m_radius = 2.0f;
	//
	////b2Fixture fx;
	//testBody->CreateFixture(&shape,5.0f);

	//        b2RevoluteJointDef jd;
	//		jd.bodyA = ground;
 //           jd.bodyB = testBody;
 //           jd.localAnchorA.Set(-40.0f + 20 * i, 20.0f);
 //           jd.localAnchorB.Set(0.0f, 5.0f);
 //           jd.referenceAngle = 0.0f;
 //           jd.motorSpeed = 1.5f * b2_pi;
 //           jd.maxMotorTorque = 1e10f;
 //           jd.enableMotor = false;
 //           
	//		re_array[i-1] = (b2RevoluteJoint *)_world->CreateJoint(&jd);
	//
	//}
	//for(int i = 0; i < 3;i++)
	//	re_array[i]->EnableMotor(true);
	
	b2BodyDef df;
	df.type = b2_dynamicBody;
	df.allowSleep = true;
	
	df.position.Set(10.0f,45.0f);

	b2Body * testBody = _world->CreateBody(&df);
	
	b2CircleShape shape;
	shape.m_radius = 3.0f;
	testBody->CreateFixture(&shape,1.0f);



	//ball definition

	ball_def.allowSleep = true;
	ball_def.type = b2_dynamicBody;
	ball_def.gravityScale = 2.0f;
	
	ball_def.fixedRotation = false;

	

	//ball_def.
	//y = 75;

	
	//b2DistanceJointDef jf;
	//jf.bodyA = _mainBody;
	//jf.bodyB = testBody;
	//jf.localAnchorA.Set(0.0f,0.0f);
	//jf.localAnchorB.Set(0.0f,0.0f);
	//b2DistanceJoint * testJoint = (b2DistanceJoint *)_world->CreateJoint(&jf);

}

void HelloStarter::Step(DebugSettings * dbset, float dt) {
	float32 timeStep = dbset->hz > 0.0f ? 1.0f / dbset->hz : float32(0.0f);


	if (dbset->pause)
    {
        if (dbset->singleStep)
        {
            dbset->singleStep = 0;
        }
        else
        {
            timeStep = 0.0f;
        }

		return;
    }

	if(ball_num < gener_ball_num && _processStep % 10 == 0) {
		jumper *= -1;
		ball_def.position.Set(-15.0f *  jumper,55.0f);
		ball_def.linearVelocity.Set(1000.0f / ball_num * jumper,0.0f);
		b2Body * body = _world->CreateBody(&ball_def);
				b2MassData ns;
				ns.mass = 10000.0f;
				ns.center = b2Vec2_zero;
				ns.I = 2.0f;
				//ballBody->SetBullet(true);
				body->SetMassData(&ns);
		b2Fixture * fkk = body->CreateFixture(&_shape,0.5f);
		fkk->SetRestitution(0.3f);
		fkk->SetFriction(0.0f);
		ball_num++;
		
	} else if( _processStep > (60 * 5) && random(100) == 1 ) {
		if (ball_left > -1 ) {
			BallArray[ball_left]->SetGravityScale(2.0f);
			BallArray[ball_left]->ApplyForceToCenter(b2Vec2(0.0f,-100.0f));
			BallArray[ball_left--]->SetAwake(true);
		}
		if (ball_right > 29) {
			BallArray[ball_right]->SetGravityScale(2.0f);
			BallArray[ball_right]->ApplyForceToCenter(b2Vec2(0.0f,-100.0f));
			BallArray[ball_right--]->SetAwake(true);
		}
	}
	b2Vec2 _g;

	if( _cupGenerated < _cupNum && _processStep % (30 * 5) == 0) {
		
		_cupArray[_cupGenerated++] = newCup(10.0f , 87.0f);
	} else if (_cupGenerated == _cupNum) {
		_cup_speed *= 1.00015f;
		_g = _world->GetGravity();
		_g *= 1.00015f;
		_world->SetGravity(_g);
	}
	for(int i = 0; i < _cupGenerated; i ++) 
		moveCup(_cupArray[i]);
	//如果暂停



	

	//设置World的参数

	_world->SetWarmStarting(dbset->enableWarmStarting); //热启动 刚体更容易休眠
	_world->SetContinuousPhysics(dbset->enableContinuous); //连续物理 精度更高
	_world->SetSubStepping(dbset->enableSubStepping); //单步运算



	//调用world Step
	_world->Step(timeStep, dbset->velocityIterations, dbset->positionIterations);

	_world->ClearForces();

	//update game timer
	_timer->timeStep(dt);


	if(dbset->debug) {

		//设置debugView的flag
		uint32 flags = 0;
		flags += dbset->drawShapes            * b2Draw::e_shapeBit;
		flags += dbset->drawJoints            * b2Draw::e_jointBit;
		flags += dbset->drawAABBs            * b2Draw::e_aabbBit;
		flags += dbset->drawPairs            * b2Draw::e_pairBit;
		flags += dbset->drawCOMs                * b2Draw::e_centerOfMassBit;
		_debugView->SetFlags(flags);

		//调用World绘制debug图像
		_world->DrawDebugData();
	}


	_processStep ++;


}
void HelloStarter::moveCup(CUP * cup) {
	if(cup == NULL || cup->action == cup->out) {
		return;
	}
	//CCLOG("_cup_speed: %.2f ", _cup_speed);
	if(cup->action == cup->up) {
		cup->transY += 0.1f;
		cup->body->SetLinearVelocity(b2Vec2(0.0f, _cup_speed));
		cup->body->SetAngularVelocity( 0.0f );
	} else if(cup->action == cup->down) {
		cup->transY -= 0.1f;
		cup->body->SetLinearVelocity(b2Vec2(0.0f, -_cup_speed));
		cup->body->SetAngularVelocity( 0.0f );
		cup->roll = false;
	} else if(cup->action == cup->left) {
		cup->transX -= 0.1f;
		cup->body->SetLinearVelocity(b2Vec2(-_cup_speed, 0.0f));
		cup->body->SetAngularVelocity( 0.0f );
	} else if(cup->action == cup->right && !cup->roll) {
		cup->transX += 0.1f;
		
		cup->body->SetAngularVelocity( -0.7f * b2_pi * _cup_speed/15.0f);
		//cup->poly->SetAngularVelocity( 0.5 * b2_pi);
		//cup->ro->EnableMotor(true);
		cup->body->SetLinearVelocity(b2Vec2(_cup_speed, 00.0f));
		cup->roll = true;
	} else if(cup->roll) {
		//CCLOG("angle %.2f" , cup->body->GetAngle());
		if(cup->body->GetAngle() <= -2 * b2_pi) {
			cup->body->SetTransform(cup->body->GetPosition(), 0.0f);
			cup->poly->SetTransform(cup->body->GetPosition(), 0.0f);
			cup->body->SetAngularVelocity( 0.0f );
			
		}
	}
	cup->poly->SetAngularVelocity(cup->body->GetAngularVelocity());
	cup->poly->SetLinearVelocity(cup->body->GetLinearVelocity());
	//cup->body->GetLocalCenter();
	//cup->body->SetTransform(b2Vec2(0.0f,10.0f),0.0f);
	b2Vec2 position = cup->body->GetPosition();
	double x = position.x;
	double y = position.y;
	//CCLOG("x = %.2f, y = %.2f, %d %d %d",x,y ,x <= -26.0f , y <= 10.0f, y < 80.0f ); 
	
	if(x >= 26.0f && y >= 87.0f && y > 10.0f)
		cup->action = cup->down;
	else if(x <= -26.0f && y <= 10.0f && y < 87.0f) {
		CCLOG("%d", cup->pf->_ball_num);
		if(cup->pf->_ball_num <=0) {
			cup->body->SetType(b2_dynamicBody);
			cup->poly->SetType(b2_dynamicBody);
			cup->action = cup->out;
			cup->body->SetGravityScale(1.0f);
			cup->poly->SetGravityScale(1.0f);
			cup->body->ApplyLinearImpulse(b2Vec2(_cup_speed,20.0f),b2Vec2(0.0f,0.0f));
			cup->poly->ApplyLinearImpulse(b2Vec2(_cup_speed,20.0f),b2Vec2(0.0f,0.0f));
		} else {
			cup->action = cup->up;
		}
		
	}
	else if(y <= 10.0f && x > -26.0f && x >= 26.0f)
		cup->action = cup->left;
	else if(y >= 87.0f && x <= -26.0f && x < 26.0f)
		cup->action = cup->right;



}

void HelloStarter::MouseUp(const b2Vec2& p)
{
    if (_mouseJoint)
    {
        _world->DestroyJoint(_mouseJoint);
        _mouseJoint = NULL;
    }
    
    //if (m_bombSpawning)
    //{
    //    CompleteBombSpawn(p);
    //}
}

void HelloStarter::MouseMove(const b2Vec2& p)
{
    //_mouseJoint = p;
    
    if (_mouseJoint)
    {
        _mouseJoint->SetTarget(p);
    }
}

bool HelloStarter::MouseDown(const b2Vec2& p)
{
    //_mouseJoint = p;
    
    if (_mouseJoint)
    {
        return false;
    }

    // Make a small box.
    b2AABB aabb;
    b2Vec2 d;
    d.Set(0.001f, 0.001f);
    aabb.lowerBound = p - d;
    aabb.upperBound = p + d;

    // Query the world for overlapping shapes.
    QueryCallback callback(p);
    _world->QueryAABB(&callback, aabb);

    if (callback.m_fixture)
    {
        b2Body* body = callback.m_fixture->GetBody();
        b2MouseJointDef md;
		

		md.bodyA = _mainBody;
        md.bodyB = body;
        md.target = p;
        md.maxForce = 1000.0f * body->GetMass();
		//md.dampingRatio = 0.0001f;
		//md.frequencyHz = 3000;
        _mouseJoint = (b2MouseJoint*)_world->CreateJoint(&md);
        body->SetAwake(true);
        return true;
    }
    return false;
}


void HelloStarter::ballGo(){
	if(!_cap.open){
		if(_cap.left)
			_cap.body->DestroyFixture(_cap.left);
		if(_cap.right)
			_cap.body->DestroyFixture(_cap.right);
		_cap.left = _cap.body->CreateFixture(_cap.leftOpen,0.0f);
		_cap.right = _cap.body->CreateFixture(_cap.rightOpen,0.0f);
		_cap.open = true;
	}
}
void HelloStarter::ballStop(){
	if(_cap.open){
		if(_cap.left)
			_cap.body->DestroyFixture(_cap.left);
		if(_cap.right)
			_cap.body->DestroyFixture(_cap.right);
		_cap.left = _cap.body->CreateFixture(_cap.leftClose,0.0f);
		_cap.right = _cap.body->CreateFixture(_cap.rightClose,0.0f);
		_cap.open = false;
	}
}


