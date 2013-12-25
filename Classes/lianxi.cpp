#include "lianxi.h"
#include "UTF8ToGBK.h"
#include "WallScene.h"
#include "Tianzige.h"
#include "tinyxml.h"
#include "ReadXML.h"
#include <sstream>

#define tianzige_draw_tag 1001

lianxi::lianxi(){
	output = "";
}

lianxi::~lianxi(){

}

bool lianxi::init(){
	if (CCLayer::init())
	{
		this->setKeypadEnabled(true);
		this->setTouchEnabled(true);

		CCSize winSize = CCDirector::sharedDirector()->getWinSize(); 
		CCSize visiableSize = CCDirector::sharedDirector()->getVisibleSize();
		CCSize originSize = CCDirector::sharedDirector()->getVisibleOrigin();

		//add wall-head
		CCSprite* wall_head = CCSprite::create("wall_head.png");
		this->addChild(wall_head,2);
		CCSize headSize = wall_head->getContentSize();
		wall_head->setPosition(ccp(visiableSize.width/2,visiableSize.height-wall_head->getContentSize().height/2));
		wall_head->setScaleX(visiableSize.width/wall_head->getContentSize().width);

		//add ceshi tail on the bottom
		CCSprite* wall_tail = CCSprite::create("wall_tail.png");
		this->addChild(wall_tail,2);
		CCSize tailSize = wall_tail->getContentSize();
		wall_tail->setPosition(ccp(visiableSize.width/2,wall_tail->getContentSize().height/2));
		wall_tail->setScaleX(visiableSize.width/wall_tail->getContentSize().width);

		//add tianzige
		CCSprite* tianzige = CCSprite::create("tianzige.png");
		this->addChild(tianzige,1);
		CCSize tianzigeSize = tianzige->getContentSize();
		tianzige->setPosition(ccp(visiableSize.width/2,visiableSize.height-headSize.height-tianzigeSize.height/2-50));


		CCSprite* tianzige_draw = CCSprite::create("tianzige.png");
		this->addChild(tianzige_draw,1,tianzige_draw_tag);
		CCSize tianzigeDrawSize = tianzige_draw->getContentSize();
		tianzige_draw->setPosition(ccp(visiableSize.width/2,tailSize.height+50+tianzigeDrawSize.height/2));

		CCSprite* bg = CCSprite::create("lianxi_background.png");
		this->addChild(bg,0);
		bg->setPosition(ccp(visiableSize.width/2,visiableSize.height/2));
		bg->setScaleX(visiableSize.width/bg->getContentSize().width);
		bg->setScaleY((visiableSize.height-headSize.height-tailSize.height)/bg->getContentSize().height);

		//     CCSprite* bg_top = CCSprite::create("lianxi_top.png");
		//     this->addChild(bg_top,0);
		//     bg_top->setPosition(ccp(visiableSize.width/2,-headSize.height+visiableSize.height-bg_top->getContentSize().height/2));
		//     bg_top->setScaleX(visiableSize.width/bg_top->getContentSize().width);
		//     float scale_y = visiableSize.height/(visiableSize.height-headSize.height*2);
		//     bg_top->setScaleY(scale_y);
		// 
		//     CCSprite* bg_bottom = CCSprite::create("lianxi_bottom.png");
		//     this->addChild(bg_bottom,0);
		//     bg_bottom->setPosition(ccp(visiableSize.width/2,tailSize.height+bg_bottom->getContentSize().height/2));
		//     bg_bottom->setScale(visiableSize.width/bg_bottom->getContentSize().width);
		//     bg_bottom->setScaleY(scale_y);
		// 
		//     CCSprite* bg_separ = CCSprite::create("lianxi_separate.png");
		//     this->addChild(bg_separ,0);
		//     bg_separ->setPosition(ccp(visiableSize.width/2,visiableSize.height/2));
		//     bg_separ->setScaleX(visiableSize.width/bg_separ->getContentSize().width);

		CCLabelTTF* back = CCLabelTTF::create("BACK","Arial",25);
		CCMenuItemLabel* menuLabel = CCMenuItemLabel::create(back,this,menu_selector(lianxi::menuBack));
		CCMenu* menu = CCMenu::create(menuLabel,NULL);
		this->addChild(menu,20);
		menuLabel->setPosition(ccp(back->getContentSize().width/2+100,back->getContentSize().height+30));
		menu->setPosition(CCPointZero);
		/*menu->registerWithTouchDispatcher();*/

		CCLabelTTF* bihuaCount = CCLabelTTF::create(UTF8ToGBK::UTF8TOGBK(string("笔画数")).c_str(),"Arial",40);
		addChild(bihuaCount);
		bihuaCount->setPosition(tianzige->getPosition()+ccp(-tianzigeSize.width/2-bihuaCount->getContentSize().width/2-50,tianzigeSize.height/2));
		CCLabelTTF* bihuashuzi = CCLabelTTF::create();
		addChild(bihuashuzi);
		bihuashuzi->setPosition(bihuaCount->getPosition()-ccp(0,2*bihuaCount->getContentSize().height));


		CCLog(hanzi.c_str());
		//luanma
		CCLabelTTF* pHanzi = CCLabelTTF::create(UTF8ToGBK::UTF8TOGBK(hanzi).c_str(),"Arial", 100);
		this->addChild(pHanzi,10);
		pHanzi->setPosition(tianzige->getPosition());

		//read xml show animation of character
		string xml = CCFileUtils::sharedFileUtils()->fullPathForFilename("xml/八.xml");
		CReadXML readxml(xml);
		charac = readxml.getCharacter();
		int coun = charac.getStrokeCount();
		string str_coun = std::to_string(coun);
		bihuashuzi->initWithString(str_coun.c_str(),"Arial",40);
		// 	this->addChild(readxml.getCharacter(),10);
		// 	readxml.getCharacter()->setPosition(ccp(visiableSize.width/2,visiableSize.height/2));


		//画正字
		charac.getBox();
		charac.resize(tianzige->getContentSize());
		//重采样
		charac.resample();

		charac.prepareDrawNode();
		vector<Bujian> bujianList = charac.bujianList;
		vector<Bujian>::iterator iter = bujianList.begin();
		for (iter;iter != bujianList.end(); ++iter)
		{
			Bujian bujian = (Bujian)*iter;
			vector<Stroke> strokeList = bujian.strokeList;
			vector<Stroke>::iterator stro_iter = strokeList.begin();
			for (stro_iter; stro_iter != strokeList.end(); ++stro_iter)
			{
				Stroke stroke = (Stroke)*stro_iter;
				vector<CCDrawNode*> nodeList = stroke.nodeList;	
				for (vector<CCDrawNode*>::iterator nodeIter = nodeList.begin(); nodeIter != nodeList.end(); ++nodeIter)
				{
					tianzige->addChild((CCDrawNode*)*nodeIter,100);
				}
			}
		}
		return true;
	}
	return false;
}

