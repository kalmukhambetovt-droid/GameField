#pragma once
#include "Health.h"
#include "Armor.h"
#include "Attack.h"
#include <string>
#include <memory> 

class Unit {
public:
    // виртуальный деструктор
    virtual ~Unit() = default;

    // виртуальные методы 

    virtual std::unique_ptr<Unit> clone() const = 0;
    virtual std::string getType() const = 0;

    virtual char getSymbol() const = 0;

    int getX() const { return x; }
    int getY() const { return y; }

    bool isAlive() const { return !health.isZero(); }

    void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }

    bool move(int dx, int dy, int fieldWidth, int fieldHeight);

    // сначала броня уменьшает урон, потом падает здоровье
    void takeDamage(int rawDamage);

    // const, так как атакующий не меняет своё состояние при атаке
    void attackTarget(Unit& target) const;

    // лечение
    void heal(int amount);

    // описание юнита для вывода на экран
    std::string describe() const;

protected:
    Unit(const Health& h, const Armor& a, const Attack& att, int startX, int startY);

    // конструктор копирования 
    Unit(const Unit& other) = default;

    Health health;
    Armor armor;
    Attack attack;
    int x;
    int y;
};
