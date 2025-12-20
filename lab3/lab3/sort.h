#pragma once
#include <cstddef>

ptrdiff_t insertionThreshold = 13;

void setInsertionThreshold(const ptrdiff_t value) { insertionThreshold = value; }

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
    
    swap(*pivot, *(last - 1));
    T* i = first - 1;
    for (T* j = first; j != last - 1; j++)
    {
        if (comp(*j, *(last - 1)))
        {
            i++;
            swap(*i, *j);
        }
    }
    i++;
    swap(*i, *(last - 1));
    return i;
}

template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp) 
{
    while (last - first > insertionThreshold)
    {
        T* pivot = partition(first, last, comp);
        std::ptrdiff_t left = pivot - first;
        std::ptrdiff_t right = last - pivot;

        if (left < right && left != 0) 
        {
          
            sort(first, pivot, comp);
            first = pivot + 1;
        }
        else 
        {
            sort(pivot + 1, last, comp);
            last = pivot;
        }
    }
    insertionSort(first, last, comp);
}

template<typename T, typename Compare>
bool is_sorted(T* first, T* last, Compare comp) 
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