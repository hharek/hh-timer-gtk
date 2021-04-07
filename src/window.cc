#include <gtkmm.h>
#include <thread>
#include <string>
#include <chrono>

#include "timer.h"
#include "window.h"
#include "worker.h"

/**
 * Конструктор
 */
Window::Window (BaseObjectType* widget, Glib::RefPtr<Gtk::Builder> & builder) :
    Gtk::Window(widget),
    builder(builder),
    signal_time_change()
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

    /* Показать кнопки */
    this->show_button();

    /* Подписываемся на сигнал «signal_time_change» */
    this->signal_time_change.connect(sigc::mem_fun(*this, &Window::slot_time_change));

    /* Запускаем воркер */
    new std::thread([this]
    {
       auto worker = new Worker();
       worker->run(this);
    });

    /* Блокируем мьютекс */
    this->mutex.lock();
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
    Timer::state = Timer::State::runnable;

    this->mutex.unlock();

    this->show_button();
}

/**
 * Нажатие на Пауза
 */
void Window::btn_pause_click()
{
    Timer::total += duration_cast<milliseconds>(steady_clock::now() - Timer::timestamp);
    Timer::timestamp = steady_clock::now();

    Timer::state = Timer::State::paused;

    this->mutex.try_lock();

    this->show_button();
}

/**
 * Нажатие на Отмена
 */
void Window::btn_cancel_click()
{
    Timer::total = 0ms;
    Timer::timestamp = steady_clock::now();

    this->signal_time_change.emit();

    Timer::state = Timer::State::stopped;

    this->mutex.try_lock();

    this->show_button();
}

/**
 * Нажатие на Продолжить
 */
void Window::btn_resume_click()
{
    Timer::total += duration_cast<milliseconds>(steady_clock::now() - Timer::timestamp);
    Timer::timestamp = steady_clock::now();

    Timer::state = Timer::State::runnable;

    this->mutex.unlock();

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
    switch (Timer::state)
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
 * Сменить время на таймере
 */
void Window::slot_time_change () const
{
    Timer::total += duration_cast<milliseconds>(steady_clock::now() - Timer::timestamp);
    Timer::timestamp = steady_clock::now();

    Glib::ustring str = Window::format(Timer::total.count());
    this->lbl_time->set_label(str);
}

/**
 * Перевести секунды с формат таймера
 */
std::string Window::format(const int total)
{
    int second = total / 1000;

    char hour[3] = {0};
    snprintf(hour, 3, "%02d", second / 3600);

    char min[3] = {0};
    snprintf(min, 3, "%02d", (second % 3600) / 60);

    char sec[3] = {0};
    snprintf(sec, 3, "%02d", second % 60);

    char ms[4] = {0};
    snprintf(ms, 4, "%03d", total % 1000);

    return std::string(hour) + ":" + std::string(min) + ":" + std::string(sec) + "." + std::string(ms);
}
