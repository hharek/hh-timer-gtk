#include <thread>
#include <chrono>

#include "worker.h"
#include "window.h"
#include "timer.h"

using namespace std::chrono;

/**
 * Основная фукнция воркера
 */
[[noreturn]] void Worker::run (Window * window)
{
    while (true)
    {
        {
            std::lock_guard<std::mutex> lock(window->mutex);
        }

        std::this_thread::sleep_for(1s);

        {
            std::lock_guard<std::mutex> lock(window->mutex);
            Timer::second += 1;
        }

        window->signal_time_change.emit();
    }
}
