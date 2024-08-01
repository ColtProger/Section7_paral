#include <algorithm>
#include <future>
#include <iostream>
#include <mutex>
#include <numeric>
#include <string>
#include <vector>

template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f)
{
    auto vol = last - first;
    Iterator mid = first + vol / 2; 

    if (vol < 10) {
        for (; first != last; ++first)
            f(*first);
    }
    else {

        std::future<void> future{ std::async(std::launch::async,
                          parallel_for_each<Iterator, Func>, first, mid, std::ref(f)) };

        future.get();
        parallel_for_each(mid, last, f);

    }
}


int main() {

    std::vector<int> v{ 3, -4, 2, -8, 15, 2, 6, 7, 12, 86, 23 };
    // increment elements in-place
    parallel_for_each(v.begin(), v.end(), [](int& n) { n++; });

    auto print = [](const int& n) { std::cout << n << ' '; };

    std::cout << "after :\t";
    parallel_for_each(v.cbegin(), v.cend(), print);
    std::cout << '\n';



    //std::vector<int> v(12, 1);
    //int sum = 0;
    //std::cout << "The sum is " << parallel_sum(v.begin(), v.end(), 0) << '\n';
    //parallel_sum(v.begin(), v.end(), std::ref(sum));

}