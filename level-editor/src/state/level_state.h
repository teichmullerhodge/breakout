#ifndef LEVEL_STATE_H
#define LEVEL_STATE_H 

#include <gtk/gtk.h>

void handle_level_open(GtkWidget *widget, gpointer data); 
void handle_save_level_open(GtkWidget *widget, gpointer data);
void new_level_selected(GObject *source, GAsyncResult *res, gpointer udata);
void handle_save_level(GObject *source, GAsyncResult *res, gpointer udata);

#endif 