void lianxi::onEnter(){
	CCLayer::onEnter();
	CCLog("onEnter linxian");
	
}

void lianxi::onExit(){
	CCLayer::onExit();
}

void lianxi::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

/************************************************************************/
/* hanzi 需要练习的汉字                                                                     */
/************************************************************************/
CCScene* lianxi::scene(string hanzi){
	CCScene *scene = CCScene::create();
	lianxi *layer = lianxi::create();
	layer->hanzi = hanzi;
	scene->addChild(layer);
	return scene;
}

// bool  lianxi::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
// 	prePoint = pTouch->getLocation();
// 	CCSprite* tianzige = (CCSprite*)this->getChildByTag(tianzige_draw_tag);
// 	CCRect rect = tianzige->boundingBox();
// 	if (rect.containsPoint(prePoint))
// 	{
// 		output += "[[";
// 		string temp = convertToString(prePoint.x) + "/" + convertToString(prePoint.y) + ",";
// 		output += temp;
// 	}
// 	return true;
// }

// void  lianxi::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
// 	CCPoint location = pTouch->getLocation();
// 	CCSprite* tian = (CCSprite*)getChildByTag(tianzige_draw_tag);
// 	CCRect rect = tian->boundingBox();
// 	if (rect.containsPoint(location))
// 	{
// 		string temp = convertToString(location.x) + "/" + convertToString(location.y);
// 		output += temp;
// 		output += "]]";
// 	}
// 	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(lianxi::clearStroke),this,1.0,false);
// 
// 	//获取手写出来笔画的中心点 prePoint location
// 	centerPoint = centerP(prePoint,location);
// }

