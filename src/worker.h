#pragma once
#include <mutex>

#include "window.h"


/**
 * Воркер
 */
class Worker
{
public:
    [[noreturn]] void run (Window * window);  /* Основная функция воркера */
};