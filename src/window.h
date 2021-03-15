#pragma once

#include <gtkmm.h>


/**
 * Основное окно
 */
class Window : public Gtk::Window
{
public:
    Window (BaseObjectType* widget, Glib::RefPtr<Gtk::Builder> & builder);      /* Конструктор */
    ~Window() override;                                                         /* Деструктор */

    Glib::RefPtr<Gtk::Builder> builder;  /* Ссылка на сборщик */
    Gtk::Label * lbl_time;  /* Циферблат */

    /* Кнопки */
    Gtk::Box * box_button;  /* Коробка с кнопками */
    Gtk::Button * btn_start;  /* Старт */
    Gtk::Button * btn_pause;  /* Пауза */
    Gtk::Button * btn_cancel;  /* Отмена */
    Gtk::Button * btn_resume;  /* Продолжить */

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

    /* Слоты */
    void btn_start_click();
    void btn_pause_click();
    void btn_cancel_click();
    void btn_resume_click();

    /* Отобразить кнопки */
    void show_button();
};