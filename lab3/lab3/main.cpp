#include <iostream>
#include <vector>
#include <chrono>

#include "sort.h"

const int MAX_ARRAY_SIZE = 50;
const int NUMBER_RUNS = 20;

static void testInsertionSort()
{
    for (int arraySize = 1; arraySize <= MAX_ARRAY_SIZE; arraySize++)
    {
        double totalDurationSorts = 0.0;
        for (int run = 0; run < NUMBER_RUNS; run++)
        {
            std::vector<int> arr(arraySize);
            for (int i = 0; i < arraySize; i++)
            {
                arr[i] = arraySize - i;
            }

            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(arr.data(), arr.data() + arraySize, [](int a, int b) { return a < b; });
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::nano> durationSort = end - start;
            totalDurationSorts += durationSort.count();
        }
        double avgTimeSort = totalDurationSorts / NUMBER_RUNS;
        std::cout << "Пороговый интервал: " << arraySize << ", Среднее время сортировки (нс): " << avgTimeSort << std::endl;
    }
}

static void testQuickSort()
{
    for (int arraySize = 1; arraySize <= MAX_ARRAY_SIZE; arraySize++)
    {
        double totalDurationSorts = 0.0;
        for (int run = 0; run < NUMBER_RUNS; run++)
        {
            std::vector<int> arr(arraySize);
            for (int i = 0; i < arraySize; i++)
            {
                arr[i] = arraySize - i;
            }

            auto start = std::chrono::high_resolution_clock::now();
            defaultQuickSort(arr.data(), arr.data() + arraySize, [](int a, int b) { return a < b; });
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::nano> durationSort = end - start;
            totalDurationSorts += durationSort.count();
        }
        double avgTimeSort = totalDurationSorts / NUMBER_RUNS;
        std::cout << "Пороговый интервал: " << arraySize << ", Среднее время сортировки (нс): " << avgTimeSort << std::endl;
    }
}

static void startTests()
{
    std::cout << "=== Тест InsertionSort ===" << std::endl;
    testInsertionSort();
    std::cout << std::endl;

    std::cout << "=== Тест QuickSort ===" << std::endl;
    testQuickSort();
}

int main()
{
    setlocale(LC_ALL, "");

    startTests();

    return 0;
}