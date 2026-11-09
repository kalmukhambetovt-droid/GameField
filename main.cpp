#include <iostream>
#include <string>
#include <utility>
#include <clocale>
#include "GameField.h"
#include "UnitFactory.h"
#include "Infantry.h"
#include "Archer.h"
#include "Cavalry.h"

// функция для вывода заголовка сценария
void printScenario(const std::string& title) {
    std::cout << "\n" << title << "\n";
}
// функция для вывода состояния поля
void printField(const std::string& title, const GameField& field) {
    std::cout << "[" << title << "]\n";
    field.print(std::cout);
    std::cout << "Всего юнитов на поле: " << field.size() << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << std::boolalpha;

    // СЦЕНАРИЙ 1: создание поля и наполнение через фабрики
    printScenario("СЦЕНАРИЙ 1: Создание поля и работа фабрик");

    GameField field(8, 6, 10); // ширина 8, высота 6, макс юнитов 10

    InfantryFactory infantryFactory;
    ArcherFactory archerFactory;
    CavalryFactory cavalryFactory;

    // наполнения поля через фабрики
    field.addUnit(infantryFactory, UnitType::Swordsman, 0, 0);
    field.addUnit(infantryFactory, UnitType::Spearman, 1, 0);
    field.addUnit(archerFactory, UnitType::LightArcher, 2, 2);
    field.addUnit(archerFactory, UnitType::HeavyArcher, 3, 2);
    field.addUnit(cavalryFactory, UnitType::Cataphract, 5, 4);
    field.addUnit(cavalryFactory, UnitType::HorseArcher, 6, 4);

    printField("Поле после добавления 6 юнитов", field);

    // демонстрация защиты фабрики
    std::cout << "\n[Тест защиты фабрики] Попытка создать Лучника через Фабрику Пехоты:\n";
    try {
        infantryFactory.createUnit(0, 0, UnitType::LightArcher);
    }
    catch (const std::exception& e) {
        std::cout << "-> Ожидаемая ошибка перехвачена: " << e.what() << "\n";
    }

    // СЦЕНАРИЙ 2: глубокое копирование и независимость объектов
    printScenario("СЦЕНАРИЙ 2: Глубокое копирование (Rule of 5)");

    std::cout << "Характеристики Swordsman в ОРИГИНАЛЕ до изменений:\n";
    std::cout << " -> " << field.getUnit(0).describe() << "\n";

    GameField fieldCopy = field;

    std::cout << "\nНаносим 40 урона Swordsman в КОПИИ поля...\n";
    fieldCopy.getUnit(0).takeDamage(40);

    std::cout << "Характеристики Swordsman в КОПИИ после урона:\n";
    std::cout << " -> " << fieldCopy.getUnit(0).describe() << "\n";

    std::cout << "Характеристики Swordsman в ОРИГИНАЛЕ (должны остаться прежними):\n";
    std::cout << " -> " << field.getUnit(0).describe() << "\n";

    if (field.getUnit(0).describe() != fieldCopy.getUnit(0).describe()) {
        std::cout << "\n[УСПЕХ] Глубокое копирование работает корректно: объекты независимы.\n";
    }

    
    // СЦЕНАРИЙ 3: семантика перемещения и движение юнитов
    printScenario("СЦЕНАРИЙ 3: Семантика перемещения и движение юнитов");

    std::cout << "Состояние fieldCopy ПЕРЕД перемещением владения: " << fieldCopy.size() << " юнитов.\n";

    GameField movedField = std::move(fieldCopy);

    std::cout << "Состояние fieldCopy ПОСЛЕ std::move: " << fieldCopy.size() << " юнитов (опустошено).\n";
    std::cout << "Состояние movedField после принятия владения: " << movedField.size() << " юнитов.\n";

    std::cout << "\nПеремещаем Swordsman (индекс 0) на 1 клетку вниз (dy=1)...\n";
    bool moveSuccess = movedField.moveUnit(0, 0, 1);
    std::cout << "Результат перемещения: " << (moveSuccess ? "Успешно" : "Невозможно") << "\n";

    printField("Поле после перемещения юнита", movedField);

   
    // СЦЕНАРИЙ 4: итератор, массовое действие и удаление погибших
    printScenario("СЦЕНАРИЙ 4: Кастомный итератор и зачистка поля");

    std::cout << "Обход поля итератором и нанесение фатального урона (999) всем:\n";

    for (GameFieldIterator it = movedField.begin(); it != movedField.end(); ++it) {
        Unit* currentUnit = *it; 
        std::cout << " -> Атакуем: " << currentUnit->getType()
            << " на (" << currentUnit->getX() << "," << currentUnit->getY() << ")\n";
        currentUnit->takeDamage(999);
    }

    std::cout << "\nВызов метода removeDead() для очистки поля от погибших...\n";
    movedField.removeDead();

    printField("Поле после зачистки (должно быть пустым)", movedField);
    std::cout << "Поле пустое? " << movedField.empty() << "\n";

 
    std::cout << " Все демонстрационные сценарии успешно завершены!\n";

    return 0;
}