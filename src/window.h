#pragma once

#include <gtkmm.h>
#include <thread>


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

    int second = 0;  /* Текущее время на таймере в секундах */

    /* Кнопки */
    Gtk::Box * box_button = nullptr;  /* Коробка с кнопками */
    Gtk::Button * btn_start = nullptr;  /* Старт */
    Gtk::Button * btn_pause = nullptr;  /* Пауза */
    Gtk::Button * btn_cancel = nullptr;  /* Отмена */
    Gtk::Button * btn_resume = nullptr;  /* Продолжить */

    /**
     * Возможные состояния
     */
    enum class State
    {
        stopped,  /* Остановлен (Старт) */
        runnable,  /* Запущен (Пауза | Отмена) */
        paused  /* На паузе (Продолжить | Отмена) */
    };

    State state = State::stopped;  /* Текущий этап */

    /* Сигнал «Время сменилось» */
    Glib::Dispatcher signal_time_change;

    /* Ссылка на поток */
    std::thread * thread;

    /* Слоты */
    void btn_start_click();
    void btn_pause_click();
    void btn_cancel_click();
    void btn_resume_click();

    /* Отобразить кнопки */
    void show_button() const;

    /* Сменить время на таймере */
    void slot_time_change () const;
};