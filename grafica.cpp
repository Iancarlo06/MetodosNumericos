#include <stdio.h>
#include <iostream>
#include <cairo.h>
#include <gtk/gtk.h>
#include <string>
#include <math.h>
#include "./fparser/fparser.hh"

using namespace std;

static void do_drawing(cairo_t *);

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr)
{
  do_drawing(cr);
  return FALSE;
}

double a,b;
string func;

static void do_drawing(cairo_t *cr)
{
   //El eje de las Y
	cairo_stroke(cr);
  	cairo_set_source_rgb(cr, 0, 0, 0);
  	cairo_set_line_width(cr, 2.5);
  	cairo_set_font_size(cr,0);
  	cairo_move_to(cr,40,40);
  	cairo_line_to(cr,40,760);
   cairo_stroke(cr);
	//El eje de las X
	cairo_stroke(cr);
	cairo_set_font_size(cr,8);
  	char *text;
	double num;
	string mystr;
	for(int i = 0; i < 11; i++)
	{
		num = a + i*(b-a)/10; 
		string mystr = to_string(num);
		text = &mystr[0];
		cairo_move_to(cr,20 + i*92, 780);
		cairo_show_text(cr,text);
	}
	cairo_move_to(cr,40,760);
   cairo_line_to(cr,980,760);
	cairo_stroke(cr);
    cairo_save(cr);
}


int main(int argc, char *argv[])
{
	a = atof(argv[1]);
	b = atof(argv[2]);
	func = argv[3];
	FunctionParser fparser;
   int x = fparser.Parse(func,"x");	
	
	cairo_t *cr;
	GtkWidget *window;
	GtkWidget *darea;
	gtk_init(&argc, &argv); 	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	darea = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), darea);
 	  	
  	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  	gtk_window_set_default_size(GTK_WINDOW(window), 1000, 800); 
  	gtk_window_set_title(GTK_WINDOW(window), "Graficador");
	g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), cr); 
  	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