// void  lianxi::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
// 	CCPoint location = pTouch->getLocation();
// 
// 	CCSprite* tianzige = (CCSprite*)this->getChildByTag(tianzige_draw_tag);
// 	CCRect rect = tianzige->boundingBox();
// 	if (rect.containsPoint(location))
// 	{
// 		// 采集点信息
// 		string temp = convertToString(location.x) + "/" + convertToString(location.y) + ",";
// 		output += temp;
// 		// 	CCDrawNode * dot = CCDrawNode::create();
// 		// 	dot->drawDot(location,5.0,ccc4f(188, 188, 188, 120));
// 		// 	//this->addChild(dot,10);
// 		// 	tianzige->addChild(dot,10);
// 		CCDrawNode* node = CCDrawNode::create();
// 		writing_stroke.push_back(node);
// 		addChild(node,10);
// 		node->drawSegment(prePoint,location,5.0,ccc4f(180,180,180,100));
// 		prePoint = location;
// 	}
// }


void lianxi::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	prePoint = ((CCTouch*)pTouches->anyObject())->getLocation();
	CCSprite* tianzige = (CCSprite*)this->getChildByTag(tianzige_draw_tag);
	CCRect rect = tianzige->boundingBox();
	if (rect.containsPoint(prePoint))
	{
		output += "[[";
		string temp = convertToString(prePoint.x) + "/" + convertToString(prePoint.y) + ",";
		output += temp;
	}
}

void lianxi::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	CCTouch* pTouch = (CCTouch*)pTouches->anyObject();
	CCPoint location = pTouch->getLocation();

	CCSprite* tianzige = (CCSprite*)this->getChildByTag(tianzige_draw_tag);
	CCRect rect = tianzige->boundingBox();
	if (rect.containsPoint(location))
	{
		// 采集点信息
		string temp = convertToString(location.x) + "/" + convertToString(location.y) + ",";
		output += temp;
		// 	CCDrawNode * dot = CCDrawNode::create();
		// 	dot->drawDot(location,5.0,ccc4f(188, 188, 188, 120));
		// 	//this->addChild(dot,10);
		// 	tianzige->addChild(dot,10);
		CCDrawNode* node = CCDrawNode::create();
		writing_stroke.push_back(node);
		addChild(node,10);
		node->drawSegment(prePoint,location,5.0,ccc4f(180,180,180,100));
		prePoint = location;
	}
}

void lianxi::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	CCPoint location = ((CCTouch*)pTouches->anyObject())->getLocation();
	CCSprite* tian = (CCSprite*)getChildByTag(tianzige_draw_tag);
	CCRect rect = tian->boundingBox();
	if (rect.containsPoint(location))
	{
		string temp = convertToString(location.x) + "/" + convertToString(location.y);
		output += temp;
		output += "]]";
	}
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(lianxi::clearStroke),this,1.0,false);

	//获取手写出来笔画的中心点 prePoint location
	centerPoint = centerP(prePoint,location);
}


void lianxi::keyBackClicked(){
	CCLog("BBBB");
// 	CCDirector::sharedDirector()->replaceScene(WallScene::scene());
	CCDirector::sharedDirector()->popScene();
}

void lianxi::menuBack(CCObject* pSender){
// 	CCDirector::sharedDirector()->replaceScene(WallScene::scene());
	CCDirector::sharedDirector()->popScene();
}

// void lianxi::draw(){
// 
// }

string lianxi::convertToString(float f){
	ostringstream buff;
	buff<<f;
	return buff.str();
}

void lianxi::clearStroke(float dt){
	CCLog("clearStroke");
	for (vector<CCDrawNode*>::const_iterator it = writing_stroke.begin(); it != writing_stroke.end(); ++it )
	{
		removeChild(*it);
	}
	writing_stroke.clear();
	CCLog("%d",writing_stroke.size());
	
	CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(lianxi::clearStroke),this);

	//DoAnimation();
}

void lianxi::DoAnimation(){
	//run action
	Stroke pie = charac.getStroke(1);
	vector<CCDrawNode*> nodeList = pie.nodeList;
	CCMoveTo* actionTo = CCMoveTo::create(1,CCPointMake(300,100));
	for (vector<CCDrawNode*>::const_iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		(*it)->runAction(actionTo);
	}

}

CCPoint lianxi::centerP(CCPoint p1,CCPoint p2){
	return CCPointMake((p1.x+p2.x)/2,(p1.y+p2.y)/2);
}