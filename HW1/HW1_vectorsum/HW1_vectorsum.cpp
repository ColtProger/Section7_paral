// HW1_vectorsum.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<vector>
#include<algorithm>
#include<chrono>
#include<thread>
#include <random>

std::vector<int> randomVector(size_t size)
{
    std::vector<int> v(size);
    std::random_device r;
    std::uniform_int_distribution<int> dist(0, 100);
    generate(v.begin(), v.end(), [&] {return dist(r); });
    return v;
}

void VecSum(std::vector<int>& v1, std::vector<int>& v2, int start, int end)
{
    for (int i = start; i <= end; i++) {
        v1[i] = v1[i] + v2[i];
    }

    //std::transform(v1.begin(), v1.end(), v2.begin(), v1.begin(), std::plus<int>());
}
double OneThread(std::vector<int>& v1, std::vector<int>& v2) {

    auto start = std::chrono::high_resolution_clock::now();
    std::thread t2{ VecSum, std::ref(v1), std::ref(v2), 0, v1.size() - 1 };
    t2.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>time = end - start;
    
    return time.count();

}


double TwoThreads(std::vector<int>& v1, std::vector<int>& v2) {

    int start1 = 0;
    int start2 = v1.size() / 2;
    
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1{ VecSum, std::ref(v1), std::ref(v2), start1, start2-1 };
    std::thread t2{ VecSum, std::ref(v1), std::ref(v2), start2, v1.size()-1};
    t1.join();
    t2.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>time = end - start;
    return time.count();

}

double FourThreads(std::vector<int>& v1, std::vector<int>& v2) {

    int start1 = 0;
    int length = v1.size() / 4;
    
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1{ VecSum, std::ref(v1), std::ref(v2), 0, length-1 };
    std::thread t2{ VecSum, std::ref(v1), std::ref(v2), length, 2*length - 1 };
    std::thread t3{ VecSum, std::ref(v1), std::ref(v2), 2 * length, 3*length - 1 };
    std::thread t4{ VecSum, std::ref(v1), std::ref(v2), 3*length, v1.size() - 1 };
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>time = end - start;
    return time.count();

}

double Threads8(std::vector<int>& v1, std::vector<int>& v2) {

    int start1 = 0;
    int length = v1.size() / 8;
   
    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1{ VecSum, std::ref(v1), std::ref(v2), 0, length - 1 };
    std::thread t2{ VecSum, std::ref(v1), std::ref(v2), length, 2 * length - 1 };
    std::thread t3{ VecSum, std::ref(v1), std::ref(v2), 2 * length, 3 * length - 1 };
    std::thread t4{ VecSum, std::ref(v1), std::ref(v2), 3 * length, 4 * length - 1 };
    std::thread t5{ VecSum, std::ref(v1), std::ref(v2), 4 * length, 5 * length - 1 };
    std::thread t6{ VecSum, std::ref(v1), std::ref(v2), 5 * length, 6 * length - 1 };
    std::thread t7{ VecSum, std::ref(v1), std::ref(v2), 6 * length, 7 * length - 1 };
    std::thread t8{ VecSum, std::ref(v1), std::ref(v2), 7 * length, v1.size() - 1 };
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>time = end - start;
    
    return time.count();
}

double Threads16(std::vector<int>& v1, std::vector<int>& v2) {

    int start1 = 0;
    int length = v1.size() / 16;

    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1{ VecSum, std::ref(v1), std::ref(v2), 0, length - 1 };
    std::thread t2{ VecSum, std::ref(v1), std::ref(v2), length, 2 * length - 1 };
    std::thread t3{ VecSum, std::ref(v1), std::ref(v2), 2 * length, 3 * length - 1 };
    std::thread t4{ VecSum, std::ref(v1), std::ref(v2), 3 * length, 4 * length - 1 };
    std::thread t5{ VecSum, std::ref(v1), std::ref(v2), 4 * length, 5 * length - 1 };
    std::thread t6{ VecSum, std::ref(v1), std::ref(v2), 5 * length, 6 * length - 1 };
    std::thread t7{ VecSum, std::ref(v1), std::ref(v2), 6 * length, 7 * length - 1 };
    std::thread t8{ VecSum, std::ref(v1), std::ref(v2), 7 * length, 8*length - 1 };
    std::thread t9{ VecSum, std::ref(v1), std::ref(v2), 8 * length, 9*length - 1 };
    std::thread t10{ VecSum, std::ref(v1), std::ref(v2), 9*length, 10 * length - 1 };
    std::thread t11{ VecSum, std::ref(v1), std::ref(v2), 10 * length, 11 * length - 1 };
    std::thread t12{ VecSum, std::ref(v1), std::ref(v2), 11 * length, 12 * length - 1 };
    std::thread t13{ VecSum, std::ref(v1), std::ref(v2), 12 * length, 13 * length - 1 };
    std::thread t14{ VecSum, std::ref(v1), std::ref(v2), 13 * length, 14 * length - 1 };
    std::thread t15{ VecSum, std::ref(v1), std::ref(v2), 14 * length, 15 * length - 1 };
    std::thread t16{ VecSum, std::ref(v1), std::ref(v2), 15 * length, v1.size() - 1 };
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    t11.join();
    t12.join();
    t13.join();
    t14.join();
    t15.join();
    t16.join();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>time = end - start;

    return time.count();
}
int main()
{
    std::vector<int> length{ 1000,10000,100000,1000000 };

    std::vector<double> thr1{};
    std::vector<double> thr2{};
    std::vector<double> thr4{};
    std::vector<double> thr8{};
    std::vector<double> thr16{};
    
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " current threads are supported.\n";

    std::cout << "\t\t";
    std::copy(length.begin(), length.end(), std::ostream_iterator<int>(std::cout, "\t\t "));
    std::cout << "\n";

    for (int i = 0; i < length.size(); i++) {
        
        size_t size = length[i];
        std::vector<int> v1(randomVector(size));
        std::vector<int> v2(randomVector(size));
        thr1.push_back(OneThread(v1, v2));
        thr2.push_back(TwoThreads(v1, v2));
        thr4.push_back(FourThreads(v1, v2));
        thr8.push_back(Threads8(v1, v2));
        thr16.push_back(Threads16(v1, v2));
        
    }
    std::cout << "1 thread: "<<"\t";
    std::copy(thr1.begin(), thr1.end(), std::ostream_iterator<double>(std::cout, "\t "));
    std::cout << "\n";


    std::cout << "2 threads: " << "\t";
    std::copy(thr2.begin(), thr2.end(), std::ostream_iterator<double>(std::cout, "\t "));
    std::cout << "\n";

    std::cout << "4 threads: " << "\t";
    std::copy(thr4.begin(), thr4.end(), std::ostream_iterator<double>(std::cout, "\t "));
    std::cout << "\n";

    std::cout << "8 threads: " << "\t";
    std::copy(thr8.begin(), thr8.end(), std::ostream_iterator<double>(std::cout, "\t "));
    std::cout << "\n";

    std::cout << "16 threads: " << "\t";
    std::copy(thr16.begin(), thr16.end(), std::ostream_iterator<double>(std::cout, "\t "));
    std::cout << "\n";

    // avtomatization
    /*std::vector<std::thread> ths;
    std::size_t n;
    std::cin >> n;
    for (std::size_t i = 0; i < n; ++i)
        ths.push_back(std::thread(&foo, i));
    for (auto& th : ths)
        th.join();
    return 0;*/
  

    return EXIT_SUCCESS;
}

