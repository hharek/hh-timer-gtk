#include <gtkmm.h>
#include <iostream>

void btn_start_click();

Gtk::Window* window = nullptr;
Gtk::Label* timeLbl = nullptr;
Gtk::Button* btn_start = nullptr;

int main (int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "ru.hharek.hh-timer");

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("../glade/home.glade");

    builder->get_widget("home", window);
    builder->get_widget("time-lbl", timeLbl);

    builder->get_widget("btn-start", btn_start);
    btn_start->signal_clicked().connect(sigc::ptr_fun(&btn_start_click));

    return app->run(*window);
}

void btn_start_click ()
{
    timeLbl->set_label("00:00:00");
}