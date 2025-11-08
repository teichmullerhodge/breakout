#include "level_state.h"
#include "level_editor_state.h"
#include "../helpers/file_helpers.h"
#include "../appconfig/appconfig.h"
#include "../helpers/string_helpers.h"
#define MAX_ALLOWED_GRID_SIZE 70

void handle_level_open(GtkWidget *widget, gpointer data) {
  (void)widget;
  LevelEditorState *lvl_editor_state = (LevelEditorState*)data;
  
  GtkFileDialog *dialog = gtk_file_dialog_new();
  gtk_file_dialog_open(dialog, lvl_editor_state->window, NULL, new_level_selected, lvl_editor_state); 
}

void handle_save_level_open(GtkWidget *widget, gpointer data) {
  (void)widget;
  LevelEditorState *lvl_editor_state = (LevelEditorState*)data;
  
  GtkFileDialog *dialog = gtk_file_dialog_new();
  gtk_file_dialog_save(dialog, lvl_editor_state->window, NULL, handle_save_level, lvl_editor_state); 
}

void handle_save_level(GObject *source, GAsyncResult *res, gpointer udata){

  LevelEditorState *lvl_editor_state = (LevelEditorState*)udata;
  GtkFileDialog *dialog = GTK_FILE_DIALOG(source);
  GFile *file = gtk_file_dialog_save_finish(dialog, res, NULL);
 
  if(file == NULL) {
    perror("File is null. aborting operation.\n");
    return;
  }

  char *path = g_file_get_path(file);
  if(path == NULL) {
    perror("Path is null.\n");
    return;
  }
 

    char contents[128];
    size_t i = 0;
  
   for(size_t r = 0; r < EDITOR_ROWS; r++) {
    for(size_t c = 0; c < EDITOR_COL; c++) {
     GtkWidget *brick = gtk_grid_get_child_at(GTK_GRID(lvl_editor_state->level_grid), c, r);

      char **css_classes = gtk_widget_get_css_classes(brick);
      char *css_class = css_classes[0];
      bool active = strcmp(css_class, "brick-active") == 0;

      contents[i] = active ? '1' : '0';
      i++;
    }

    contents[i] = '\n';
    i++;
  
  }

   contents[i] = '\0';
   save_file_contents(path, contents);

}
 
void new_level_selected(GObject *source, GAsyncResult *res, gpointer udata) {
  
  LevelEditorState *lvl_editor_state = (LevelEditorState*)udata;
  GtkFileDialog *dialog = GTK_FILE_DIALOG(source);
  GFile *file = gtk_file_dialog_open_finish(dialog, res, NULL);
 
  if(file == NULL) {
    perror("File is null. aborting operation.\n");
    return;
  }

  char *path = g_file_get_path(file);
  if(path == NULL) {
    perror("Path is null. Can't read it's contents.\n");
    return;
  }
 
  char *contents = read_file_contents(path);
  remove_not_allowed_chars(contents);
  printf("Contents of the file: %s", contents);
  size_t str_size = strlen(contents);
  if(str_size < EDITOR_COL * EDITOR_ROWS) {
    printf("Contents of the string are too small to fit in the editor grid. - size: %ld", str_size);
    return; // handle this in a better way? 
  }
  size_t index = 0;
   printf("Full contents len: %ld\n", str_size);
   for(size_t r = 0; r < EDITOR_ROWS; r++) {
    for(size_t c = 0; c < EDITOR_COL; c++) {
     
     GtkWidget *brick = gtk_grid_get_child_at(GTK_GRID(lvl_editor_state->level_grid), c, r);

      bool active = contents[index] == '1';
    
      printf("Char at position: %ld - %d\n", index, contents[index]);
      gtk_widget_remove_css_class(brick, active ? "brick-inactive" : "brick-active");
      gtk_widget_add_css_class(brick, active ? "brick-active" : "brick-inactive");
      index++;
    }
  }
}

