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

    /* Текущее время на таймере в секундах */
    static int second;
};