#include "Array.h"
#include <iostream>
#include <string>

int main() {
    Array<int> a;
    for (int i = 0; i < 10; ++i) 
    {
        a.insert(i + 1);
    }

    for (int i = 0; i < a.size(); ++i)
    {
        a[i] *= 2;
    }

    std::cout << "=== Default Cycle ===" << '\n';
    for (int i = 0; i < a.size(); ++i)
    {
        std::cout << a[i] << '\n';
    }

    std::cout << "=== Iterator ===" << '\n';
    for (auto it = a.iterator(); it.hasNext(); it.next()) 
    {
        std::cout << it.get() << '\n';
    }
    
    std::cout << "=== Cycle For-Each ===" << '\n';
    for (int x : a) 
    {
        std::cout << x << '\n';
    }

    return 0;
}