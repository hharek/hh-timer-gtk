#include <gtkmm.h>

#include "timer.h"
#include "window.h"

/**
 * Конструктор
 */
Window::Window (BaseObjectType* widget, Glib::RefPtr<Gtk::Builder> & builder) :
    Gtk::Window(widget),
    builder(builder)
{
    this->timer = new Timer();

    /* Окно */
    builder->get_widget("lbl-time", this->lbl_time);
    if (this->timer->settings_milliseconds_show)
        this->lbl_time->set_label("00:00:00.000");
    else
        this->lbl_time->set_label("00:00:00");

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

    /* Показать кнопки */
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
    this->timeout_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Window::time_change), this->timer->timeout_interval);

    this->timer->start();
    this->time_change();
    this->show_button();
}

/**
 * Нажатие на Пауза
 */
void Window::btn_pause_click()
{
    this->timeout_conn.disconnect();

    this->timer->pause();
    this->time_change();
    this->show_button();
}

/**
 * Нажатие на Отмена
 */
void Window::btn_cancel_click()
{
    this->timeout_conn.disconnect();

    this->timer->cancel();
    this->time_change();
    this->show_button();
}

/**
 * Нажатие на Продолжить
 */
void Window::btn_resume_click()
{
    this->timeout_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Window::time_change), this->timer->timeout_interval);

    this->timer->resume();
    this->time_change();
    this->show_button();
}

/**
 * Показать кнопки
 */
void Window::show_button () const
{
    /* Удаляем старые */
    for (Gtk::Widget * child : this->box_button->get_children())
        this->box_button->remove(* child);

    /* Отображаем в соответствии с состоянием */
    switch (this->timer->state)
    {
        case Timer::State::stopped:
            this->box_button->add(* this->btn_start);
            break;

        case Timer::State::runnable:
            this->box_button->add(* this->btn_pause);
            this->box_button->add(* this->btn_cancel);
            break;

        case Timer::State::paused:
            this->box_button->add(* this->btn_resume);
            this->box_button->add(* this->btn_cancel);
            break;
    }

}

/**
 * Сменить время
 */
bool Window::time_change () const
{
    milliseconds total;
    if (this->timer->state == Timer::State::runnable)
        total = this->timer->total + (duration_cast<milliseconds>(steady_clock::now() - this->timer->timestamp));
    else
        total = this->timer->total;

    Glib::ustring str = Window::format((int)total.count(), this->timer->settings_milliseconds_show);
    this->lbl_time->set_label(str);

    return true;
}

/**
 * Перевести секунды с формат таймера
 */
std::string Window::format(const int total, const bool milliseconds_show)
{
    int second = total / 1000;

    char hour[3] = {0};
    snprintf(hour, 3, "%02d", second / 3600);

    char min[3] = {0};
    snprintf(min, 3, "%02d", (second % 3600) / 60);

    char sec[3] = {0};
    snprintf(sec, 3, "%02d", second % 60);

    std::string total_str = std::string(hour) + ":" + std::string(min) + ":" + std::string(sec);

    if (milliseconds_show)
    {
        char ms[4] = {0};
        snprintf(ms, 4, "%03d", total % 1000);
        total_str += "." + std::string(ms);
    }

    return total_str;
}
