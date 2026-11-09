#pragma once
#include <stdexcept>
// броня юнита
// поглощает часть урона, но не может поглотить больше, чем сама броня
class Armor {
private:
	int value;
public:
	Armor(int startValue) {
		if (startValue < 0) {
			throw std::invalid_argument("Броня не может быть отрицательной");
		}
		else {
			value = startValue;
		}
	}
	// сколько реального урона нанесется после учета брони
	int reduceDamage(int amount) const {
		if (amount < 0) {
			throw std::invalid_argument("Урон не может быть отрицательным");
		}
		int result = amount - value;
		if (result < 0) {
			return 0;
		}
		return result;
	}
	int getValue() const {
		return value;
	}
};