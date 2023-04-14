#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include <memory>

template <typename T, size_t N>
struct limited_instance
{
    inline static std::atomic<size_t> count{0};
    limited_instance()
    {
        if (count >= N) {
            throw std::logic_error("To much instance");
        }
        ++count;
    }
};

struct executor
{

    void execute(std::function<void(void)> const &task)
    {
        threads.push_back(std::thread([task]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            task();
        }));
    }

    ~executor()
    {
        for (auto &t : threads) {
            t.join();
        }
    }

private:
    std::vector<std::thread> threads;
};

struct building : public std::enable_shared_from_this<building>
{
    building()
    {
        ptr = new int{2000};
        std::cout << "binding()" << std::endl;
    }
    ~building()
    {
        *ptr = 0;
        delete ptr;
        std::cout << "~building()" << std::endl;
    }

    void upgrade()
    {
        if (exec) {
            exec->execute([self = shared_from_this()]() {
                self->do_upgrade();
            });
        }
    }

    void set_executor(executor *e)
    {
        exec = e;
    }

private:
    void do_upgrade()
    {
        std::cout << "upgrading\n";
        operational = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        operational = true;
        std::cout << "building is function\n";
        std::cout << "*ptr = " << *ptr << std::endl;
    }
    executor *exec;
    bool operational = false;
    int *ptr{};
};

int main()
{
    executor e;
    std::shared_ptr<building> b = std::make_shared<building>();
    b->set_executor(&e);
    b->upgrade();

    std::cout << "main thread\n";
    return 0;
}
