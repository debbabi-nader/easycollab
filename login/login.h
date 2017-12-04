GtkWidget *loginWindow;
GtkWidget *previousWindow;
GtkWidget *fixed;
GtkWidget *vbox;
GtkWidget *hbox;
GtkWidget *eventBox;

GtkWidget *loginLbl;
GtkWidget *username;
GtkWidget *password;
GtkWidget *loginBtn;
GtkWidget *signupBottomLbl;
GtkWidget *signupLink;
GtkWidget *errorLbl;

GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;

FILE *usersf;
User user;
int exist;


static void login (GtkWidget *widget, gpointer data)
{

  usersf = fopen("./files/users.txt", "r");
  
  if(usersf != NULL) {

    while(fscanf(usersf, "%d %s %s %s %s %s %s %d", &user.id, user.name, user.firstName, user.username, user.password, user.email, user.role, &user.connected) == 8) {
      
      if(strcmp(user.username, gtk_entry_get_text (GTK_ENTRY (username))) != 0) {
	
	exist = 0;
        
      }
      else {
        
	if(strcmp(user.password, gtk_entry_get_text (GTK_ENTRY (password))) != 0) {
	  gtk_label_set_text(GTK_LABEL (errorLbl), "* Wrong password!");
	  gtk_entry_set_text (GTK_ENTRY (password), "");
        }
        else {
	  gtk_label_set_text(GTK_LABEL (errorLbl), "");
	  showUserDashboardWindow(widget, NULL);
        }

	exist = 1;
	break;

      }
      
    }

    if(exist == 0) {
      gtk_label_set_text(GTK_LABEL (errorLbl), "* No existing account with the provided\nusername!");
      gtk_entry_set_text (GTK_ENTRY (password), "");
    }

  }
  else {
    printf("Error while opening the file.\n");
  }

  fclose(usersf);

}


static void showLoginWindow (GtkWidget *widget, gpointer data)
{

  loginWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title (GTK_WINDOW (loginWindow), "EasyCollab - Login");
  gtk_window_set_default_size (GTK_WINDOW (loginWindow), 800, 520);
  gtk_window_set_resizable (GTK_WINDOW (loginWindow), FALSE);
  gtk_window_set_position(GTK_WINDOW(loginWindow), GTK_WIN_POS_CENTER);
  gtk_widget_set_name(loginWindow, "loginWindow");
  
  vbox = gtk_box_new(TRUE, 10);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(vbox), GTK_ORIENTATION_VERTICAL);
  gtk_widget_set_size_request (vbox, 300, 280);
  gtk_box_set_homogeneous (GTK_BOX (vbox), FALSE);
  gtk_widget_set_name(vbox, "vbox");

  hbox = gtk_box_new(TRUE, 0);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(hbox), GTK_ORIENTATION_HORIZONTAL);
  gtk_box_set_homogeneous (GTK_BOX (hbox), FALSE);
  gtk_widget_set_name(hbox, "hbox");

  loginLbl = gtk_label_new("Login");
  gtk_widget_set_name(loginLbl, "loginLbl");
  
  errorLbl = gtk_label_new("");
  gtk_widget_set_name(errorLbl, "errorLbl");

  username = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(username) , "Username");
  gtk_widget_set_name(username, "username");

  password = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(password) , "Password");
  gtk_entry_set_visibility(GTK_ENTRY(password) , FALSE);
  gtk_widget_set_name(password, "password");

  loginBtn = gtk_button_new_with_label ("CONNECTION");
  gtk_widget_set_name(loginBtn, "loginBtn");
  g_signal_connect (loginBtn, "clicked", G_CALLBACK (login), NULL);

  signupBottomLbl = gtk_label_new("New to EasyCollab?");
  gtk_widget_set_name(signupBottomLbl, "signupBottomLbl");

  signupLink = gtk_label_new("Sign up now");
  gtk_widget_set_name(signupLink, "signupLink");

  eventBox = gtk_event_box_new();
  gtk_container_add (GTK_CONTAINER (eventBox), signupLink);
  gtk_widget_set_events (eventBox, GDK_BUTTON_PRESS_MASK);
  g_signal_connect (eventBox, "button_press_event", G_CALLBACK (showSignupWindow), NULL);
  
  gtk_box_pack_start(GTK_BOX(hbox), signupBottomLbl, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), eventBox, FALSE, FALSE, 5);

  gtk_box_pack_start(GTK_BOX(vbox), loginLbl, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), errorLbl, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), username,TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), password, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), loginBtn, TRUE, TRUE, 16);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
  
  fixed = gtk_fixed_new ();
  gtk_widget_set_size_request (fixed, 800, 520);
  gtk_widget_set_name(fixed, "fixed");
  gtk_fixed_put (GTK_FIXED (fixed), vbox, 450, 80);  
  gtk_container_add(GTK_CONTAINER (loginWindow), fixed);

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
 
  GError *error = 0;
  gtk_css_provider_load_from_file(provider, g_file_new_for_path("./login/login-style.css"), &error);
  
  gtk_widget_show_all (loginWindow);

  if(widget != NULL)
  {
    previousWindow = gtk_widget_get_toplevel (widget);

    if (gtk_widget_is_toplevel (previousWindow))
    {
      gtk_widget_destroy (previousWindow);
    }
  }

}
