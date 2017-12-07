GtkWidget *addProjectWindow;
GtkWidget *previousWindow;
GtkWidget *fixed;
GtkWidget *vbox;
GtkWidget *hbox,*hboxd;


GtkWidget *namelbl;
GtkWidget *descriptionlbl;
GtkWidget *duelbl;
GtkWidget *addprojectLbl;

GtkWidget *nameput,*membre,*add;
GtkWidget *descriptionput,*memberlbl;
GtkWidget *dueput1;
GtkWidget *dueput2;
GtkWidget *dueput3;
GtkWidget *duelbl1;
GtkWidget *duelbl2;
GtkWidget *test,*createproj;

GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;


static void showAddProjectWindow (GtkWidget *widget, gpointer data)
{
  
  addProjectWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title (GTK_WINDOW (addProjectWindow), "EasyCollab - Add Project");
  gtk_window_set_default_size (GTK_WINDOW (addProjectWindow), 800, 520);
  gtk_window_set_resizable (GTK_WINDOW (addProjectWindow), FALSE);
  gtk_window_set_position(GTK_WINDOW(addProjectWindow), GTK_WIN_POS_CENTER);
  gtk_widget_set_name(addProjectWindow, "addProjectWindow");

  addprojectLbl = gtk_label_new("Add Project");
  gtk_widget_set_name(addprojectLbl, "addprojectLbl");
  
  
  /*vbox = gtk_box_new(TRUE, 10);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(vbox), GTK_ORIENTATION_VERTICAL);
  gtk_widget_set_size_request (vbox, 300, 280);
  gtk_box_set_homogeneous (GTK_BOX (vbox), TRUE);
  gtk_widget_set_name(vbox, "vbox");*/
  
  hbox = gtk_box_new(TRUE, 5);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(hbox), GTK_ORIENTATION_HORIZONTAL);
  gtk_box_set_homogeneous (GTK_BOX (hbox), FALSE);
  gtk_widget_set_name(hbox, "hbox");
  
  namelbl = gtk_label_new("Project Name");
  gtk_widget_set_name(namelbl, "namelbl");
  
  descriptionlbl = gtk_label_new("Project Description");
  gtk_widget_set_name(descriptionlbl, "descriptionlbl");
  
  duelbl = gtk_label_new("Due Date");
  gtk_widget_set_name(duelbl, "duelbl");
  
  duelbl1 = gtk_label_new("/");
  gtk_widget_set_name(duelbl1, "duelbl1");
  
  duelbl2 = gtk_label_new("/");
  gtk_widget_set_name(duelbl2, "duelbl2");
  
  nameput = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(nameput) , "Project Name");
  gtk_widget_set_size_request (nameput, 1, 5);
  gtk_widget_queue_resize (nameput);
  gtk_widget_set_name(nameput, "nameput");
  
  descriptionput = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(descriptionput) , "Project Description");
  gtk_widget_set_size_request (descriptionput, 5, 5);
  gtk_widget_set_name(descriptionput, "descriptionput");
  
  
  dueput1 = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(dueput1) , "JJ");
  gtk_widget_set_size_request (nameput, 1, 5);
  gtk_entry_set_max_length (dueput1,2);
  gtk_widget_set_name(dueput1, "dueput1");
  
  dueput2 = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(dueput2) , "MM");
  gtk_widget_set_size_request (nameput, 1, 5);
  gtk_entry_set_max_length (dueput2,2);
  gtk_widget_set_name(dueput2, "dueput2");
  
  dueput3 = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(dueput3) , "AAAA");
  gtk_widget_set_size_request (nameput, 1, 5);
  gtk_entry_set_max_length (dueput3,4);
  gtk_widget_set_name(dueput3, "dueput3");
  
  gtk_box_pack_start(GTK_BOX(hbox), dueput1, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), duelbl1, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), dueput2, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), duelbl2, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hbox), dueput3, FALSE, FALSE, 0);
  
  memberlbl= gtk_label_new("Add Members");
  gtk_widget_set_name(memberlbl, "memberlbl");
  
  hboxd = gtk_box_new(TRUE, 5);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(hboxd), GTK_ORIENTATION_HORIZONTAL);
  gtk_box_set_homogeneous (GTK_BOX (hboxd), FALSE);
  gtk_widget_set_name(hboxd, "hboxd");
  
  membre = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(membre) , "New member");
  gtk_widget_set_size_request (membre, 1, 5);
  gtk_widget_set_name(membre, "membre");
  
  add = gtk_button_new_with_label ("ADD");
  gtk_widget_set_name(add, "add");
  //g_signal_connect (add, "clicked", G_CALLBACK (addMember), NULL);
  gtk_box_pack_start(GTK_BOX(hboxd), membre, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hboxd), add, FALSE, FALSE, 0);
  
  
  createproj = gtk_button_new_with_label ("Create Project");
  gtk_widget_set_name(createproj, "createproj");
  //g_signal_connect (createproj, "clicked", G_CALLBACK (createProject), NULL);
  
  /*gtk_box_pack_start(GTK_BOX(vbox), namelbl, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), nameput, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), descriptionlbl, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), descriptionput, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), duelbl, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);*/
  
    test = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(nameput) , "Project Name");
  gtk_widget_set_size_request (test, 1, 10);
  gtk_widget_set_name(test, "nameput");

  fixed = gtk_fixed_new ();
  gtk_widget_set_size_request (fixed, 800, 520);
  gtk_widget_set_name(fixed, "fixed");
  gtk_fixed_put (GTK_FIXED (fixed), addprojectLbl, 30, 18);
  gtk_fixed_put (GTK_FIXED (fixed), vbox, 450, 80); 
  gtk_fixed_put (GTK_FIXED (fixed), namelbl, 100, 100);
  gtk_fixed_put (GTK_FIXED (fixed), nameput, 100, 130);
  gtk_fixed_put (GTK_FIXED (fixed), descriptionlbl, 100, 210);
  gtk_fixed_put (GTK_FIXED (fixed), descriptionput, 100, 240); 
  gtk_fixed_put (GTK_FIXED (fixed), duelbl, 140, 320); 
  gtk_fixed_put (GTK_FIXED (fixed), hbox, 20, 350);
  gtk_fixed_put (GTK_FIXED (fixed), memberlbl, 550, 100);
  gtk_fixed_put (GTK_FIXED (fixed), hboxd, 550, 130);
  gtk_fixed_put (GTK_FIXED (fixed), createproj, 640, 450);
  gtk_container_add(GTK_CONTAINER (addProjectWindow), fixed);

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
 
  GError *error = 0;
  gtk_css_provider_load_from_file(provider, g_file_new_for_path("./addproject/addprojectstyle.css"), &error);
  
  gtk_widget_show_all (addProjectWindow);

  if(widget != NULL)
  {
    previousWindow = gtk_widget_get_toplevel (widget);

    if (gtk_widget_is_toplevel (previousWindow))
    {
      gtk_widget_destroy (previousWindow);
    }
  }

}
