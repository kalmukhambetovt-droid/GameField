#include "UnitFactory.h"
#include <stdexcept>

std::unique_ptr<Unit> InfantryFactory::createUnit(int x, int y, UnitType type) const {
    if (type == UnitType::Swordsman) {
        return std::make_unique<Swordsman>(x, y);
    }
    else if (type == UnitType::Spearman) {
        return std::make_unique<Spearman>(x, y);
    }
    else {
        throw std::invalid_argument("Неверный тип юнита для фабрики пехоты");
    }
}

std::unique_ptr<Unit> ArcherFactory::createUnit(int x, int y, UnitType type) const {
    if (type == UnitType::LightArcher) {
        return std::make_unique<LightArcher>(x, y);
    }
    else if (type == UnitType::HeavyArcher) {
        return std::make_unique<HeavyArcher>(x, y);
    }
    else {
        throw std::invalid_argument("Неверный тип юнита для фабрики лучников");
    }
}

std::unique_ptr<Unit> CavalryFactory::createUnit(int x, int y, UnitType type) const {
    if (type == UnitType::Cataphract) {
        return std::make_unique<Cataphract>(x, y);
    }
    else if (type == UnitType::HorseArcher) {
        return std::make_unique<HorseArcher>(x, y);
    }
    else {
        throw std::invalid_argument("Неверный тип юнита для фабрики конницы");
    }
}