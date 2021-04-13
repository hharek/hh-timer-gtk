#include "timer.h"
#include "chrono"

using namespace std::chrono;

/**
 * Старт
 */
void Timer::start()
{
    this->state = Timer::State::runnable;

    this->timestamp = steady_clock::now();
    this->total = { 0ms };

    this->mutex.unlock();
}

/**
 * Пауза
 */
void Timer::pause()
{
    this->mutex.try_lock();

    this->state = Timer::State::paused;

    this->total += duration_cast<milliseconds>(steady_clock::now() - this->timestamp);
}

/**
 * Продолжить
 */
void Timer::resume()
{
    this->state = Timer::State::runnable;

    this->timestamp = steady_clock::now();

    this->mutex.unlock();
}

/**
 * Отмена
 */
void Timer::cancel()
{
    this->mutex.try_lock();

    this->state = Timer::State::stopped;

    this->total = { 0ms };
}

