#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "sort.h"
#include "testInsertionThreshold.h"

int testInsertionThreshold()
{
    for (int threshold = 0; threshold < MAX_THRESHOLD; threshold++) 
    {
        double totalDurationSorts = 0.0;
        for (int run = 0; run < NUMBER_RUNS; run++) 
        {
            std::vector<int> arr(ARRAY_SIZE);
            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                arr[i] = ARRAY_SIZE - i;
            }

            setInsertionThreshold(threshold);

            auto start = std::chrono::high_resolution_clock::now();
            sort(arr.data(), arr.data() + ARRAY_SIZE, [](int a, int b) { return a < b; });
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double, std::milli> durationSort = end - start;
            totalDurationSorts += durationSort.count();
        }
        double avgTimeSort = totalDurationSorts / NUMBER_RUNS;
        std::cout << "Пороговый интервал: " << threshold << ", Среднее время сортировки (мс): " << avgTimeSort << std::endl;
    }

    return 0;
}