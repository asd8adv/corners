
#include "AIPlayer.h"
#include "GameMaster.h"


NS_CC_BEGIN


/***************
class AIPlayer
***************/

AIPlayer::AIPlayer(GameMaster* gm) :_gm(gm) {
	_target = std::make_shared<AITarget>(AITarget());
	_base = std::make_shared<AIBased>(AIBased());
	_support = std::make_shared<Support>(Support());

	for (auto it : START_BLACK_POSITION) {
		Field* field = _gm->getFieldWithNum(it);
		_chekers.push_back(AIChecker(field, _gm));
	}

}

bool AIPlayer::tryMove(AIChecker& Checker, AIChecker::Direction direction, bool anyway, bool isLast) {
	auto move = Checker.getMoveForDirection(direction);
	auto pos = Checker._body->getPosition();
	auto field = GameMaster::getFieldIdWithPos(pos.x, pos.y);
	auto resultPos = field + move;
	bool correct = GameMaster::isCorrectField(resultPos);
	auto fieldId = _gm->getNumWithFieldPos(resultPos.x, resultPos.y);
	if (correct && Checker.isfieldAvialable(fieldId)) {
		auto nextField = _gm->getFieldWithNum(fieldId);
		if(isLast&& !anyway){
			if (targetÑollision(Checker._body->getFieldId()) < targetÑollision(nextField->getFieldId())) {
				Checker.move(nextField);
				return true;
			}
		}
		else {
			Checker.move(nextField);
			return true;
		}
	}
	return false;
}

void AIPlayer::play(bool anyway) {
	for (int8_t k = 0; k < 9; k++) {
		for (int8_t i = 0; i < 9; i++) {
			for (auto& it : _chekers) {
				auto direction = AIChecker::Direction(i);
				int8_t tk = targetÑollision(it._body->getFieldId());
				
				auto kol = (tk == k);
				bool isLast = (1);
				if (tryMove(it, direction, anyway,isLast)) {
				return;
				}
			}
		}

	}
	if (anyway) {
		CCASSERT(false, "pat");
	}
	else
		play(true);
}


int8_t AIPlayer::targetÑollision(uint8_t id)  const {
	TargetZone neutral1{ 59,51,43,35,27,28,29,30,31 };
	TargetZone neutral2{ 60,39 };
	TargetZone neutral4{ 36,28,29 };
	TargetZone neutral3{ 52,38 };

	bool a = std::any_of(_target->zone_A._zone.begin(), _target->zone_A._zone.end(), [id](uint8_t i) {
		return i == id;
		});
	if (a) return 8;

	bool b = std::any_of(_target->zone_B._zone.begin(), _target->zone_B._zone.end(), [id](uint8_t i) {
		return i == id;
		});
	if (b) return 7;

	bool c = std::any_of(_target->zone_C._zone.begin(), _target->zone_C._zone.end(), [id](uint8_t i) {
		return i == id;
		});
	if (c) return 6;

	bool d = std::any_of(neutral1._zone.begin(), neutral1._zone.end(), [id](uint8_t i) {
		return i == id;
		});
	if (d) return 2;

	bool h = std::any_of(neutral2._zone.begin(), neutral2._zone.end(), [id](uint8_t i) {
		return i == id;
		});
	if (h) return 3;

	bool f = std::any_of(neutral3._zone.begin(), neutral3._zone.end(), [id](uint8_t i) {
		return i == id;
		});
	if (f) return 4;

	bool g = std::any_of(neutral4._zone.begin(), neutral4._zone.end(), [id](uint8_t i) {
		return i == id;
		});
	if (g) return 5;


	bool e = std::any_of(START_BLACK_POSITION.begin(), START_BLACK_POSITION.end(), [id](uint8_t i) {
		return i == id;
		});
	if (e) return 0;


	return 1;
}

/***************
class AIChecker
***************/

bool AIChecker::isfieldAvialable(uint8_t id) const {
	Field* field = _gm->getFieldWithNum(id);
	CCASSERT(field != nullptr, "field is nullptr");
	bool Uniq = (field->getFieldId() != _body->getFieldId());
	bool correctMove = _gm->isCorrectMove((field->getPosition() - _body->getPosition()) / 100);
	bool correctField = _gm->isCorrectField(field->getPosition() / 100);
	bool emptyField = field->getType() == Field::Type::NONE;
	return Uniq && correctMove && correctField && emptyField;
}

void AIChecker::move(Field* f) {
	_body->setType(Field::Type::NONE);
	_body = f;
	_body->setType(Field::Type::BLACK);
}





NS_CC_END