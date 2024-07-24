#include <iostream>
#include<chrono>
#include<thread>
#include<atomic>

std::atomic_int client_counter{ 1 };

void AddQueue() {
    auto lastUpdate = std::chrono::steady_clock::now();

    while (client_counter.load() != 27) {
        auto now(std::chrono::steady_clock::now());
        auto dt = now - lastUpdate;
        if (dt >= std::chrono::seconds(1)) {
            lastUpdate = now;
            client_counter++;
           // client_counter.store(counter);
            std::cout << client_counter.load() << std::endl;
        }
    }
}
void DeleteQueue() {
    auto lastUpdate = std::chrono::steady_clock::now();

    while (client_counter.load() > 0) {
        auto now(std::chrono::steady_clock::now());
        auto dt = now - lastUpdate;
        if (dt >= std::chrono::seconds(2)) {
            lastUpdate = now;
            client_counter--;

            //client_counter.store(counter);

            std::cout << "-" << client_counter.load() << std::endl;
        }
    }
}

int main()
{
    //int counter = 1;
    std::thread t1(AddQueue);
    std::thread t2(DeleteQueue);
    t1.join();
    t2.join();
    return EXIT_SUCCESS;
}

