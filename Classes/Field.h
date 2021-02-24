#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

NS_CC_BEGIN

class Field : public Node {
public:
    enum class Type {
        NONE,
        WHITE,
        BLACK
    };

protected:
    uint8_t _num;
    Type _fieldType;
    bool _isSelected;

    cocos2d::Menu* _invisibleBtn;

    cocos2d::Sprite* _white;
    cocos2d::Sprite* _whiteSelected;
    cocos2d::Sprite* _black;
    cocos2d::Sprite* _BlackSelected;
public:

    static Field* create() {
        return new Field;
    }

    Field();

    void setFieldId(uint8_t id) {
        _num = id;
    }

    uint8_t getFieldId() {
        return _num;
    }

    void setType(Type type) {
        _fieldType = type;
        changeTypeOrSelected();
    }

    Type getType() {
        return _fieldType;
    }

    void changeSelected() {
        setSelected(!_isSelected);
    }

    void setSelected(bool selected) {
        _isSelected = selected;
        changeTypeOrSelected();
    }

    void changeTypeOrSelected();


    bool getSelected() {
        return _isSelected;
    }

protected:
    void createInvisibleButton();
};

NS_CC_END