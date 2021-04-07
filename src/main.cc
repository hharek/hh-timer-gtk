#include <gtkmm.h>
#include <chrono>

#include "timer.h"
#include "window.h"

/* Инициализируем статические переменные */
using namespace std::chrono;

steady_clock::time_point Timer::timestamp = steady_clock::now();
milliseconds Timer::total = {0ms};
Timer::State Timer::state = Timer::State::stopped;

/**
 * main
 */
int main (int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "ru.hharek.hh-timer");

    /* Собираем окно и вешаем на объект Window */
    Window * window;
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../glade/home.glade");
    builder->get_widget_derived("home", window);

    return app->run(*window);
}
