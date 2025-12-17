#include <iostream>
#include "HammurabiGameMode.h"

int main()
{
    setlocale(LC_ALL, "");

    hammurabi::HammurabiGameMode* gameMode = new hammurabi::HammurabiGameMode;
    gameMode->startGame();
    return 0;
}