#pragma once

#include <chrono>
#include <mutex>

using namespace std::chrono;

/**
 * Общий класс
 */
class Timer
{
public:
    /**
     * Возможные состояния
     */
    enum class State
    {
        stopped,  /* Остановлен (Старт) */
        runnable,  /* Запущен (Пауза | Отмена) */
        paused  /* На паузе (Продолжить | Отмена) */
    };

    /* Текущее состояние */
    State state = Timer::State::stopped;

    /* Последняя временная метка */
    steady_clock::time_point timestamp = steady_clock::now();

    /* Текущее время на таймере в миллисекундах */
    milliseconds total = { 0ms };

    /* Мьютекс для управления воркером */
    std::mutex mutex;

    /* Показывать миллисекунды */
    bool settings_milliseconds_show = true;

    /* Основные функции */
    void start ();
    void pause ();
    void resume();
    void cancel ();
};