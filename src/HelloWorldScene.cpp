#include "HelloWorldScene.h"
#include "ContactListener.h"
#include "GameTimer.h"
#include "query.h"


////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
//
// ** HelloWorld
// The base View of the entire game
// create and implement the scene
// 
//
//


//主场景
CCScene* HelloWorld::scene()
{

    CCScene *scene = CCScene::create();
    

	HelloStarter * hl = HelloStarter::create();
	hl->start();
	

    HelloWorld *layer = HelloWorld::create();

	

	layer->setUserData(hl);
	layer->setStep(NULL);

	

    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
// 在CClayer create里面会自动调用
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	this->setTouchEnabled(true);
	//CCDirector * s_Director = CCDirector::sharedDirector();
	//VisiableRect = CCRectMake(s_Director->getVisibleOrigin().x,s_Director->getVisibleOrigin().y,s_Director->getVisibleSize);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	visiableRect = new CCRect(origin.x,origin.y,visibleSize.width,visibleSize.height);


    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);




	CCTexture2D * cd = CCTextureCache::sharedTextureCache()->addImage("ball.png");

    CCLabelTTF* pLabel = CCLabelTTF::create("TestBall", "Arial", 24);

    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    this->addChild(pLabel, 1);



	hw = HelloView::viewCreate();
	this->addChild(hw,2);
	hw->registerWithTouchDispatcher();
	hw->setScale(10);
	hw->setAnchorPoint(ccp(0,0));
	hw->setPosition(ccp(origin.x + visibleSize.width/2, origin.y));
	
	//setting up score board
	_scoreBoard = CCLabelTTF::create("testScore","FZCuYuan-M03S",60);
	_scoreBoard->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + _scoreBoard->getContentSize().height + 300));

	this->addChild(_scoreBoard,0);
	//this->addChild(platform,2);
	

	schedule(schedule_selector(HelloWorld::Step));
    
    return true;
}

bool HelloWorld::ccTouchBegan(CCTouch* touch, CCEvent * event){
	st->ballGo();
	return true;
}
void HelloWorld::ccTouchMoved(CCTouch* touch, CCEvent * event){

	return;
}

void HelloWorld::ccTouchEnded(CCTouch* touch, CCEvent * event){

	st->ballStop();
}

void HelloWorld::registerWithTouchDispatcher(){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 10, true);
}




CCRect * HelloWorld::getVisiableRect() {
		return visiableRect;
}

void HelloWorld::setStep(HelloStarter * h){
		//if(!h){
			st = (HelloStarter *) this->getUserData();
			hw->_engine = this->st;

			//setting up timer
	
			_timer = GameTimer::create(st);

			st->_timer = _timer;
			st->setBaseView(this);

		//}
	}

void HelloWorld::Step(float dt){
	 
	//if(!st)
		st -> Step(st->_setting,dt);
		//st->_world;

}



void HelloWorld::menuCloseCallback(CCObject* pSender)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
//	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//#else
//    CCDirector::sharedDirector()->end();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
//#endif

	if(st->_setting->drawJoints)
		st->_setting->drawJoints = 0;
	else 
		st->_setting->drawJoints = 1;
}


void HelloWorld::scoreCallBack(char * str) {
	_scoreBoard->setString(str);
}

void HelloWorld::scoreCallBack(unsigned int str) {
	sprintf_s(score,"%d",str);

	//CCLOG("%d",str);

	_scoreBoard->setString(score);
}