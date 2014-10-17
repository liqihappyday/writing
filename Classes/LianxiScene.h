#ifndef __LianxiScene_H__
#define __LianxiScene_H__

#include "cocos2d.h"
#include "TouchLayer.h"
#include "BackgroundLayer.h"
#include "TcharacterLayer.h"
#include "HcharacterLayer.h"
#include "CharacterExtend.h"
USING_NS_CC;


class LianxiScene : public CCScene
{
public:
	LianxiScene(string hanzi);
	~LianxiScene();
	static LianxiScene* create(string hanzi);
	virtual bool init();

	string CurrentCharacter;			//当前正在练习的汉字字符
	string funcs;						//当前汉字需要使用到数据中笔画lua评判规则

// 	BackgroundLayer* backgroundLayer;		//背景图层
// 	TouchLayer* touchLayer;			//触摸事件响应层
// 	TcharacterLayer* TLayer;			//正字图层
// 	HcharacterLayer* HLayer;
	CC_SYNTHESIZE_RETAIN(BackgroundLayer*,backgroundLayer,backgroundLayer);
	CC_SYNTHESIZE_RETAIN(TouchLayer*,touchLayer,touchLayer);
	CC_SYNTHESIZE_RETAIN(TcharacterLayer*,TLayer,TLayer);
	CC_SYNTHESIZE_RETAIN(HcharacterLayer*,HLayer,HLayer);
//	CC_SYNTHESIZE_RETAIN(CharacterEntity*,p,CharacterP);
	CC_SYNTHESIZE_RETAIN(CharacterExtend*,ext_p,CharacterExt);
private:

};



#endif
