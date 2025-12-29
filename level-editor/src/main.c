#include "appconfig/appconfig.h"
#include <gtk/gtk.h>
#include "layout/layout.h"
#include "state/level_editor_state.h"
#include "widgets/widget_config.h"
#include "widgets/widget_touchable.h"
#include <string.h>
#include "state/level_state.h"
#include "state/level_editor_state.h"

static void handle_brick_clicked(GtkWidget *widget, gpointer data) {
    (void)data;
    char **css_names = gtk_widget_get_css_classes(widget);
    char *css = css_names[0];
    
    bool active = css != NULL && strcmp("brick-inactive", css) == 0;
    gtk_widget_remove_css_class(widget, active ? "brick-inactive" : "brick-active");
    gtk_widget_add_css_class(widget, active ? "brick-active" : "brick-inactive");
    g_strfreev(css_names);
}

static void on_activate(GtkApplication *app) {
  
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "../resources/css/index.css");
  gtk_style_context_add_provider_for_display(gdk_display_get_default(),
                                             GTK_STYLE_PROVIDER(provider),
                                             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  g_object_unref(provider);

  GtkWidget *window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), APP_CONFIG_WIN_TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window), APP_CONFIG_WIN_WIDTH, APP_CONFIG_WIN_HEIGHT);
  gtk_widget_add_css_class(window, "window-main");
 

  GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_set_spacing(GTK_BOX(main_box), 10);
   
  GtkWidget *level_grid = gtk_grid_new();
  gtk_grid_set_column_spacing(GTK_GRID(level_grid), 5);
  gtk_grid_set_row_spacing(GTK_GRID(level_grid), 5);
   for(size_t c = 0; c < EDITOR_COL; c++) {
    for(size_t r = 0; r < EDITOR_ROWS; r++) {
       GtkWidget *brick = touchable(" ", NULL, NULL);
      gtk_widget_add_css_class(brick, "brick-inactive");
      gtk_grid_attach(GTK_GRID(level_grid), brick, c, r, 1, 1);  
      g_signal_connect (brick, "clicked", G_CALLBACK (handle_brick_clicked), NULL);



    }
  }


  LevelEditorState *state = malloc(sizeof(LevelEditorState));
  state->window = malloc(sizeof(GtkWindow));
  state->level_grid = malloc(sizeof(GtkWidget));

  state->window = GTK_WINDOW(window);
  state->level_grid = level_grid;
  GtkWidget *done_btn = touchable("Save", "media-floppy-symbolic", "done-btn");
  g_signal_connect(done_btn, "clicked", G_CALLBACK (handle_save_level_open), state);

   
  GtkWidget *load_btn = touchable("Open level", "folder-saved-search-symbolic", "open-level-btn");
   g_signal_connect (load_btn, "clicked", G_CALLBACK (handle_level_open), state);
   expand_all(main_box);
   expand_all(level_grid);
   GtkWidget *buttons_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
   gtk_box_set_spacing(GTK_BOX(buttons_box), 10);
  
   gtk_box_append(GTK_BOX(buttons_box), load_btn);
   gtk_box_append(GTK_BOX(buttons_box), done_btn);

   set_positioning(main_box, &(struct WidgetPositioning){
      GTK_ALIGN_CENTER,
      GTK_ALIGN_CENTER, 
      true, 
      true 
   });

   gtk_widget_add_css_class(main_box, "main-box");
   gtk_widget_add_css_class(level_grid, "level-grid");


   gtk_box_append(GTK_BOX(main_box), level_grid);
   gtk_box_append(GTK_BOX(main_box), buttons_box);
  
  
   gtk_window_set_child(GTK_WINDOW(window), main_box);   
   gtk_window_present(GTK_WINDOW(window));

  

}

int main(int argc, char **argv) {

  GtkApplication *app =
      gtk_application_new(APP_CONFIG_APP_ID, APP_CONFIG_APP_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}
