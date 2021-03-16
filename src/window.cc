#include <gtkmm.h>
#include <thread>
#include <string>

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
    this->thread = new std::thread([this]
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
    Timer::second = 0;
    this->state = Timer::State::runnable;
    this->mutex.unlock();

    this->show_button();
}

/**
 * Нажатие на Пауза
 */
void Window::btn_pause_click()
{
    this->state = Timer::State::paused;
    this->mutex.try_lock();

    this->show_button();
}

/**
 * Нажатие на Отмена
 */
void Window::btn_cancel_click()
{
    Timer::second = 0;
    this->signal_time_change.emit();

    this->state = Timer::State::stopped;
    this->mutex.try_lock();

    this->show_button();
}

/**
 * Нажатие на Продолжить
 */
void Window::btn_resume_click()
{
    this->state = Timer::State::runnable;
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
    switch (this->state)
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
    Glib::ustring str = Window::format(Timer::second);
    this->lbl_time->set_label(str);
}

/**
 * Перевести секунды с формат таймера
 */
std::string Window::format(const int second)
{
    std::string hour = std::to_string(second / 3600);
    if (hour.length() == 1)
        hour = "0" + hour;

    std::string min = std::to_string((second % 3600) / 60);
    if (min.length() == 1)
        min = "0" + min;

    std::string sec = std::to_string(second % 60);
    if (sec.length() == 1)
        sec = "0" + sec;

    return hour + ":" + min + ":" + sec;
}
