#include <stdio.h>
#include <iostream>
#include <cairo.h>
#include <gtk/gtk.h>
#include "./fparser/fparser.hh"

using namespace std;

static void do_drawing(cairo_t *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr)
{
  do_drawing(cr);
  return FALSE;
}

static void do_drawing(cairo_t *cr)
{
    //El eje de las Y
	cairo_stroke(cr);
  	cairo_set_source_rgb(cr, 0.3, 0, 0.4);
  	cairo_set_line_width(cr, 2.5);
  	cairo_set_font_size(cr,0);
  	cairo_move_to(cr,20,20);
    cairo_line_to(cr,20,480);
    cairo_stroke(cr);
    cairo_save(cr);
}


int main(int argc, char *argv[])
{
	cairo_t *cr;
	GtkWidget *window;
	GtkWidget *darea;
	gtk_init(&argc, &argv); 	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), darea);
 	  	
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500); 
  	gtk_window_set_title(GTK_WINDOW(window), "Graficador");
	g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), cr); 
  	gtk_widget_show_all(window);
	gtk_main();
	return 0;

}
