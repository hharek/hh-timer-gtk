#pragma once
#include <mutex>

#include "window.h"


/**
 * Воркер
 */
class Worker
{
public:
    void run (Window * window);  /* Основная функция воркера */
    mutable std::mutex mutex;
};