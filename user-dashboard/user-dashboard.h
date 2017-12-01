GtkWidget *userDashboardWindow;
GtkWidget *previousWindow;
GtkWidget *fixed;
GtkWidget *vbox;
GtkWidget *hbox;

GtkWidget *dashboardLbl;

GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;


static void showUserDashboardWindow (GtkWidget *widget, gpointer data)
{
  
  userDashboardWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title (GTK_WINDOW (userDashboardWindow), "EasyCollab - Dashboard");
  gtk_window_set_default_size (GTK_WINDOW (userDashboardWindow), 800, 520);
  gtk_window_set_resizable (GTK_WINDOW (userDashboardWindow), FALSE);
  gtk_window_set_position(GTK_WINDOW(userDashboardWindow), GTK_WIN_POS_CENTER);
  gtk_widget_set_name(userDashboardWindow, "userDashboardWindow");

  dashboardLbl = gtk_label_new("Dashboard");
  gtk_widget_set_name(dashboardLbl, "dashboardLbl");

  fixed = gtk_fixed_new ();
  gtk_widget_set_size_request (fixed, 800, 520);
  gtk_widget_set_name(fixed, "fixed");
  gtk_fixed_put (GTK_FIXED (fixed), dashboardLbl, 30, 18);
  gtk_container_add(GTK_CONTAINER (userDashboardWindow), fixed);

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
 
  GError *error = 0;
  gtk_css_provider_load_from_file(provider, g_file_new_for_path("./user-dashboard/user-dashboard-style.css"), &error);
  
  gtk_widget_show_all (userDashboardWindow);

  if(widget != NULL)
  {
    previousWindow = gtk_widget_get_toplevel (widget);

    if (gtk_widget_is_toplevel (previousWindow))
    {
      gtk_widget_destroy (previousWindow);
    }
  }

}
