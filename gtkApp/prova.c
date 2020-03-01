#include <gtk/gtk.h>

static void activate (GtkApplication* , gpointer);
static void preferences_activated (GSimpleAction *, GVariant *, gpointer);
static void quit_activated (GSimpleAction *, GVariant *, gpointer);
static void example_app_startup(GApplication *);
static void example_app_class_init(ExampleAppClass *);

/*main dell'applicazione dove la creo e la faccio partire*/
int main (int argc, char **argv){
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
/*Questa è la fase in cui si popola l'app con una finestra a cui do le direttive*/
static void activate(GtkApplication* app, gpointer user_data){
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Ricerca");
  gtk_window_set_default_size (GTK_WINDOW (window), 400, 300);
  gtk_widget_show_all (window);
}
/*Da qui in poi ci sono i leoni*/
/*Qui provo ad impleemntare un menù dell'applicazione gnome3 compliant*/
static void preferences_activated (GSimpleAction *action, GVariant *parameter, gpointer app){
}

static void quit_activated (GSimpleAction *action, GVariant *parameter, gpointer app){
  g_application_quit (G_APPLICATION (app));
}

static GActionEntry app_entries[] =
{
  { "preferences", preferences_activated, NULL, NULL, NULL },
  { "quit", quit_activated, NULL, NULL, NULL }
};

static void example_app_startup(GApplication *app){
  GtkBuilder *builder;
  GMenuModel *app_menu;
  const gchar *quit_accels[2] = { "<Ctrl>Q", NULL };

  G_APPLICATION_CLASS(example_app_parent_class)->startup(app);
  g_action_map_add_action_entries(G_ACTION_MAP (app), app_entries, G_N_ELEMENTS(app_entries), app);
  gtk_application_set_accels_for_action(GTK_APPLICATION(app), "app.quit", quit_accels);

  builder = gtk_builder_new_from_resource("menu.xml");
  app_menu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
  gtk_application_set_app_menu (GTK_APPLICATION (app), app_menu);
  g_object_unref (builder);
}

static void example_app_class_init(ExampleAppClass *class){
  G_APPLICATION_CLASS (class)->startup = example_app_startup;
  /*...*/
}

