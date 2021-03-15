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
    /* Окно */
    builder->get_widget("lbl-time", this->lbl_time);

    /* Отмечаем кнопки и вешаем на них функции */
    builder->get_widget("box-button", this->box_button);
    builder->get_widget("btn-start", this->btn_start);
    this->btn_start->signal_clicked().connect(sigc::mem_fun(*this, &Window::btn_start_click));
    builder->get_widget("btn-pause", this->btn_pause);
    this->btn_pause->signal_clicked().connect(sigc::mem_fun(*this, &Window::btn_pause_click));
    builder->get_widget("btn-cancel", this->btn_cancel);
    this->btn_cancel->signal_clicked().connect(sigc::mem_fun(*this, &Window::btn_cancel_click));
    builder->get_widget("btn-resume", this->btn_resume);
    this->btn_resume->signal_clicked().connect(sigc::mem_fun(*this, &Window::btn_resume_click));

    this->show_button();
}

/**
 * Деструктор
 */
Window::~Window() = default;

/**
 * Нажатие на Старт
 */
void Window::btn_start_click()
{
    this->state = State::runnable;
    this->show_button();
}

/**
 * Нажатие на Пауза
 */
void Window::btn_pause_click()
{
    this->state = State::paused;
    this->show_button();
}

/**
 * Нажатие на Отмена
 */
void Window::btn_cancel_click()
{
    this->state = State::stopped;
    this->show_button();
}

/**
 * Нажатие на Продолжить
 */
void Window::btn_resume_click()
{
    this->state = State::runnable;
    this->show_button();
}

/**
 * Показать кнопки
 */
void Window::show_button ()
{
    /* Удаляем старые */
    for (Gtk::Widget * child : this->box_button->get_children())
        this->box_button->remove(* child);

    /* Отображаем в соответствии с состоянием */
    switch (this->state)
    {
        case State::stopped:
            this->box_button->add(* this->btn_start);
            break;

        case State::runnable:
            this->box_button->add(* this->btn_pause);
            this->box_button->add(* this->btn_cancel);
            break;

        case State::paused:
            this->box_button->add(* this->btn_resume);
            this->box_button->add(* this->btn_cancel);
            break;
    }

}
