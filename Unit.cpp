#include "Unit.h"
#include <sstream>

Unit::Unit(const Health& h, const Armor& a, const Attack& att, int startX, int startY)
    : health(h), armor(a), attack(att), x(startX), y(startY) {
}

bool Unit::move(int dx, int dy, int fieldWidth, int fieldHeight) {
    int newX = x + dx;
    int newY = y + dy;

    if (newX >= 0 && newX < fieldWidth && newY >= 0 && newY < fieldHeight) {
        x = newX;
        y = newY;
        return true; 
    }

    return false;
}

void Unit::takeDamage(int rawDamage) {
    // сначала броня поглощает часть урона
    int actualDamage = armor.reduceDamage(rawDamage);
    // затем здоровье уменьшается на остаток
    health.decrease(actualDamage);
}

void Unit::attackTarget(Unit& target) const {
    if (this->isAlive() && target.isAlive()) {
        // получаем силу своей атаки и передаём цели
        target.takeDamage(attack.getValue());
    }
}

void Unit::heal(int amount) {
    if (amount > 0) {
        health.increase(amount);
    }
}

std::string Unit::describe() const {
    std::ostringstream out;
    out << getType()
        << " at (" << x << "," << y << ")"
        << " | HP: " << health.getValue()
        << " | Armor: " << armor.getValue()
        << " | Attack: " << attack.getValue();
    return out.str();
}



