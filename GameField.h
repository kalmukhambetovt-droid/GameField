#pragma once
#include "Unit.h"
#include "UnitFactory.h"
#include "GameFieldIterator.h" 
#include <vector>
#include <memory>
#include <iostream>

class GameField {
private:
    int width;
    int height;
    int maxUnits;

    // хранение юнитов в векторе умных указателей
    std::vector<std::unique_ptr<Unit>> units;

public:
    GameField(int w, int h, int max);

    // правило пяти
    ~GameField();
    GameField(const GameField& other);
    GameField& operator=(const GameField& other);
    GameField(GameField&& other) noexcept;
    GameField& operator=(GameField&& other) noexcept;

    void addUnit(std::unique_ptr<Unit> unit);
    void addUnit(const UnitFactory& factory, UnitType type, int x, int y); 
    void removeUnit(int x, int y);
    Unit* getUnit(int x, int y) const;
    Unit& getUnit(size_t index); 

    int getWidth() const;
    int getHeight() const;
    int size() const;
    bool empty() const;
    void clear();

    bool inBounds(int x, int y) const; 
    bool isCellFree(int x, int y) const; 
    void removeDead(); 
    bool moveUnit(size_t index, int dx, int dy); 
    void print(std::ostream& os = std::cout) const;

    GameFieldIterator begin();
    GameFieldIterator end();
   
};