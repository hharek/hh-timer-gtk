#include <gtkmm.h>

#include "timer.h"
#include "window.h"

/* Инициализируем статические переменные */
int Timer::second = 0;

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
