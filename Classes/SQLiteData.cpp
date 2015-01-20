#include "SQLiteData.h"

vector<string> SQLiteData::splitStrokeSeq(string seq){
	string::size_type pos1,pos2;
	vector<string> strvec;
	pos2 = seq.find('-');
	pos1 = 0;
	while (string::npos != pos2)
	{
		strvec.push_back(seq.substr(pos1,pos2-pos1));
		pos1 = pos2 +1;
		pos2 = seq.find('-',pos1);
	}
	// 	strvec.push_back(seq.substr(pos1));
	return strvec;
}

void SQLiteData::getHanziData(string hz,CCObject* p){
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	string dbpath = CCFileUtils::sharedFileUtils()->fullPathForFilename("character_info.db");
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	string dbpath = CCFileUtils::sharedFileUtils()->getWritablePath()+"character_info.db";
#endif
	SqliteHelper::initDB(dbpath.c_str());
	string sql = "select * from ziData where ziName ='"+hz+"'";
	SqliteHelper::getZiDataInfo(sql,p);
	SqliteHelper::closeDB();
}

string SQLiteData::getstrokeFunc(string strokeID){
	CCLog("SQLiteData::getstrokeFunc %s",strokeID.c_str());
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	string dbpath = CCFileUtils::sharedFileUtils()->fullPathForFilename("character_judge.db");
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	string dbpath = CCFileUtils::sharedFileUtils()->getWritablePath()+"character_judge.db";
#endif
	SqliteHelper::initDB(dbpath.c_str());
	string sql = "select * from strokeFunc where strokeID ='"+strokeID+"'";
	strokeFunc* ret = new strokeFunc();
	SqliteHelper::getstrokeFunc(sql,ret);
	SqliteHelper::closeDB();
	return string(ret->getFunc()->getCString());
}

void SQLiteData::getHanziDataExtend(string hz,CCObject* p){
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	string dbpath = CCFileUtils::sharedFileUtils()->fullPathForFilename("character_judge.db");
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	string dbpath = CCFileUtils::sharedFileUtils()->getWritablePath()+"character_judge.db";
#endif
	SqliteHelper::initDB(dbpath.c_str());
	string sql = "select * from ziData where ziName ='"+hz+"'";
	SqliteHelper::getZiDataInfoExtend(sql,p);
	SqliteHelper::closeDB();
}

bool SQLiteData::isExist(string hz){
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	string dbpath = CCFileUtils::sharedFileUtils()->fullPathForFilename("character_judge.db");
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	string dbpath = CCFileUtils::sharedFileUtils()->getWritablePath()+"character_judge.db";
#endif
	SqliteHelper::initDB(dbpath.c_str());
	string sql = "select * from ziData where ziName ='"+hz+"'";
	int count = SqliteHelper::getDataCount(sql);
	SqliteHelper::closeDB();
	if (count > 0)
	{
		return true;
	}else{
		return false;
	}
	return true;
}

// vector<string> SQLiteData::getGroupCharacter(string index){
// #if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
// 	string dbpath = CCFileUtils::sharedFileUtils()->fullPathForFilename("character_judge.db");
// #endif
// #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
// 	string dbpath = CCFileUtils::sharedFileUtils()->getWritablePath()+"character_judge.db";
// #endif
// 	SqliteHelper::initDB(dbpath.c_str());
// 	string sql = "select * from groupCharacter where id ='"+index+"'";
// 	vector<string> resultOfGroupCharacter = SqliteHelper::getGroupCharacter(sql);
// 	SqliteHelper::closeDB();
// 	return resultOfGroupCharacter;
// }
// 
// bool SQLiteData::updateGroupCharacter(string index, string indexOfCharacter, string character){
// #if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
// 	string dbpath = CCFileUtils::sharedFileUtils()->fullPathForFilename("character_judge.db");
// #endif
// #if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
// 	string dbpath = CCFileUtils::sharedFileUtils()->getWritablePath()+"character_judge.db";
// #endif
// 	SqliteHelper::initDB(dbpath.c_str());
// 	string sql = "update groupCharacter set C"+index+" = '"+character+"' where id = "+index;
// 	SqliteHelper::updateData(sql);
// 	return true;
// }

vector<string> splitSingle(string singlestring){
	string::size_type pos1,pos2;
	vector<string> strRe;
	pos2 = singlestring.find(':');
	pos1 = 0;
	while (string::npos != pos2)
	{
		strRe.push_back(singlestring.substr(pos1,pos2-pos1));
		pos1 = pos2+1;
		pos2 = singlestring.find(':',pos1);
	}
	return strRe;
}

vector<vector<string>> splitUnitString(string charstring){
	string::size_type pos1,pos2;
	vector<vector<string>> strvec;
	pos2 = charstring.find('/');
	pos1 = 0;
	while (string::npos != pos2)
	{
		strvec.push_back(splitSingle(charstring.substr(pos1,pos2-pos1)));
		pos1 = pos2 +1;
		pos2 = charstring.find('/',pos1);
	}
	return strvec;
}

string createUnitString(vector<vector<string>> unit){
	string ret;
	for (int i = 0 ; i < unit.size(); i++)
	{
		vector<string> singleChar = unit.at(i);
		for (int j = 0; j< singleChar.size(); j++)
		{
			ret += singleChar.at(j)+":";
		}
		ret += "/";
	}
	return ret;
}

vector<vector<string>> SQLiteData::getUnit(string index,int count){
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	string dbpath = CCFileUtils::sharedFileUtils()->fullPathForFilename("character_judge.db");
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	string dbpath = CCFileUtils::sharedFileUtils()->getWritablePath()+"character_judge.db";
#endif
	SqliteHelper::initDB(dbpath.c_str());
	string sql = "select * from unit where id ='"+index+"'";
	string charstring = SqliteHelper::getUnit(sql);
	vector<vector<string>> result = splitUnitString(charstring);
	vector<vector<string>> re;
	for (int i = 0 ; i < count ; ++i)
	{
		re.push_back(result.at(i));
	}
	SqliteHelper::closeDB();
	return re;
}

bool SQLiteData::updateUnit(string index,vector<vector<string>> unit){
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	string dbpath = CCFileUtils::sharedFileUtils()->fullPathForFilename("character_judge.db");
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	string dbpath = CCFileUtils::sharedFileUtils()->getWritablePath()+"character_judge.db";
#endif
	SqliteHelper::initDB(dbpath.c_str());
	string unitStr = createUnitString(unit);
	string sql = "update unit set characters='"+unitStr+"' where id = '"+index+"'";
	SqliteHelper::updateData(sql);
	SqliteHelper::closeDB();
	return true;
}