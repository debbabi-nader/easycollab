GtkWidget *signupWindow;
GtkWidget *previousWindow;
GtkWidget *fixed;
GtkWidget *vbox;
GtkWidget *hbox;

GtkWidget *signupLbl;
GtkWidget *firstName;
GtkWidget *name;
GtkWidget *email;
GtkWidget *username;
GtkWidget *password;
GtkWidget *projectManager;
GtkWidget *employee;
GSList *roleList;
GtkWidget *signupBtn;

GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;

char role[5];


static void roleChange(GtkWidget *widget, gpointer data) {
    strcpy(role, data);
    printf("%s\n" , role);
}


static void signup (GtkWidget *widget, gpointer data)
{

}


static void showSignupWindow (GtkWidget *widget, gpointer data)
{
  
  signupWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title (GTK_WINDOW (signupWindow), "EasyCollab - Sign up");
  gtk_window_set_default_size (GTK_WINDOW (signupWindow), 800, 520);
  gtk_window_set_resizable (GTK_WINDOW (signupWindow), FALSE);
  gtk_window_set_position(GTK_WINDOW(signupWindow), GTK_WIN_POS_CENTER);
  gtk_widget_set_name(signupWindow, "signupWindow");
  
  vbox = gtk_box_new(TRUE, 2);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(vbox), GTK_ORIENTATION_VERTICAL);
  gtk_widget_set_size_request (vbox, 300, 400);
  gtk_box_set_homogeneous (GTK_BOX (vbox), FALSE);
  gtk_widget_set_name(vbox, "vbox");

  hbox = gtk_box_new(TRUE, 0);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(hbox), GTK_ORIENTATION_HORIZONTAL);
  gtk_box_set_homogeneous (GTK_BOX (hbox), FALSE);
  gtk_widget_set_name(hbox, "hbox");

  signupLbl = gtk_label_new("Sign up");
  gtk_widget_set_name(signupLbl, "signupLbl");

  firstName = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(firstName) , "First Name");
  gtk_widget_set_name(firstName, "firstName");

  name = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(name) , "Name");
  gtk_widget_set_name(name, "name");

  email = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(email) , "E-mail");
  gtk_widget_set_name(email, "email");

  username = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(username) , "Username");
  gtk_widget_set_name(username, "username");

  password = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(password) , "Password");
  gtk_entry_set_visibility(GTK_ENTRY(password) , FALSE);
  gtk_widget_set_name(password, "password");

  projectManager = gtk_radio_button_new_with_label (NULL, "Project Manager");
  gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (projectManager), TRUE);
  g_signal_connect (projectManager, "pressed", G_CALLBACK (roleChange), "PM");
  gtk_box_pack_start(GTK_BOX(hbox), projectManager, FALSE, FALSE, 0);

  roleList = gtk_radio_button_get_group (GTK_RADIO_BUTTON (projectManager));

  employee = gtk_radio_button_new_with_label (roleList, "Employee");
  g_signal_connect (employee, "pressed", G_CALLBACK (roleChange), "EM");
  gtk_box_pack_start(GTK_BOX(hbox), employee, FALSE, FALSE, 25);

  signupBtn = gtk_button_new_with_label ("SIGN UP");
  gtk_widget_set_name(signupBtn, "signupBtn");
  g_signal_connect (signupBtn, "clicked", G_CALLBACK (signup), NULL);

  gtk_box_pack_start(GTK_BOX(vbox), signupLbl, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), firstName, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), name, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), email, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), username,TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), password, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 2);
  gtk_box_pack_start(GTK_BOX(vbox), signupBtn, TRUE, TRUE, 16);

  fixed = gtk_fixed_new ();
  gtk_widget_set_size_request (fixed, 800, 520);
  gtk_widget_set_name(fixed, "fixed");
  gtk_fixed_put (GTK_FIXED (fixed), vbox, 450, 40);
  gtk_container_add(GTK_CONTAINER (signupWindow), fixed);

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  GError *error = 0;
  gtk_css_provider_load_from_file(provider, g_file_new_for_path("./signup/signup-style.css"), &error);
  
  gtk_widget_show_all (signupWindow);

  if(widget != NULL)
  {
    previousWindow = gtk_widget_get_toplevel (widget);

    if (gtk_widget_is_toplevel (previousWindow))
    {
      gtk_widget_destroy (previousWindow);
    }
  }

}
