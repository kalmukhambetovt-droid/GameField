#pragma once
#include <stdexcept>
#include "Armor.h"
// сила атаки юнита
class Attack {
private:
    int value;

public:
    Attack(int startValue) {
        if (startValue < 0) {
            throw std::invalid_argument("Атака не может быть отрицательной");
        }
        value = startValue;
    }

    // учитывает броню цели и возвращает реальный урон
    int calculateDamage(const Armor& targetArmor) const {
        return targetArmor.reduceDamage(value);
    }

    int getValue() const {
        return value;
    }
};
