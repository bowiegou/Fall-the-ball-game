#ifndef GAME_TIMER_H
#define GAME_TIMER_H
#include "cocos2d.h"

using namespace cocos2d;

class HelloStarter;

class GameTimer {
private:
	char _score[200];
public:
	float _velocity;
	unsigned int _time;
	HelloStarter * _engine;

public:
	GameTimer(void * _engine);
	~GameTimer();
	static GameTimer * create(HelloStarter * hl);
	void timeStep(float dt);





};




#endif
