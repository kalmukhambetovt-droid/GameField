#pragma once
#include "Unit.h"
#include <vector>
#include <memory>

class GameFieldIterator {
private:
    std::vector<std::unique_ptr<Unit>>::iterator current;
    std::vector<std::unique_ptr<Unit>>::iterator end;

public:
    GameFieldIterator(std::vector<std::unique_ptr<Unit>>::iterator current,
        std::vector<std::unique_ptr<Unit>>::iterator end)
        : current(current), end(end) {
    }

    // достаем текущего юнита
    Unit* operator*() const {
        return current->get();
    }

    // переходим к следующему
    GameFieldIterator& operator++() {
        ++current;
        return *this;
    }

    bool operator!=(const GameFieldIterator& other) const {
        return current != other.current;
    }
};