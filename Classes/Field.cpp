#include "Field.h"
#include "GameMaster.h"

NS_CC_BEGIN

Field::Field() {
    Node::setContentSize(Size(100, 100));
    _white = cocos2d::Sprite::create("white.png");
    addChild(_white, 1, "white");
    _whiteSelected = cocos2d::Sprite::create("white_selected.png");
    addChild(_whiteSelected, 1, "white_selected");
    _black = cocos2d::Sprite::create("black.png");
    addChild(_black, 1, "black");
    _BlackSelected = cocos2d::Sprite::create("black_selected.png");
    addChild(_BlackSelected, 1, "black_selected");

    auto ss = MenuItemImage::create("zero.png", "zero.png", [this](Ref* sender) {
        if (auto parent = getParent()) {
            auto result = dynamic_cast<GameMaster*>(parent);
            result->onSelected(_num);
        }
     });

    _invisibleBtn = Menu::create(ss, NULL);
    _invisibleBtn->setPosition(0, 0);
    addChild(_invisibleBtn, 5, "invisible");
    _isSelected = 0;
    setType(Type::NONE);
}

void Field::changeTypeOrSelected() {
    _white->setVisible(_fieldType == Type::WHITE && !_isSelected);
    _whiteSelected->setVisible(_fieldType == Type::WHITE && _isSelected);
    _black->setVisible(_fieldType == Type::BLACK && !_isSelected);
    _BlackSelected->setVisible(_fieldType == Type::BLACK && _isSelected);

}

void Field::createInvisibleButton() {
    auto ss = MenuItemImage::create("zero.png", "zero.png", [this](Ref* sender) {
        CCLOG("boom");
        setSelected(!_isSelected);
    });
    _invisibleBtn = Menu::create(ss, NULL);
}




NS_CC_END