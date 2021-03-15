#include <thread>
#include <chrono>

#include "worker.h"
#include "window.h"

using namespace std::chrono;

/**
 * Основная фукнция воркера
 */
void Worker::run (Window * window)
{
    for (int i = 0; i < 3; i++)
    {
        std::this_thread::sleep_for(1s);
        {
            std::lock_guard<std::mutex> lock(this->mutex);
            window->second += 1;
        }
        window->signal_time_change.emit();
    }
}
