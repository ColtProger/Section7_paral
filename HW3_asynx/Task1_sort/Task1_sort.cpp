#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>
#include<vector>
#include<algorithm>
#include<random>

std::vector<int> randomVector(size_t size)
{
    std::vector<int> v(size);
    std::random_device r;
    std::uniform_int_distribution<int> dist(0, 10 * size);
    generate(v.begin(), v.end(), [&] {return dist(r); });
    return v;
}

void minimum(std::vector<int> v,
    int start, int end,
    std::promise<int> accumulate_promise)
{

    int min = v[start];
    int id = start;
    for (int i = start; i < end; i++) {
        if (v[i] < min) {
            min = v[i];
            id = i;
        }
    }
    accumulate_promise.set_value(id);  // Notify future
}

int main()
{
    // Demonstrate using promise<int> to transmit a result between threads.
    std::vector<int> v{ randomVector(10) };
    std::cout << "Before sorting: " << std::endl;
    for (auto elem : v) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    
    int start = 0;

    for (int i = start; i < v.size(); i++) {
        std::promise<int> accumulate_promise;
        std::future<int> accumulate_future = accumulate_promise.get_future();

        std::thread work_thread(minimum, v, i, v.size(), std::move(accumulate_promise));

        // future::get() will wait until the future has a valid result and retrieves it.
        int id = accumulate_future.get();

        int temp = v[i];
        v[i] = v[id];
        v[id] = temp;

        start++;
        work_thread.join();
    }
    std::cout << "After sorting: " << std::endl;
    for (auto elem : v) {
        std::cout << elem << " ";
    }
    std::cout << "\n";
    
}