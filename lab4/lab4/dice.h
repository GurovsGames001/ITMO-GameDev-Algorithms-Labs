#pragma once
#include <vector>
#include <string>

struct Die {
    int count;
    int sides;
    int mod;
};

// Функция для парсинга строки в вектор структур Die
std::vector<Die> parseStringToDice(const std::string& dicesString);

// Функция для преобразования вектора Die обратно в строку
std::string parseDiceToString(const std::vector<Die>& diceGroups);

// Функция для симуляции броска костей
int dice(const std::string& dicesString);

// Функция для исследования распределения
void investigateDistribution(const std::string& dicesString, int nSimulation = 10000);