#pragma once

#include <gtkmm.h>


/**
 * Основное окно
 */
class Window : public Gtk::Window
{
public:
    Glib::RefPtr<Gtk::Builder> builder;         /* Ссылка на сборщик */
    Gtk::Label * lbl_time;                      /* Циферблат */
    Gtk::Button * btn_start;                    /* Кнопка */

    Window (BaseObjectType* widget, Glib::RefPtr<Gtk::Builder> & builder);      /* Конструктор */
    ~Window() override;                                                         /* Деструктор */
};