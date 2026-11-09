#pragma once
#include "Unit.h"
#include "Infantry.h"
#include "Archer.h"
#include "Cavalry.h"
#include <memory>
// выбран Фабричный метод, так как требуется создание конкретного юнита по типу, а не семейство связанных между собой объектов
// enum class как замена строкам, защищает от опечаток
enum class UnitType {
    Swordsman, Spearman,
    LightArcher, HeavyArcher,
    Cataphract, HorseArcher
};

class UnitFactory {
public:
    virtual ~UnitFactory() = default;

    virtual std::unique_ptr<Unit> createUnit(int x, int y, UnitType type) const = 0;
};

// фабрика пехоты
class InfantryFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(int x, int y, UnitType type) const override;
};

// фабрика лучников
class ArcherFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(int x, int y, UnitType type) const override;
};

// фабрика конницы
class CavalryFactory : public UnitFactory {
public:
    std::unique_ptr<Unit> createUnit(int x, int y, UnitType type) const override;
};