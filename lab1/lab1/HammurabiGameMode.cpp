#include "HammurabiGameMode.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

namespace hammurabi {
	void HammurabiGameMode::startGame()
	{
		std::srand(std::time(nullptr));

		char choice;

		std::ifstream check(SAVE_FILE);
		bool hasSavedGame = check.good();
		check.close();

		if (hasSavedGame) 
		{
			std::cout << "Есть сохраненная игра. Продолжить? (y/n): ";
			std::cin >> choice;
			if (choice == 'y' || choice == 'Y') 
			{
				loadSavedGame();
			}
			else 
			{
				initNewGame();
			}
		}
		else 
		{
			initNewGame();
		}

		while (gameState_.year_ <= MAX_YEARS) 
		{
			std::cout << "Продолжить правление в год " << gameState_.year_ << "? (y/n): ";
			std::cin >> choice;
			if (choice != 'y' && choice != 'Y') 
			{
				saveGame();
				std::cout << "Игра сохранена. До свидания, повелитель!" << std::endl;
				return;
			}

			bool continue_game = playRound();
			if (!continue_game) 
			{
				return;
			}
			gameState_.year_++;
		}

		finishGame();
		remove(SAVE_FILE.c_str());
	}

	void HammurabiGameMode::initNewGame()
	{
		gameState_.year_ = 1;
		gameState_.peoplePopulation_ = START_PEOPLE_POPULATION;
		gameState_.numberBushelsWheat_ = START_NUMBER_BUSHELS_WHEAT;
		gameState_.numberAcresLand_ = START_NUMBER_ACRES_LAND;

		gameState_.numberPeopleStarvedLastRound_ = 0;
		gameState_.numberPeopleImmigrantsLastRound_ = 0;
		gameState_.wasPlagueLastRound_ = false;
		gameState_.amountWheatHarvested_ = 0;
		gameState_.amountWheatHarvestedPerAcre_ = 0;
		gameState_.amountWheatDestroyedByRats_ = 0;
		gameState_.totalPeopleStarvedPercent_ = 0.0;
	}

	bool HammurabiGameMode::loadSavedGame()
	{
		std::ifstream in(SAVE_FILE, std::ios::binary);
		if (in.is_open()) 
		{
			in >> gameState_.year_;
			in >> gameState_.peoplePopulation_;
			in >> gameState_.numberBushelsWheat_;
			in >> gameState_.numberAcresLand_;
			in >> gameState_.numberPeopleStarvedLastRound_;
			in >> gameState_.numberPeopleImmigrantsLastRound_;
			in >> gameState_.wasPlagueLastRound_;
			in >> gameState_.amountWheatHarvested_;
			in >> gameState_.amountWheatHarvestedPerAcre_;
			in >> gameState_.amountWheatDestroyedByRats_;
			in >> gameState_.totalPeopleStarvedPercent_;
			in.close();
			return true;
		}
		return false;
	}

	bool HammurabiGameMode::saveGame() const
	{
		std::ofstream out(SAVE_FILE, std::ios::binary);
		if (out.is_open()) 
		{
			out << gameState_.year_ << std::endl;
			out << gameState_.peoplePopulation_ << std::endl;
			out << gameState_.numberBushelsWheat_ << std::endl;
			out << gameState_.numberAcresLand_ << std::endl;
			out << gameState_.numberPeopleStarvedLastRound_ << std::endl;
			out << gameState_.numberPeopleImmigrantsLastRound_ << std::endl;
			out << gameState_.wasPlagueLastRound_ << std::endl;
			out << gameState_.amountWheatHarvested_ << std::endl;
			out << gameState_.amountWheatHarvestedPerAcre_ << std::endl;
			out << gameState_.amountWheatDestroyedByRats_ << std::endl;
			out << gameState_.totalPeopleStarvedPercent_ << std::endl;

			out.close();
		}
		return true;
	}

	bool HammurabiGameMode::playRound()
	{
		currentPriceOneAcre_ = randomRange(MIN_ONE_ACRE_PRICE, MAX_ONE_ACRE_PRICE);
		printRoundStats();
		return goToNextRound(enterPlayerValues());
	}

