#pragma once
#include <stdexcept>
// здоровье юнита, хранит текущее и максимальное значение здоровья
class Health {
private:
	int value;
public:
	Health(int startValue) {
		if (startValue <= 0) {
			throw std::invalid_argument("Здоровье не может быть отрицательным");
		}
		else {
			value = startValue;
		}
	}
// decrease и increase изменяют здоровье с проверкой границ, чтобы значение не уходило в минус и не превышало максимум
	void decrease(int amount) {
		if (amount < 0) {
			throw std::invalid_argument("Урон не может быть отрицательным");
		}
		value = value - amount;
		if (value < 0) {
			value = 0;
		}
	}
	void increase(int amount) {
		if (amount < 0) {
			throw std::invalid_argument("Лечение не может быть отрицательным");
		}
		value = value + amount;
	}
	bool isZero() const {
		return value == 0; 
	}
	int getValue() const {
		return value;
	}
};