#include "pch.h"

#include <string>
#include <vector>
#include <limits>

#include "..\lab3\sort.h"

TEST(SortTest_Int, Single) 
{
    int arr[] = { 42 };
    sort(arr, arr + 1, [](int a, int b) { return a < b; });
    EXPECT_EQ(arr[0], 42);
}

TEST(SortTest_Int, TwoElements_Asc) 
{
    int arr[] = { 2, 1 };
    sort(arr, arr + 2, [](int a, int b) { return a < b; });
    EXPECT_EQ(arr[0], 1); EXPECT_EQ(arr[1], 2);
}

TEST(SortTest_Int, AlreadySorted_Asc) 
{
    int arr[] = { 1, 2, 3, 4, 5 };
    sort(arr, arr + 5, [](int a, int b) { return a < b; });
    EXPECT_TRUE(is_sorted(arr, arr + 5, [](int a, int b) { return a < b; }));
}

TEST(SortTest_Int, Reverse_Asc) 
{
    int arr[] = { 5, 4, 3, 2, 1 };
    sort(arr, arr + 5, [](int a, int b) { return a < b; });
    EXPECT_TRUE(is_sorted(arr, arr + 5, [](int a, int b) { return a < b; }));
}

TEST(SortTest_Int, Duplicates_Asc) 
{
    int arr[] = { 3, 1, 3, 2, 3 };
    int expected[] = { 1, 2, 3, 3, 3 };
    sort(arr, arr + 5, [](int a, int b) { return a < b; });
    for (int i = 0; i < 5; i++) EXPECT_EQ(arr[i], expected[i]);
}

TEST(SortTest_Int, AllEqual_Asc) 
{
    int arr[] = { 7, 7, 7, 7, 7 };
    sort(arr, arr + 5, [](int a, int b) { return a < b; });
    EXPECT_TRUE(is_sorted(arr, arr + 5, [](int a, int b) { return a < b; }));
}

TEST(SortTest_Int, LargeRandom_Asc) 
{
    std::srand(std::time(nullptr));
    constexpr int size = 1000;
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = rand() % 1000;
    sort(arr.data(), arr.data() + size, [](int a, int b) { return a < b; });
    EXPECT_TRUE(is_sorted(arr.data(), arr.data() + size, [](int a, int b) { return a < b; }));
}
TEST(SortTest_Int, Reverse_Desc) 
{
    int arr[] = { 1, 2, 3, 4, 5 };
    sort(arr, arr + 5, [](int a, int b) { return a > b; });
    EXPECT_TRUE(is_sorted(arr, arr + 5, [](int a, int b) { return a > b; }));
}

TEST(SortTest_Int, Duplicates_Desc) 
{
    int arr[] = { 3, 1, 3, 2, 3 };
    int expected[] = { 3, 3, 3, 2, 1 };
    sort(arr, arr + 5, [](int a, int b) { return a > b; });
    for (int i = 0; i < 5; i++) EXPECT_EQ(arr[i], expected[i]);
}

TEST(SortTest_Int, AllEqual_Desc) 
{
    int arr[] = { 7, 7, 7, 7, 7 };
    sort(arr, arr + 5, [](int a, int b) { return a > b; });
    EXPECT_TRUE(is_sorted(arr, arr + 5, [](int a, int b) { return a > b; }));
}

TEST(SortTest_Int, Duplicates_GE) 
{
    int arr[] = { 3, 1, 3, 2, 3 };
    int expected[] = { 3, 3, 3, 2, 1 };
    sort(arr, arr + 5, [](int a, int b) { return a >= b; });
    for (int i = 0; i < 5; i++) EXPECT_EQ(arr[i], expected[i]);
}

TEST(SortTest_Int, AllEqual_GE) 
{
    int arr[] = { 7, 7, 7, 7, 7 };
    int expected[] = { 7, 7, 7, 7, 7 };
    sort(arr, arr + 5, [](int a, int b) { return a >= b; });
    for (int i = 0; i < 5; i++) EXPECT_EQ(arr[i], expected[i]);
}

TEST(SortTest_Int, Duplicates_LE) 
{
    int arr[] = { 3, 1, 3, 2, 3 };
    int expected[] = { 1, 2, 3, 3, 3 };
    sort(arr, arr + 5, [](int a, int b) { return a <= b; });
    for (int i = 0; i < 5; i++) EXPECT_EQ(arr[i], expected[i]);
}

TEST(SortTest_Int, AllEqual_LE) 
{
    int arr[] = { 7, 7, 7, 7, 7 };
    int expected[] = { 7, 7, 7, 7, 7 };
    sort(arr, arr + 5, [](int a, int b) { return a <= b; });
    for (int i = 0; i < 5; i++) EXPECT_EQ(arr[i], expected[i]);
}

TEST(SortTest_String, Asc) 
{
    std::string arr[] = { "cherry", "banana", "apple" };
    sort(arr, arr + 3, [](const std::string& a, const std::string& b) { return a < b; });
    EXPECT_EQ(arr[0], "apple"); EXPECT_EQ(arr[2], "cherry");
}

TEST(SortTest_String, Desc) 
{
    std::string arr[] = { "cherry", "banana", "apple" };
    sort(arr, arr + 3, [](const std::string& a, const std::string& b) { return a > b; });
    EXPECT_EQ(arr[0], "cherry"); EXPECT_EQ(arr[2], "apple");
}

TEST(SortTest_String, GE) 
{
    std::string arr[] = { "b", "a", "b", "c", "b" };
    std::string expected[] = { "c", "b", "b", "b", "a" };
    sort(arr, arr + 5, [](const std::string& a, const std::string& b) { return a >= b; });
    for (int i = 0; i < 5; i++) EXPECT_EQ(arr[i], expected[i]);
}

TEST(SortTest_String, LE) 
{
    std::string arr[] = { "b", "a", "b", "c", "b" };
    std::string expected[] = { "a", "b", "b", "b", "c" };
    sort(arr, arr + 5, [](const std::string& a, const std::string& b) { return a <= b; });
    for (int i = 0; i < 5; i++) EXPECT_EQ(arr[i], expected[i]);
}

TEST(SortTest_Int, SmallInterval_Asc) 
{
    int arr[] = { 4, 3, 2, 1 };
    sort(arr, arr + 4, [](int a, int b) { return a < b; });
    EXPECT_TRUE(is_sorted(arr, arr + 4, [](int a, int b) { return a < b; }));
}

TEST(SortTest_Int, VeryLarge_Asc) 
{
    constexpr int size = 100000;
    std::vector<int> arr(size);
    for (int i = 0; i < size; i++) arr[i] = size - i;
    sort(arr.data(), arr.data() + size, [](int a, int b) { return a < b; });
    EXPECT_TRUE(is_sorted(arr.data(), arr.data() + size, [](int a, int b) { return a < b; }));
}