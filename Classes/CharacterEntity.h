#ifndef __CharacterEntity_H__
#define __CharacterEntity_H__

#include "cocos2d.h"
USING_NS_CC;

class CharacterEntity : public CCObject
{
public:
	CharacterEntity();
	~CharacterEntity();
	CC_SYNTHESIZE_RETAIN(CCInteger*,id,ID);			//id
	CC_SYNTHESIZE_RETAIN(CCString*,name,Name);		//Character name
	CC_SYNTHESIZE_RETAIN(CCString*,xml,XML);			//Character xml from sqlite
	CC_SYNTHESIZE_RETAIN(CCString*,rules,Rules);		//Character rules
	CC_SYNTHESIZE_RETAIN(CCString*,strokeIDSeq,SEQ);	//sequence
private:
	
};

#endif
