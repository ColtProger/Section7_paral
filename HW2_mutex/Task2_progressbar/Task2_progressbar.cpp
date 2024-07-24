#include <iostream> // std::cout
#include <thread>   // std::thread
#include <vector>
#include<atomic>
#include <Windows.h> // WinApi
#include<chrono>
#include<mutex>

std::mutex m;
auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

// устанавливает курсор в консоли на указанную позицию
void set_cursor(int x, int y)
{
    COORD point;
    point.X = x;
    point.Y = y;
    SetConsoleCursorPosition(handle, point);
    //SetConsoleCursorPosition(handle, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
}

// отрисовывает прогресс-бар в консоли по указанным координатам
// x - х-координата для прогресс-бара
// y - у-координата для прогресс-бара
// barWidth - ширина прогресс-бара
// progress - пройденный прогресс [0; 1]

void render_progress_bar(int x, int y, int barWidth, double progress)
{
    
    set_cursor(x, y);

    int fill_w = static_cast<int>(barWidth * progress);
    int empty_w = barWidth - fill_w;

    for (int i = 0; i < fill_w; i++)
    std::cout << ">";

    for (int i = 0; i < empty_w; i++)
     std::cout << " ";
}

void process_imitation(int indx, int num, int count) {

    int barWidth = 20;

    int length = count / num;
    int start = indx * length;
    int end = (indx + 1) * length - 1;


    int last_index = start;
    double progress = 0;

    int progress_y = 2 +  indx;
    int progress_x = 1;

    m.lock();
    
    set_cursor(progress_x, progress_y);
    std::cout <<indx<<". "<< std::this_thread::get_id() << " " << "[";

    set_cursor(progress_x +barWidth+11, progress_y);
    std::cout << "]";
    
    auto start_t = std::chrono::high_resolution_clock::now();

   
    // имитация изменения прогресса
    while (last_index < end)
    {
       render_progress_bar(progress_x+10, progress_y, barWidth, progress);
       last_index += 1;
       progress = (static_cast<double>(last_index - start) / static_cast<double>(end - start));
    }

    auto end_t = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>time = end_t - start_t;

   set_cursor(progress_x + barWidth + 13, progress_y);
   std::cout << " " << time.count() << std::endl;
   m.unlock();
   //std::cout << "\n";
}

int main()
{
    set_cursor(0, 0);

    // поток отрисовки
    int number_of_th = 5;
    int count = 5000;


    std::vector<std::thread> ths;
    ths.reserve(number_of_th);

    std::cout << "#" << "\t" << "id" << "\t " << "PrBar" << "\t\t " << "time" << std::endl;

    for (int i = 0; i < number_of_th; i++) {
        int length = count / number_of_th; 
        ths.emplace_back(process_imitation, i, number_of_th, count);
        std::cout << "\n\n";
       
    }

    for (auto& thread : ths) {          // (2)
        thread.join();
    }

    set_cursor(0,10);
    return 0;
}