#pragma once
#include <cstdint>
#include <string>

namespace hammurabi {
	// Имя файла сохранения
	const std::string SAVE_FILE = "savegame.txt";

	// Константы игры
	const uint32_t START_PEOPLE_POPULATION = 100;
	const uint32_t START_NUMBER_BUSHELS_WHEAT = 2800;
	const uint32_t START_NUMBER_ACRES_LAND = 1000;

	const uint32_t MAX_YEARS = 10;
	const uint32_t FOOD_PER_PERSON = 20;
	const uint32_t ACRES_PER_PERSON = 10;
	const double BUSHELS_WHEAT_PER_PLANT_ACRE = 0.5;
	const double RATS_MAX_PERCENT = 0.07;
	const double PEOPLE_STARVED_FAIL_PERCENT = 0.45;
	const uint32_t PLAGUE_CHANCE = 15;
	const uint32_t MIN_ONE_ACRE_PRICE = 17;
	const uint32_t MAX_ONE_ACRE_PRICE = 26;
	const uint32_t MAX_IMMIGRANTS = 50;

	struct GameState 
	{
		uint32_t year_;

		uint32_t peoplePopulation_;
		uint32_t numberBushelsWheat_;
		uint32_t numberAcresLand_;

		uint32_t numberPeopleStarvedLastRound_;
		uint32_t numberPeopleImmigrantsLastRound_;

		bool wasPlagueLastRound_;

		uint32_t amountWheatHarvested_;
		uint32_t amountWheatHarvestedPerAcre_;
		uint32_t amountWheatDestroyedByRats_;

		double totalPeopleStarvedPercent_;
	};

	struct PlayerValues
	{
		PlayerValues(uint32_t numberAcresLandWantsToBuy,
			uint32_t numberAcresLandWantsToSell,
			uint32_t numberBushelsWheatToFood,
			uint32_t numberAcresLandNeedToPlantWheat) 
			: numberAcresLandWantsToBuy_(numberAcresLandWantsToBuy),
				numberAcresLandWantsToSell_(numberAcresLandWantsToSell), 
				numberBushelsWheatToFood_(numberBushelsWheatToFood), 
				numberAcresLandNeedToPlantWheat_(numberAcresLandNeedToPlantWheat) {};

		uint32_t numberAcresLandWantsToBuy_;
		uint32_t numberAcresLandWantsToSell_;
		uint32_t numberBushelsWheatToFood_;
		uint32_t numberAcresLandNeedToPlantWheat_;
	};


	class HammurabiGameMode
	{
	public:
		void startGame();

	private:
		GameState gameState_;
		uint32_t currentPriceOneAcre_ = 0;

		void initNewGame();
		bool loadSavedGame();
		bool saveGame() const;

		bool playRound();
		void finishGame() const;

		void printRoundStats() const;
		PlayerValues enterPlayerValues() const;
		bool goToNextRound(const PlayerValues& playerValues);

		uint32_t randomRange(uint32_t min, uint32_t max) const { return min + rand() % (max - min + 1); }
	};
}



