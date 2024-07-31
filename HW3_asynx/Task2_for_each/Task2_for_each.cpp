#include <vector>
#include <thread>
#include <future>
#include <numeric>
#include <iostream>
#include <chrono>

void accumulate(std::vector<int>::iterator first,
    std::vector<int>::iterator last,
    std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);  // оповестить future
}

int main()
{
    // Демонстрация использования promise<int> для передачи результата между потоками.
    std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
        std::move(accumulate_promise));

    // future::get() будет ждать, пока future не будет иметь допустимый результат,
    // после чего запросит его.
    // Вызов wait() перед get() не требуется.
    //accumulate_future.wait();  // ждать результата
    std::cout << "result=" << accumulate_future.get() << '\n';
    work_thread.join();  // ждем завершения потока
}