#pragma once
#include "Unit.h"
#include <memory>

// лучник
class Archer : public Unit {
protected:
    Archer(const Health& h, const Armor& a, const Attack& att, int x, int y)
        : Unit(h, a, att, x, y) {
    }
};

// лёгкий лучник
class LightArcher : public Archer {
public:
    LightArcher(int x, int y)
        : Archer(Health(50), Armor(5), Attack(12), x, y) {
    }

    std::string getType() const override {
        return "LightArcher";
    }

    char getSymbol() const override { return 'L'; } 

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<LightArcher>(*this);
    }
};

// тяжёлый лучник
class HeavyArcher : public Archer {
public:
    HeavyArcher(int x, int y)
        : Archer(Health(70), Armor(10), Attack(10), x, y) {
    }

    std::string getType() const override {
        return "HeavyArcher";
    }

    char getSymbol() const override { return 'H'; } 

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<HeavyArcher>(*this);
    }
};