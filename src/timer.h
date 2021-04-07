#pragma once

#include <chrono>

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

    /**
     * Текущее состояние
     */
    static State state;

    /* Последняя временная метка */
    static steady_clock::time_point timestamp;

    /* Текущее время на таймере в милисекундах */
    static milliseconds total;
};