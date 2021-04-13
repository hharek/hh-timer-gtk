#pragma once

#include <gtkmm.h>
#include <thread>
#include <string>
#include <mutex>

#include "timer.h"

/**
 * Основное окно
 */
class Window : public Gtk::Window
{
public:
    Window (BaseObjectType* widget, Glib::RefPtr<Gtk::Builder> & builder);      /* Конструктор */
    ~Window() override;                                                         /* Деструктор */

    Glib::RefPtr<Gtk::Builder> builder;  /* Ссылка на сборщик */
    Gtk::Label * lbl_time = nullptr;  /* Панель. Время на таймере */

    /* Кнопки */
    Gtk::Box * box_button = nullptr;  /* Коробка с кнопками */
    Gtk::Button * btn_start = nullptr;  /* Старт */
    Gtk::Button * btn_pause = nullptr;  /* Пауза */
    Gtk::Button * btn_cancel = nullptr;  /* Отмена */
    Gtk::Button * btn_resume = nullptr;  /* Продолжить */

    /* Сигнал «Время сменилось» */
    Glib::Dispatcher signal_time_change;

    /* Ссылка на таймер */
    Timer * timer;

    /* Слоты */
    void btn_start_click() const;
    void btn_pause_click() const;
    void btn_cancel_click() const;
    void btn_resume_click() const;

    /* Отобразить кнопки */
    void show_button() const;

    /* Сменить время на таймере */
    void slot_time_change () const;

    /* Перевести секунды с формат таймера */
    static std::string format (int total, bool milliseconds_show);
};