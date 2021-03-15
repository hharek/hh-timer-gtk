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
    std::this_thread::sleep_for(3s);
    window->signal_time_change.emit();
}
