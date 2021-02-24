#include "GameScene.h"
#include "AIPlayer.h"

NS_CC_BEGIN

class GameMaster;



/*
Vec2    fieldID = 0,0; 7,0; 7,7; 0,7
Vec2    fieldPos = 50,50; 750,750
uint8_t num=0,7,63    number field
Field*  field
*/

class GameMaster :public Node {
	std::unique_ptr<AIPlayer> _ai;
	bool _gameEnd;
	Field* _selectedField;
public:
	GameMaster();

	void onSelected(uint8_t id);

	void move(Field* field);

	void checkWins(Field::Type type);
	

	Field::Type getPlayerType() {
		return Field::Type::WHITE;
	}

	//get Field
	Field* getFieldWithNum(int i) {
		return static_cast<Field*>(getChildByTag(i));
	}

	Field* getFieldWithPos(float x, float y) {
		return getFieldWithNum(getNumWithFieldPos(x, y));
	}

	Field* getFieldWithPos(Vec2 Pos) {
		return getFieldWithNum(getNumWithFieldPos(Pos.x, Pos.y));
	}

	//get fieldId
	
	static Vec2 getFieldIdWithPos(Vec2 pos) {
		return (Vec2(pos.x - 50, pos.y - 50) / 100);
	}

	static Vec2 getFieldIdWithPos(float x, float y) {
		return (Vec2(x - 50, y - 50) / 100);
	}

	static Vec2 getFieldIdWithNum(uint8_t num) {
		return (Vec2(num%8, num / 8));
	}

	//get fieldPos


	static Vec2 getposWithField(cocos2d::Vec2 field) {
		auto x = (field.x) * 100 + 50;
		auto y = (field.y) * 100 + 50;
		return Vec2(x, y);
	}

	static Vec2 getposWithId(uint8_t id) {
		auto dx = id % 8;
		auto dy = id / 8;
		return getposWithField(Vec2(dx, dy));
	}

	//get Num

	static uint8_t getNumWithFieldId(Vec2 pos) {
		return pos.x + pos.y * 8;
	}

	static uint8_t getNumWithFieldPos(float x, float y) {
		return x + y * 8;
	}


	//check position metods
	static bool isCorrectField(cocos2d::Vec2 field) {
		return (field.x > -1 && field.y > -1) && (field.x < 8 && field.y < 8);
	}

	static bool isCorrectMove(cocos2d::Vec2 res) {
		return ((res.x * res.x <= 1) && (res.y * res.y <= 1));
	}
};

NS_CC_END