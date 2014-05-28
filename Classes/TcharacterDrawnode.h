#ifndef _TcharacterDrawnode_H__
#define _TcharacterDrawnode_H__

#include "cocos2d.h"
#include "Character.h"
#include "StrokeDrawnode.h"
USING_NS_CC;

/************************************************************************/
/* 继承CCNode,用于显示正确汉字                                                                     */
/************************************************************************/
class TcharacterDrawnode : public CCNode
{
public:
	TcharacterDrawnode();
	~TcharacterDrawnode();
	/**
	* 实现CCNode绘图函数，根据自身笔画列表绘图
	* @return
	*/
	virtual void draw();
	/**
	* 用汉字和显示区域初始化TcharacterDrawnode
	* @param hz 
	* @param showrect
	* @return
	*/
	virtual bool init(string hz,CCSize showrect);
	/**
	* 用汉字和显示区域创建TcharacterDrawnode
	* @param hz
	* @param showrect
	* @return
	*/
	static TcharacterDrawnode* create(string hz,CCSize showrect);

//	CREATE_FUNC(TcharacterDrawnode);
// 	vector<StrokeDrawnode*> strokedrawList;

	/**
	* 返回当前正字Character
	* @return
	*/
	Character getCharacter(){return m_character;}

	/**
	 * get all strokes points count for animation
	 * @return
	 */
	int getPointsCount();

	void setVisibleIndex(int vi);
	int getVisibleIndex()    { return visibleIndex; }

	CC_SYNTHESIZE_RETAIN(CCArray*,strokedrawList,strokedrawList);
private:
	CCSize showRect;				//根据传入的显示范围定义显示范围
	Character m_character;			//根据汉字读取字符xml文件，构造Character
	int visibleIndex;
};


#endif
