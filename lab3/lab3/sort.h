#pragma once
#include <cstddef>

const ptrdiff_t INSERTION_THRESHOLD = 10;

template<typename T>
void swap(T& a, T& b) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

template<typename T, typename Compare>
void insertionSort(T* first, T* last, Compare comp) {
    for (T* i = first + 1; i < last; i++) 
    {
        T key = std::move(*i);
        T* j = i - 1;
        while (j >= first && comp(key, *j)) 
        {
            *(j + 1) = std::move(*j);
            j--;
        }
        *(j + 1) = std::move(key);
    }
}

template<typename T, typename Compare>
T* getMedianOfThree(T* a, T* b, T* c, Compare comp)
{
    T* median = c;
    if ((comp(*a, *b) && comp(*b, *c)) || (comp(*c, *b) && comp(*b, *a))) 
    {
        median = b;
    }
    else if ((comp(*b, *a) && comp(*a, *c)) || (comp(*c, *a) && comp(*a, *b)))
    {
        median = a;
    }
    return median;
}

template<typename T, typename Compare>
T* partition(T* first, T* last, Compare comp)
{
    T* middle = first + (last - first) / 2;
    T* pivot = getMedianOfThree(first, middle, last - 1, comp);
    T pivotValue = *pivot;

    T* i = first - 1;
    T* j = last;

    while (true) {
        do { ++i; } while (comp(*i, pivotValue));
        do { --j; } while (comp(pivotValue, *j));

        if (i >= j)
        {
            break;
        }
        swap(*i, *j);
    }
    return j;
}

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp) 
{
    while (last - first > INSERTION_THRESHOLD)
    {
        T* pivot = partition(first, last, comp);
        std::ptrdiff_t left = (pivot - first) + 1;
        std::ptrdiff_t right = last - (pivot + 1);

        if (left < right && left > 0) 
        {
            if (left > 0)
            {
                sort(first, pivot + 1, comp);
            }
            first = pivot + 1;
        }
        else 
        {
            if (right > 0)
            {
                sort(pivot + 1, last, comp);
            }
            last = pivot + 1;
        }
    }
    insertionSort(first, last, comp);
}

template<typename T, typename Compare>
void defaultQuickSort(T* first, T* last, Compare comp)
{
    T* pivot = partition(first, last, comp);
    std::ptrdiff_t left = (pivot - first) + 1;
    std::ptrdiff_t right = last - (pivot + 1);

    if (left < right)
    {
        if (left > 0)
        {
            defaultQuickSort(first, pivot + 1, comp);
        }
        first = pivot + 1;
    }
    else
    {
        if (right > 0) {
            defaultQuickSort(pivot + 1, last, comp);
        }
        last = pivot + 1;
    }
}

template<typename T, typename Compare>
bool isSorted(T* first, T* last, Compare comp) 
{
    for (T* i = first + 1; i < last; ++i) 
    {
        if (comp(*i, *(i - 1)))
        {
            return false;
        }
    }
    return true;
}