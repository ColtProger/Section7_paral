#include <condition_variable> 
#include <iostream> 
#include <mutex> 
#include <queue> 
#include <thread> 
#include <functional>
#include<atomic>

std::mutex m;
std::atomic_bool stop_ = false;

template <typename T>
class SafeQueue {
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;

public:
    void push(T item)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(item);
        m_cond.notify_one();
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
         m_cond.wait(lock, [this] { return !m_queue.empty(); });
        T item = std::move( m_queue.front());
        m_queue.pop();
        return item;
    }

    T front()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
       while (m_queue.empty()) {
            m_cond.wait(lock); 
        }
        T item = m_queue.front();
        return item;
    }

    bool ifempty() {
        return m_queue.empty();
    }
};

class ThreadPool {
private:
    std::vector<std::thread> VecThreads;
    SafeQueue <std::function<void()> > tasks_;
    std::mutex queue_mutex_;

    std::condition_variable cv_;
    //bool stop_ = false;


public:

    ThreadPool(size_t num_threads)
    {
        for (size_t i = 0; i < num_threads; ++i)
            VecThreads.emplace_back(std::thread([this]() { this->work(); }));
    };

    ~ThreadPool()
    {
        // Lock the queue to update the stop flag safely 
        std::unique_lock<std::mutex> lock(queue_mutex_); 
        stop_ = true;

        // Notify all threads 
        cv_.notify_all();

        for (auto& thread : VecThreads) thread.join();

    };

    void submit(std::function<void()> task)
    {
        // lock the queue to add the task
        std::unique_lock<std::mutex> lock(queue_mutex_);
        tasks_.push(task);

        //notify the task to process
        cv_.notify_one();
       
    };

    void work()
    {
        {
            std::lock_guard<std::mutex> lock(m);
            std::cout << "[work]\trunning id" << std::this_thread::get_id() << std::endl;
        }

        while (true)
        {
            while (!tasks_.ifempty())
            {
                //std::unique_lock<std::mutex> lock(queue_mutex_);
                auto task = tasks_.pop();
               // auto task = tasks_.front();
                task();
               // tasks_.pop();
            }

            
        }
        stop_ = false;
    }


};

void function1() {

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "working function " << __FUNCTION__ << std::endl;
    }
}

void function2() {

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "working function " << __FUNCTION__ << std::endl;
    }
}

void function3() {

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    {
        std::lock_guard<std::mutex> lock(m);
        std::cout << "working function " << __FUNCTION__ << std::endl;
    }
}

// Driver code 
int main()
{
    const auto cores = std::thread::hardware_concurrency();
    ThreadPool pool(cores);

    // Enqueue tasks for execution 
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        m.lock();
        std::cout << "STEP " << i << std::endl;
        m.unlock();

        pool.submit(function1);
        pool.submit(function2);
        pool.submit(function3);
    }

    return EXIT_SUCCESS;

}