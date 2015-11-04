#include "ContactListener.h"


CupContactListener::CupContactListener(HelloStarter * hl) {
	this->_engine = hl;
}
CupContactListener::~CupContactListener() {

}
CupContactListener * CupContactListener::create(HelloStarter * hl) {
	return new CupContactListener(hl);
}

void CupContactListener::BeginContact(b2Contact * contact) {

	b2Fixture * fixtureA = contact->GetFixtureA();
	b2Fixture * fixtureB = contact->GetFixtureB();
	
	if(fixtureA->IsSensor() && fixtureA->GetBody()->GetType() != b2_dynamicBody) {
		if(fixtureA->GetUserData() != NULL) {
			this->CupBeginContact(fixtureA);

		}
	}
	else if(fixtureB->IsSensor() &&  fixtureB->GetBody()->GetType() != b2_dynamicBody ) {
		if(fixtureB->GetUserData() != NULL) {
			this->CupBeginContact(fixtureB);
		}
	}
}

void CupContactListener::EndContact(b2Contact * contact) {
	b2Fixture * fixtureA = contact->GetFixtureA();
	b2Fixture * fixtureB = contact->GetFixtureB();

	if(fixtureA->IsSensor()) {
		if(fixtureA->GetUserData() != NULL) {
			this->CupEndContact(fixtureA);
		}
	}
	else if(fixtureB->IsSensor()) {
		if(fixtureB->GetUserData() != NULL) {
			this->CupEndContact(fixtureB);
		}
	}
}

void CupContactListener::CupBeginContact(b2Fixture * fx) {
	CupProfile * pf = (CupProfile * ) fx->GetUserData();
	pf->_ball_num ++;
	_engine->_timer->_velocity *= 1.2;
			
}

void CupContactListener::CupEndContact(b2Fixture * fx) {
	CupProfile * pf = (CupProfile * ) fx->GetUserData();
	pf->_ball_num --;
	_engine->_timer->_velocity /= 1.2;
}