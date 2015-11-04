#include "GameTimer.h"
#include "HelloWorldScene.h"
#include "ArcadeMode.h"


GameTimer::GameTimer(void * _engine) {
	this->_engine = (HelloStarter *) _engine;
	_velocity = 1.0f;
	_time = 0;
}

GameTimer::~GameTimer() {

}

GameTimer * GameTimer::create(HelloStarter * hl) {
	return new GameTimer(hl);
}
void GameTimer::timeStep(float dt) {
	if(_velocity < 1.0f)
		_velocity = 1.0f;
	//CCLOG("velocity: %.2f ", _velocity);
	_time += (dt + 1) * _velocity  ;
	//float s;
		_engine->_baseView->scoreCallBack(_time/60);
}