	void HammurabiGameMode::printRoundStats() const
	{
		std::cout << "Мой повелитель, соизволь поведать тебе:" << std::endl;
		std::cout << "В году " << gameState_.year_ << " твоего высочайшего правления" << std::endl;
		if (gameState_.numberPeopleStarvedLastRound_ > 0) 
		{
			std::cout << gameState_.numberPeopleStarvedLastRound_ << " человек умерли от голода;" << std::endl;
		}
		if (gameState_.numberPeopleImmigrantsLastRound_ > 0) 
		{
			std::cout << gameState_.numberPeopleImmigrantsLastRound_ << " человек прибыли в наш великий город;" << std::endl;
		}
		if (gameState_.wasPlagueLastRound_) 
		{
			std::cout << "Чума уничтожила половину населения;" << std::endl;
		}
		std::cout << "Население города сейчас составляет " << gameState_.peoplePopulation_ << " человек;" << std::endl;
		if (gameState_.amountWheatHarvested_ > 0) 
		{
			std::cout << "Мы собрали " << gameState_.amountWheatHarvested_ << " бушелей пшеницы, по "
				<< gameState_.amountWheatHarvestedPerAcre_ << " бушеля с акра;" << std::endl;
		}
		if (gameState_.amountWheatDestroyedByRats_ > 0) 
		{
			std::cout << "Крысы истребили " << gameState_.amountWheatDestroyedByRats_ << " бушелей пшеницы;" << std::endl;
		}
		std::cout << "Город сейчас занимает " << gameState_.numberAcresLand_ << " акров;" << std::endl;
		std::cout << "1 акр земли стоит сейчас " << currentPriceOneAcre_ << " бушель." << std::endl;
	}

	PlayerValues HammurabiGameMode::enterPlayerValues() const
	{
		int32_t numberAcresLandWantsToBuy = -1;
		int32_t numberAcresLandWantsToSell = -1;
		int32_t numberBushelsWheatToFood = -1;
		int32_t numberAcresLandNeedToPlantWheat = -1;

		std::cout << "Что пожелаешь, повелитель?" << std::endl;

		while (numberAcresLandWantsToBuy < 0) 
		{
			std::cout << "Сколько акров земли повелеваешь купить? ";
			std::cin >> numberAcresLandWantsToBuy;
			if (numberAcresLandWantsToBuy < 0) 
			{
				std::cout << "О, повелитель, значение не может быть отрицательным!" << std::endl;
			}
			else if (numberAcresLandWantsToBuy * currentPriceOneAcre_ > gameState_.numberBushelsWheat_) 
			{
				std::cout << "О, повелитель, у нас недостаточно пшеницы для покупки!" << std::endl;
				numberAcresLandWantsToBuy = -1;
			}
		}

		while (numberAcresLandWantsToSell < 0) 
		{
			std::cout << "Сколько акров земли повелеваешь продать? ";
			std::cin >> numberAcresLandWantsToSell;
			if (numberAcresLandWantsToSell < 0) 
			{
				std::cout << "О, повелитель, значение не может быть отрицательным!" << std::endl;
			}
			else if (numberAcresLandWantsToSell > gameState_.numberAcresLand_) 
			{
				std::cout << "О, повелитель, у нас нет столько земли!" << std::endl;
				numberAcresLandWantsToSell = -1;
			}
		}

		while (numberBushelsWheatToFood < 0) 
		{
			std::cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
			std::cin >> numberBushelsWheatToFood;
			if (numberBushelsWheatToFood < 0) 
			{
				std::cout << "Значение не может быть отрицательным!" << std::endl;
			}
		}

		while (numberAcresLandNeedToPlantWheat < 0) 
		{
			std::cout << "Сколько акров земли повелеваешь засеять? ";
			std::cin >> numberAcresLandNeedToPlantWheat;
			if (numberAcresLandNeedToPlantWheat < 0) 
			{
				std::cout << "О, повелитель, значение не может быть отрицательным!" << std::endl;
			}
			else if (numberAcresLandNeedToPlantWheat > gameState_.numberAcresLand_ - numberAcresLandWantsToSell + numberAcresLandWantsToBuy) 
			{
				std::cout << "О, повелитель, у нас нет столько земли!" << std::endl;
				numberAcresLandNeedToPlantWheat = -1;
			}
			else if (numberAcresLandNeedToPlantWheat > gameState_.peoplePopulation_ * ACRES_PER_PERSON) 
			{
				std::cout << "О, повелитель, наши люди не смогут обработать столько!" << std::endl;
				numberAcresLandNeedToPlantWheat = -1;
			}
			else if (numberAcresLandNeedToPlantWheat * BUSHELS_WHEAT_PER_PLANT_ACRE >
				gameState_.numberBushelsWheat_ - numberBushelsWheatToFood + numberAcresLandWantsToSell * currentPriceOneAcre_) 
			{
				std::cout << "О, повелитель, у нас недостаточно пшеницы на семена и еду!" << std::endl;
				numberAcresLandNeedToPlantWheat = -1;
			}
		}

		return PlayerValues(numberAcresLandWantsToBuy, numberAcresLandWantsToSell, numberBushelsWheatToFood, numberAcresLandNeedToPlantWheat);
	}

