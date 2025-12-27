#include <iostream>
#include <sstream>
#include <random>
#include <map>
#include <iomanip>

#include "dice.h"

std::vector<Die> parseStringToDice(const std::string& dicesString)
{
    std::vector<Die> diceGroups;
    std::stringstream ss(dicesString);
    std::string diceGroupString;
    while (std::getline(ss, diceGroupString, ','))
    {
        Die dice = { 1, 0, 0 };
        std::stringstream diceGroupSs(diceGroupString);
        std::string dicePart;
        bool hasD = false;
        char modSign = '+';

        while (std::getline(diceGroupSs, dicePart, 'd'))
        {
            if (!hasD)
            {
                if (!dicePart.empty())
                {
                    dice.count = std::stoi(dicePart);
                }
                hasD = true;
            }
            else
            {
                size_t modPos = dicePart.find('+');
                if (modPos == std::string::npos) {
                    modPos = dicePart.find('-');
                    if (modPos != std::string::npos)
                    {
                        modSign = '-';
                    }
                }
                if (modPos != std::string::npos)
                {
                    dice.sides = std::stoi(dicePart.substr(0, modPos));
                    int modValue = std::stoi(dicePart.substr(modPos + 1));
                    dice.mod = (modSign == '+') ? modValue : -modValue;
                }
                else
                {
                    dice.sides = std::stoi(dicePart);
                }
            }
        }
        diceGroups.push_back(dice);
    }
    return diceGroups;
}

std::string parseDiceToString(const std::vector<Die>& diceGroups)
{
    std::stringstream ss;
    for (size_t i = 0; i < diceGroups.size(); i++)
    {
        if (i > 0)
        {
            ss << ",";
        }
        ss << diceGroups[i].count << "d" << diceGroups[i].sides;
        if (diceGroups[i].mod != 0) 
        {
            ss << (diceGroups[i].mod > 0 ? "+" : "-") << diceGroups[i].mod;
        }
    }
    return ss.str();
}

int dice(const std::string& dicesString)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int total = 0;
    std::vector<Die> diceGroups = parseStringToDice(dicesString);
    for (const Die& diceGroup : diceGroups)
    {
        for (int i = 0; i < diceGroup.count; i++)
        {
            std::uniform_int_distribution<> dist(1, diceGroup.sides);
            total += dist(gen);
        }
        total += diceGroup.mod;
    }
    return total;
}

void investigateDistribution(const std::string& dicesString, int nSimulation)
{
    std::vector<Die> diceGroups = parseStringToDice(dicesString);
    int minSum = 0;
    int maxSum = 0;
    for (const Die& diceGroup : diceGroups)
    {
        minSum += diceGroup.count * 1 + diceGroup.mod;
        maxSum += diceGroup.count * diceGroup.sides + diceGroup.mod;
    }

    std::map<int, int> frequencies;
    for (int i = 0; i < nSimulation; i++)
    {
        int result = dice(dicesString);
        frequencies[result]++;
    }

    std::cout << "Распределение для " << dicesString << " (" << nSimulation << " симуляций):" << std::endl;
    int barLength = 100;
    for (int sum = minSum; sum <= maxSum; sum++)
    {
        if (frequencies[sum] > 0)
        {
            double probability = static_cast<double>(frequencies[sum]) / nSimulation;
            int nStar = static_cast<int>(probability * barLength);
            std::cout << std::setw(3) << sum << ": " << std::string(nStar, '*')
                << " (" << std::fixed << std::setprecision(2) << probability * 100 << "%)" << std::endl;
        }
    }
    std::cout << std::endl;
}