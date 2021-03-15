#include <gtkmm.h>

#include "window.h"

int main (int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "ru.hharek.hh-timer");

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../glade/home.glade");

    Window * window;
    builder->get_widget_derived("home", window);

    return app->run(*window);
}
