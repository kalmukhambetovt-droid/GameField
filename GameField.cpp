#include "GameField.h"
#include "UnitFactory.h" 
#include <algorithm>
#include <stdexcept>
#include <iostream>

GameField::GameField(int w, int h, int max)
    : width(w), height(h), maxUnits(max) {
    if (w <= 0 || h <= 0 || max <= 0) {
        throw std::invalid_argument("Размеры поля и лимит юнитов должны быть больше нуля");
    }
}

GameField::~GameField() {
}

// проходим по всем юнитам и вызываем clone() для каждого, так как unique_ptr нельзя скопировать
GameField::GameField(const GameField& other)
    : width(other.width), height(other.height), maxUnits(other.maxUnits) {
    for (size_t i = 0; i < other.units.size(); ++i) {
        if (other.units[i]) {
            units.push_back(other.units[i]->clone());
        }
    }
}

// оператор присваивания копированием
GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        units.clear();
        width = other.width;
        height = other.height;
        maxUnits = other.maxUnits;

        for (size_t i = 0; i < other.units.size(); ++i) {
            if (other.units[i]) {
                units.push_back(other.units[i]->clone());
            }
        }
    }
    return *this;
}

GameField::GameField(GameField&& other) noexcept
    : width(other.width), height(other.height), maxUnits(other.maxUnits),
    units(std::move(other.units)) {
    other.width = 0;
    other.height = 0;
    other.maxUnits = 0;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        units.clear();
        width = other.width;
        height = other.height;
        maxUnits = other.maxUnits;
        units = std::move(other.units);

        other.width = 0;
        other.height = 0;
        other.maxUnits = 0;
    }
    return *this;
}

bool GameField::inBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool GameField::isCellFree(int x, int y) const {
    for (size_t i = 0; i < units.size(); ++i) {
        if (units[i]->getX() == x && units[i]->getY() == y) {
            return false;
        }
    }
    return true;
}

void GameField::addUnit(std::unique_ptr<Unit> unit) {
    if (!unit) {
        throw std::invalid_argument("Нельзя добавить пустой указатель на юнита");
    }
    if (units.size() >= static_cast<size_t>(maxUnits)) {
        throw std::length_error("Достигнут максимальный лимит юнитов на поле");
    }
    if (!inBounds(unit->getX(), unit->getY())) {
        throw std::out_of_range("Координаты юнита выходят за границы поля");
    }
    if (!isCellFree(unit->getX(), unit->getY())) {
        throw std::logic_error("Ячейка с такими координатами уже занята");
    }

    units.push_back(std::move(unit));
}

void GameField::addUnit(const UnitFactory& factory, UnitType type, int x, int y) {
    std::unique_ptr<Unit> unit = factory.createUnit(x, y, type);
    addUnit(std::move(unit));
}

void GameField::removeUnit(int x, int y) {
    for (size_t i = 0; i < units.size(); ++i) {
        if (units[i]->getX() == x && units[i]->getY() == y) {
            units.erase(units.begin() + i);
            return;
        }
    }
}

Unit* GameField::getUnit(int x, int y) const {
    for (size_t i = 0; i < units.size(); ++i) {
        if (units[i]->getX() == x && units[i]->getY() == y) {
            return units[i].get();
        }
    }
    return nullptr;
}

Unit& GameField::getUnit(size_t index) {
    if (index >= units.size()) {
        throw std::out_of_range("Неправильный индекс юнита");
    }
    return *units[index];
}

int GameField::getWidth() const { return width; }
int GameField::getHeight() const { return height; }
int GameField::size() const { return static_cast<int>(units.size()); }
bool GameField::empty() const { return units.empty(); }

void GameField::clear() {
    units.clear();
}

void GameField::removeDead() {
    for (size_t i = units.size(); i-- > 0; ) {
        if (!units[i]->isAlive()) {
            units.erase(units.begin() + i);
        }
    }
}

bool GameField::moveUnit(size_t index, int dx, int dy) {
    if (index >= units.size()) return false;

    // запрет перемещения на 0 клеток
    if (dx == 0 && dy == 0) {
        return false;
    }

    Unit& unit = *units[index];
    int nx = unit.getX() + dx;
    int ny = unit.getY() + dy;

    if (!inBounds(nx, ny)) return false;
    if (!isCellFree(nx, ny)) return false;

    return unit.move(dx, dy, width, height);
}

void GameField::print(std::ostream& os) const {
    for (int visualY = 0; visualY < height + 2; ++visualY) {
        for (int visualX = 0; visualX < width + 2; ++visualX) {
            // проверка, является ли клетка границей поля
            bool isBorder = (visualX == 0 || visualX == width + 1 ||
                visualY == 0 || visualY == height + 1);

            if (isBorder) {
                os << "X ";
            }
            else {
                int logicalX = visualX - 1;
                int logicalY = visualY - 1;

                // есть ли юнит на этой логической позиции
                bool unitFound = false;
                for (size_t i = 0; i < units.size(); ++i) {
                    if (units[i]->getX() == logicalX && units[i]->getY() == logicalY) {
                        os << units[i]->getSymbol() << " ";
                        unitFound = true;
                        break;
                    }
                }
                if (!unitFound) {
                    os << "  ";
                }
            }
        }
        os << "\n";
    }
}


GameFieldIterator GameField::begin() {
    return GameFieldIterator(units.begin(), units.end());
}

GameFieldIterator GameField::end() {
    return GameFieldIterator(units.end(), units.end());
}