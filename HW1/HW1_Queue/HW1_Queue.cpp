// HW1_Queue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<chrono>
#include<thread>
void AddQueue(int &counter) {
    auto lastUpdate = std::chrono::steady_clock::now();
    
    while (counter != 27) {
        auto now(std::chrono::steady_clock::now());
        auto dt = now - lastUpdate;
        if (dt >= std::chrono::seconds(1)) {
            lastUpdate = now;
            counter++;
            std::cout << counter << std::endl;
        }
    }
}
void DeleteQueue(int& counter) {
    auto lastUpdate = std::chrono::steady_clock::now();

    while (counter> 0) {
        auto now(std::chrono::steady_clock::now());
        auto dt = now - lastUpdate;
        if (dt >= std::chrono::seconds(2)) {
            lastUpdate = now;
            counter--;
            std::cout <<"-" << counter << std::endl;
        }
    }
}

int main()
{
    int counter = 1;
    std::thread t1(AddQueue, std::ref(counter));
    std::thread t2(DeleteQueue, std::ref(counter));
    t1.join(); 
    t2.join();
    return EXIT_SUCCESS;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
