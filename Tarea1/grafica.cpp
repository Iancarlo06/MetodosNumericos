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
double epsilon = 0.00000010; //Esto es por si la funcion es casi una linea horizontal en el intervalo asignado
string func;
FunctionParser fparser;

static void do_drawing(cairo_t *cr)
{
	fparser.Parse(func, "x");	
	int parti = 1000;
	double aux,faux;	
	double imaxi = a;
	double fmaxi = fparser.Eval(&a);
	double imini= a;
	double fmini = fmaxi;
	//Calculo el máximo y el minimo de la función para escoger los ejes X y Y
	for(int i = 0; i < parti+1; i++)
	{
			aux = a + i*(b-a)/parti;
			faux = fparser.Eval(&aux);
			if(faux > fmaxi) 
			{
				fmaxi = faux;
				imaxi = aux;			
			}
			if(faux < fmini) 
			{
				imini = aux;
				fmini = faux;
			}
	}
	char *text;
	double num;
	string mystr;	
 	//El eje de las Y
	cairo_stroke(cr);
	cairo_set_font_size(cr,8);  	
  	cairo_set_source_rgb(cr, 0, 0, 0);
  	cairo_set_line_width(cr, 2.5);
  	cairo_move_to(cr,40,40);
  	cairo_line_to(cr,40,760);
	if(fmaxi - fmini < epsilon)
	{
		fmaxi = fmaxi + 10;
		fmini = fmini - 10;
	}  	
  	for(int i = 0; i < 11; i++)
	{
		num = fmini + i*(fmaxi-fmini)/10; 
		mystr = to_string(num);
		text = &mystr[0];
		cairo_move_to(cr,20, 760 - i*72);
		cairo_show_text(cr,text);
	}
	//El eje de las X
	for(int i = 0; i < 11; i++)
	{
		num = a + i*(b-a)/10; 
		mystr = to_string(num);
		text = &mystr[0];
		cairo_move_to(cr,20 + i*92, 780);
		cairo_show_text(cr,text);
	}
	cairo_move_to(cr,40,760);
   	cairo_line_to(cr,980,760);
   	cairo_stroke(cr);
   	cairo_save(cr);
	//graficamos la función
	cairo_stroke(cr);
	cairo_set_line_width(cr, 5);
  	cairo_set_source_rgb(cr, 0.88, 0.69, 1);
	if(fmaxi - fmini > epsilon)
	{	
		faux = fparser.Eval(&a);	
		num = (faux - fmini)/(fmaxi - fmini);
		num *= 720.0;
		cairo_move_to(cr,40, 760 - num);
		for(int i = 1; i < 1001; i++)
  		{
			aux = a + i*(b-a)/1000;
			faux = fparser.Eval(&aux);
			num = (faux - fmini)/(fmaxi - fmini);
			num *= 720.0;		
			cairo_line_to(cr, 40 + i*0.92,760 - num); 
			cairo_move_to(cr, 40 + i*0.92,760 - num);
		}
	}
	else
	{
		cairo_move_to(cr,40,400);
		cairo_line_to(cr,980l,700);		
	}		
	cairo_stroke(cr);
   cairo_save(cr); 
}


int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		cout<<"Error: Numero incorrecto de argumentos";   
   	}
	a = atof(argv[1]);
	b = atof(argv[2]);
	func = argv[3];
	fparser.Parse(func,"x");	
	fparser.AddConstant("pi", 3.1415926535897932);

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
