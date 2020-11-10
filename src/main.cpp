#include <gtk/gtk.h>

int main (int argc, char **argv)
{
    gtk_init (&argc, &argv);

    GtkBuilder * builder = gtk_builder_new_from_file("/hh/site/hh-timer/glade/home.glade");
    GtkWidget * window = GTK_WIDGET(gtk_builder_get_object(builder, "home"));

    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_widget_show_all (window);

    gtk_main ();
    return 0;
}