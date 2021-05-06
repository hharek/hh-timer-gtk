#pragma once

#include <gtkmm.h>
#include <string>

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

    /* Ссылка на таймер */
    Timer * timer;

    /* Слоты */
    void btn_start_click();
    void btn_pause_click();
    void btn_cancel_click();
    void btn_resume_click();

    /* Отобразить кнопки */
    void show_button() const;

    /* Сменить время */
    bool time_change () const;

    /* Перевести секунды с формат таймера */
    static std::string format (int total, bool milliseconds_show);

    /* Ресурс события */
    sigc::connection timeout_conn;
};