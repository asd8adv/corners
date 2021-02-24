#include "GameMaster.h"
NS_CC_BEGIN


/***************
class GameMaster
***************/

GameMaster::GameMaster() {
	_gameEnd = false;
	for (size_t i = 0; i < 64; i++) {
		std::string number = std::to_string(i);
		auto it = Field::create();
		auto x = i % 8;
		auto y = i / 8;
		if (x <= 2 && y <= 2) {
			it->setType(Field::Type::BLACK);
		}
		if (x >= 5 && y >= 5) {
			it->setType(Field::Type::WHITE);
		}
		it->setFieldId(i);
		it->setPosition(getposWithId(i));
		addChild(it, 1, i);
	}
	_ai = std::make_unique<AIPlayer>(AIPlayer(this));
	_selectedField = nullptr;
}

void GameMaster::onSelected(uint8_t id) {
	if (_gameEnd)return;
	if (id < 64) {
		auto currentField = getFieldWithNum(id);
		if (!_selectedField) {//גûהוכÿול ןמכו
			if (currentField->getType() == getPlayerType()) {
				if (currentField == _selectedField) {
					_selectedField->changeSelected();
				}
				else {
					_selectedField = currentField;
					_selectedField->changeSelected();
					return;
				}
			}
		}
		else {
			if (_selectedField->getSelected()) {
				if (currentField->getType() == Field::Type::NONE) {
					auto ids = _selectedField->getFieldId();
					auto res = (getposWithId(_selectedField->getFieldId()) - getposWithId(currentField->getFieldId()))/100;
					if (isCorrectMove(res)) {
						move(currentField);
						return;
					}
					_selectedField->setSelected(0);
				}
				else if (currentField->getType() == getPlayerType()) {
					if (_selectedField == currentField) {
						_selectedField->changeSelected();
					}
					else
					{
						_selectedField->setSelected(0);
						_selectedField = currentField;
						_selectedField->setSelected(1);
					}

				}
				else {
					_selectedField->setSelected(0);
					_selectedField = nullptr;//null mb

				}
			}
			else {
				if (currentField->getType() == Field::Type::NONE) {
					_selectedField->setSelected(0);
					_selectedField = nullptr;
				}
				else
					_selectedField->setSelected(1);
			}
		}

	}
	CCLOG("select");

}

void GameMaster::move(Field* field) {
	field->setType(getPlayerType());
	_selectedField->setType(Field::Type::NONE);
	_selectedField->setSelected(0);
	field->setSelected(0);
	_selectedField = nullptr;
	checkWins(Field::Type::WHITE);
	_ai.get()->play();
	checkWins(Field::Type::BLACK);
}

void GameMaster::checkWins(Field::Type type) {
	if (Field::Type::BLACK == type) {
		bool isWin=std::all_of(START_WHITE_POSITION.begin(), START_WHITE_POSITION.end(), [this, type](uint8_t i) {
			return getFieldWithNum(i)->getType() == type;
		});
		if (!isWin)return;
		_gameEnd = true;
		std::string win = "Black WIN!!!";
		auto label = Label::createWithTTF(win, "fonts/Marker Felt.ttf", 44);
		label->setPosition(Vec2(400, 400));
		addChild(label, 3);

		// add the label as a child to this layer
	   // this->addChild(label, 1);
	}


	if (Field::Type::WHITE == type) {
		bool isWin = std::all_of(START_BLACK_POSITION.begin(), START_BLACK_POSITION.end(), [this, type](uint8_t i) {
			return getFieldWithNum(i)->getType() == type;
		});
		if (!isWin)return;
		_gameEnd = true;
		std::string win = "White WIN!!!";
		auto label = Label::createWithTTF(win, "fonts/Marker Felt.ttf", 44);
		label->setPosition(Vec2(400,400));
		addChild(label, 3);
		// add the label as a child to this layer
	   // this->addChild(label, 1);


	}

}





NS_CC_END