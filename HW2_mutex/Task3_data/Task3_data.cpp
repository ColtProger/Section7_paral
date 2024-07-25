#include <chrono>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Data
{
public:
    int value;
    std::mutex m;

    Data(int num)
    {
        this->value = num;
    }

};

void SWAP_scopedlock(Data& D1, Data& D2) {

    std::scoped_lock (D1.m, D2.m);

    int  temp = D1.value;
    D1.value = D2.value;
    D2.value = temp;

}

void SWAP_lock(Data& D1, Data& D2) {

    //std::scoped_lock lock(D1.m, D2.m);

    
   std::lock(D1.m, D2.m);

    int  temp = D1.value;
    D1.value = D2.value;
    D2.value = temp;

   D1.m.unlock();
   D2.m.unlock();
}

void SWAP_unique_lock(Data& D1, Data& D2) {

    std::unique_lock<std::mutex> lk1(D1.m, std::defer_lock);
    std::unique_lock<std::mutex> lk2(D2.m, std::defer_lock);
    std::lock(lk1, lk2);

    int  temp = D1.value;
    D1.value = D2.value;
    D2.value = temp;

    }

int main()
{
    std::cout << __cplusplus << std::endl;
    Data D1(43), D2(56);
    std::thread tr0(SWAP_scopedlock, std::ref(D1), std::ref(D2));
    std::thread tr1(SWAP_lock, std::ref(D1), std::ref(D2));
    std::thread tr2(SWAP_unique_lock, std::ref(D1), std::ref(D2));
    tr0.join();
    tr1.join();
    tr2.join();
    std::cout << "D1.value: "<< D1.value  << "\nD2.value: " << D2.value << std::endl;
}


