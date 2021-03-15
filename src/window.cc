#include <gtkmm.h>
#include <iostream>

#include "window.h"


/**
 * Конструктор
 */
Window::Window (BaseObjectType* widget, Glib::RefPtr<Gtk::Builder> & builder) :
    Gtk::Window(widget),
    builder(builder)
{
    builder->get_widget("lbl-time", this->lbl_time);
    builder->get_widget("btn-start", this->btn_start);
    this->btn_start->signal_clicked().connect([]
    {
        std::cout << "Нажали на кнопку" << std::endl;
    });
}

/**
 * Деструктор
 */
Window::~Window() = default;