	void HammurabiGameMode::finishGame() const
	{
		double P = gameState_.totalPeopleStarvedPercent_ / (gameState_.year_ - 1);
		uint32_t L = gameState_.numberAcresLand_ / gameState_.peoplePopulation_;

		std::cout << "Итоги твоего правления, повелитель:" << std::endl;
		std::cout << "Среднегодовой процент умерших от голода: " << P << "%" << std::endl;
		std::cout << "Акров земли на одного жителя: " << L << std::endl;

		if (P > 33 && L < 7) 
		{
			std::cout << "Плохо: Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. "
				<< "Теперь вы вынуждены влачить жалкое существование в изгнании!" << std::endl;
		}
		else if (P > 10 && L < 9) 
		{
			std::cout << "Удовлетворительно: Вы правили железной рукой, подобно Нерону и Ивану Грозному. "
				<< "Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем" << std::endl;
		}
		else if (P > 3 && L < 10) 
		{
			std::cout << "Хорошо: Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, "
				<< "но многие хотели бы увидеть вас во главе города снова" << std::endl;
		}
		else 
		{
			std::cout << "Отлично: Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше" << std::endl;
		}
	}

	bool HammurabiGameMode::goToNextRound(const PlayerValues& playerValues)
	{
		// Обработка торговли землей
		gameState_.numberAcresLand_ += playerValues.numberAcresLandWantsToBuy_ - playerValues.numberAcresLandWantsToSell_;
		gameState_.numberBushelsWheat_ -= playerValues.numberAcresLandWantsToBuy_ * currentPriceOneAcre_;
		gameState_.numberBushelsWheat_ += playerValues.numberAcresLandWantsToSell_ * currentPriceOneAcre_;

		// Расход на еду и семена
		uint32_t seeds = static_cast<uint32_t>(playerValues.numberAcresLandNeedToPlantWheat_ * BUSHELS_WHEAT_PER_PLANT_ACRE);
		gameState_.numberBushelsWheat_ -= playerValues.numberBushelsWheatToFood_ + seeds;

		// Сбор урожая
		uint32_t harvestedWheatPerAcre = randomRange(1, 6);
		uint32_t harvestedWheat = harvestedWheatPerAcre * playerValues.numberAcresLandNeedToPlantWheat_;
		gameState_.numberBushelsWheat_ += harvestedWheat;

		// Крысы
		uint32_t ratsEatenWheat = randomRange(0, static_cast<uint32_t>(gameState_.numberBushelsWheat_ * RATS_MAX_PERCENT));
		gameState_.numberBushelsWheat_ -= ratsEatenWheat;

		// Голод
		uint32_t requiredFood = gameState_.peoplePopulation_ * FOOD_PER_PERSON;
		uint32_t starvedPeople = (playerValues.numberBushelsWheatToFood_ < requiredFood)
			? gameState_.peoplePopulation_ - playerValues.numberBushelsWheatToFood_ / FOOD_PER_PERSON
			: 0;

		uint32_t peoplePopulationBeforeStarve = gameState_.peoplePopulation_;
		peoplePopulationBeforeStarve -= starvedPeople;

		if (starvedPeople > PEOPLE_STARVED_FAIL_PERCENT * peoplePopulationBeforeStarve)
		{
			std::cout << "Более " << PEOPLE_STARVED_FAIL_PERCENT * 100 << "% населения умерло от голода в этом году! Народ свергнул тебя, повелитель!" << std::endl;
			return false;
		}

		double starvedPeoplePercent = (static_cast<double>(starvedPeople) / peoplePopulationBeforeStarve) * 100.0;
		gameState_.totalPeopleStarvedPercent_ += starvedPeoplePercent;
		gameState_.peoplePopulation_ = peoplePopulationBeforeStarve;

		// Чума
		bool wasPlague = (randomRange(0, 99) < PLAGUE_CHANCE);
		if (wasPlague)
		{
			gameState_.peoplePopulation_ = static_cast<uint32_t>(floor(gameState_.peoplePopulation_ / 2.0));
		}

		// Прибывшие жители
		int immigrants = starvedPeople / 2 + (5 - gameState_.amountWheatHarvestedPerAcre_) * gameState_.numberBushelsWheat_ / 600 + 1;
		if (immigrants < 0)
		{
			immigrants = 0;
		}
		else if (immigrants > MAX_IMMIGRANTS)
		{
			immigrants = MAX_IMMIGRANTS;
		}
		gameState_.peoplePopulation_ += immigrants;

		if (gameState_.peoplePopulation_ <= 0)
		{
			std::cout << "Все население вымерло! Ты проиграл, повелитель!" << std::endl;
			return false;
		}

		// Сохранение значений для следующего отчета
		gameState_.numberPeopleStarvedLastRound_ = starvedPeople;
		gameState_.numberPeopleImmigrantsLastRound_ = immigrants;
		gameState_.wasPlagueLastRound_ = wasPlague;
		gameState_.amountWheatHarvested_ = harvestedWheat;
		gameState_.amountWheatHarvestedPerAcre_ = harvestedWheatPerAcre;
		gameState_.amountWheatDestroyedByRats_ = ratsEatenWheat;

		return true;
	}
}

