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

        std::this_thread::sleep_for(111ms);

        if (Timer::state == Timer::State::runnable)
        {
            window->signal_time_change.emit();
        }
    }
}
