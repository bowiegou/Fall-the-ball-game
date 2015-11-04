#include "ball.h"

Ball::Ball() {
}

Ball::~Ball() {
}

Ball * Ball::createWithTexture(CCTexture2D * txt) {
	Ball * b = new Ball();
	b->initWithTexture(txt);
	b->autorelease();

	b2BodyDef df;
	df.type = b2_dynamicBody;
	df.allowSleep = true;
	df.bullet = true;

	b2CircleShape shape;
	shape.m_radius = 2.0f;

	return b;
}

void Ball::onEnter() {

}

void Ball::onExit() {

}

void Ball::move(float dt) {

	this->setPosition( ccpAdd(getPosition(), ccpMult(b_def.velocity, dt)) );


}



