#pragma once
#include "Unit.h"
#include <memory>

// класс Пехота
class Infantry : public Unit {
protected:
    Infantry(const Health& h, const Armor& a, const Attack& att, int x, int y)
        : Unit(h, a, att, x, y) {
    }
};

// мечник
class Swordsman : public Infantry {
public:
    Swordsman(int x, int y)
        : Infantry(Health(100), Armor(15), Attack(10), x, y) {
    }

    std::string getType() const override {
        return "Swordsman";
    }

    char getSymbol() const override { return 'S'; }

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<Swordsman>(*this);
    }
};

// копейщик
class Spearman : public Infantry {
public:
    Spearman(int x, int y)
        : Infantry(Health(80), Armor(10), Attack(15), x, y) {
    }

    std::string getType() const override {
        return "Spearman";
    }
    char getSymbol() const override { return 'P'; }

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<Spearman>(*this);
    }
};