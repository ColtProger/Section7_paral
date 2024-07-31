#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

int print(int elem) {

    std::cout << elem << " ";
    return 0;

}

void for_each(std::vector<int>::iterator first,
    std::vector<int>::iterator last,
    int(*func)(int))
{    
    for (auto it = first; it != last; ++it)
        func(*it);
}

int main()
{
    // Демонстрация использования promise<int> для передачи результата между потоками.
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    
    for_each(numbers.begin(), numbers.end(), &print);
}