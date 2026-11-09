#pragma once
#include "Unit.h"
#include <memory>

// конница
class Cavalry : public Unit {
protected:
    Cavalry(const Health& h, const Armor& a, const Attack& att, int x, int y)
        : Unit(h, a, att, x, y) {
    }
};

// тяжёлая конница
class Cataphract : public Cavalry {
public:
    Cataphract(int x, int y)
        : Cavalry(Health(150), Armor(20), Attack(15), x, y) {
    }

    std::string getType() const override {
        return "Cataphract";
    }

    char getSymbol() const override { return 'C'; }

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<Cataphract>(*this);
    }
};

// конный лучник(всадник)
class HorseArcher : public Cavalry {
public:
    HorseArcher(int x, int y)
        : Cavalry(Health(60), Armor(5), Attack(12), x, y) {
    }

    std::string getType() const override {
        return "HorseArcher";
    }

    char getSymbol() const override { return 'R'; }

    std::unique_ptr<Unit> clone() const override {
        return std::make_unique<HorseArcher>(*this);
    }
};