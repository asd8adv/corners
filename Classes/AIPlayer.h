#pragma once
#include "GameScene.h"
#include <vector>
#include <algorithm>
#include <random>


class Support {
	std::mt19937 _rands;
public:
	Support() {
		std::random_device rd;
		_rands = std::mt19937(rd());
	}


	int32_t Support::getRandomNumber(int32_t lower, int32_t upper = 0) {
		auto num = _rands();
		if (upper != 0) {
			if (lower > upper) {
				return 0;
			}
			auto diff = upper - lower;
			return lower + num % (diff + 1);
		}
		else {
			return num % (lower + 1);
		}
	}
};

static const std::vector<uint8_t> START_BLACK_POSITION{
	0,1,2,
	8,9,10,
	16,17,18 };

static const std::vector<uint8_t> START_WHITE_POSITION{
	61,62,63,
	53,54,55,
	45,46,47
};

NS_CC_BEGIN

struct TargetZone {
	std::vector<uint8_t> _zone;
	bool _isFull;
	TargetZone(std::initializer_list<uint8_t> a) :_zone(a), _isFull(0)
	{
	}

};

struct AIBased {
	TargetZone zone_A;
	TargetZone zone_B;
	TargetZone zone_C;

	AIBased() :
		zone_A{ 16,17,18 },
		zone_B{ 8,9,10 },
		zone_C{ 0,1,2 }
	{
	}
};

struct AITarget {
	TargetZone zone_A;
	TargetZone zone_B;
	TargetZone zone_C;

	AITarget() :
		zone_A{ 55,62,63 },
		zone_B{ 47,54,61 },
		zone_C{ 45,46,53 }
	{
	}
};

struct AIChecker {
	GameMaster* _gm;
	Field* _body;

	enum class Direction :int8_t {
		/*********
		*NW N NE *
		*W  0  E *
		*SW S SE *
		*********/

		NE,
		N,
		E,
		NW,
		SE,
		W,
		SW,
		S,
	};

	AIChecker(Field* b, GameMaster* gm) :_body(b), _gm(gm)
	{}

	bool isfieldAvialable(uint8_t id);

	static Vec2 getMoveForDirection(Direction dr) {
		switch (dr) {
		case Direction::NE:
			return Vec2(1, 1);

		case Direction::N:
			return Vec2(0, 1);

		case Direction::E:
			return Vec2(1, 0);

		case Direction::NW:
			return Vec2(-1, 1);

		case Direction::SE:
			return Vec2(1, -1);

		case Direction::W:
			return Vec2(-1, 0);

		case Direction::SW:
			return Vec2(-1, -1);

		case Direction::S:
			return Vec2(0, -1);

		default: return Vec2::ZERO;
		}
	}

	void move(Field* f);
};


class AIPlayer {
	bool _aZoneFull;
	bool _bZoneFull;
	bool _isAllNeutralField;
	std::shared_ptr<Support> _support;
	std::shared_ptr<AITarget> _target;
	std::shared_ptr<AIBased> _base;
	std::vector<AIChecker> _chekers;
	GameMaster* _gm;
public:
	AIPlayer(GameMaster* gm);

	int8_t target—ollision(uint8_t id);

	std::shared_ptr<AITarget> getTarget() {
		return std::shared_ptr<AITarget>(_target);
	}

	std::shared_ptr<AIBased> getBase() {
		return std::shared_ptr<AIBased>(_base);
	}

	bool tryMove(AIChecker& Checker, AIChecker::Direction direction, bool anyway, bool isLast = false);

	void play(bool anyway = false);

};


NS_CC_END