#include <iostream>

#include "dice.h"

int main() 
{
    setlocale(LC_ALL, "");

    // Пример использования
    std::string exampleDicesString = "2d6+2,3d10";
    int result = dice(exampleDicesString);
    std::cout << "Результат броска для \"" << exampleDicesString << "\": " << result << std::endl;

    // Преобразование обратно в строку
    std::vector<Die> parsedDiceGroups = parseStringToDice(exampleDicesString);
    std::string backToDicesString = parseDiceToString(parsedDiceGroups);
    std::cout << "Обратно в строку: " << backToDicesString << std::endl;

    // Исследование распределений
    std::vector<std::string> dicesStrings = { "1d6", "2d6", "3d6", "1d10", "2d10", "3d10" };
    for (const std::string& dicesString : dicesStrings) 
    {
        investigateDistribution(dicesString);
    }

    return 0;
}