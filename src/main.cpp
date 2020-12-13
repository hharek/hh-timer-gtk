#include <gtkmm.h>

int main (int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "ru.hharek.hh-timer");

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../glade/home.glade");

    Gtk::Window* window = nullptr;
    builder->get_widget("home", window);

    return app->run(*window);
}