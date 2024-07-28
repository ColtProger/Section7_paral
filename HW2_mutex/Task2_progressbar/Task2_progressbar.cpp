#include <iostream> // std::cout
#include <thread>   // std::thread
#include <vector>
#include<atomic>
#include <Windows.h> // WinApi
#include<chrono>
#include<mutex>
#include <random>

std::mutex m;
//auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

class consol_parameter
{
public:
    static void SetColor(int text, int background)
    {
        SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
    }
    static void SetPosition(int x, int y)
    {
        COORD point;
        point.X = x;
        point.Y = y;
        SetConsoleCursorPosition(hStdOut, point);
    }
private:
    static HANDLE hStdOut;
};
HANDLE consol_parameter::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);


//// устанавливает курсор в консоли на указанную позицию
//void set_cursor(int x, int y)
//{
//    COORD point;
//    point.X = x;
//    point.Y = y;
//    SetConsoleCursorPosition(handle, point);
//    //SetConsoleCursorPosition(handle, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
//}

// отрисовывает прогресс-бар в консоли по указанным координатам
// x - х-координата для прогресс-бара
// y - у-координата для прогресс-бара
// barWidth - ширина прогресс-бара
// progress - пройденный прогресс [0; 1]

void render_progress_bar(int x, int y, int barWidth, double progress)
{
    consol_parameter::SetPosition(x, y);
    int pos = barWidth * progress;

    for (int i = 0; i <= barWidth; i++) {
        if (i == 0) std::cout << "[";
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
        if (i == barWidth) std::cout << "]";
    }
  
}

void process_imitation(int indx, int num, int count) {

    int barWidth = 20;

    int length = count / num;
    int start = indx * length;
    int end = (indx + 1) * length - 1;


    int last_index = start;
    double progress = 0;

    int progress_y = 1+indx;
    int progress_x = 0;

    m.lock();
    consol_parameter::SetPosition(progress_x, progress_y);
    std::cout << indx << ". " << std::this_thread::get_id();

    consol_parameter::SetPosition(progress_x + 10, progress_y);
    std::cout << "[";
    
    consol_parameter::SetPosition(progress_x+ 12 + barWidth, progress_y);
    std::cout <<"]";
    m.unlock();

    auto start_t = std::chrono::high_resolution_clock::now();

  // 
  //  // имитация изменения прогресса
    while (last_index<end)
    {   
        // случайная задержка времени 
        std::random_device t;
        std::uniform_int_distribution<int> dist(0, 10);
        int time = dist(t);
        std::this_thread::sleep_for(std::chrono::milliseconds(time));

        std::lock_guard<std::mutex> grd(m);

        int pos = barWidth * progress;
        consol_parameter::SetPosition(progress_x + 11 + pos, progress_y);
        if (pos < barWidth) std::cout << "=";

       last_index += 1;
       progress = (static_cast<double>(last_index - start) / static_cast<double>(end - start));
    } 

    auto end_t = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>time = end_t - start_t;

    std::lock_guard<std::mutex> grd(m);
    consol_parameter::SetPosition(progress_x + barWidth + 15, progress_y);
    std::cout << " " << time.count();
 
  std::cout << "\n";
}

int main()
{
    consol_parameter::SetPosition(0, 0);

    // поток отрисовки
    int number_of_th = 3;
    int count = 1000;


    std::vector<std::thread> ths;
    ths.reserve(number_of_th);

    std::cout << "#" << "  " << "id" << "\t\t" << "PrBar" << "\t\t\t " << "time";

    for (int i = 0; i < number_of_th; i++) {
        int length = count / number_of_th; 
        //std::cout << i << std::endl;
       // consol_parameter::SetPosition(1, 2+i);
        ths.emplace_back(process_imitation, i, number_of_th, count);
        //std::cout << "\n";
       
    }

    for (auto& thread : ths) {          // (2)
        thread.join();
    }

    consol_parameter::SetPosition(0,6);
    return 0;
}