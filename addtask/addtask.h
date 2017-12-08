GtkWidget *previousWindow;
GtkWidget *fixed;
GtkWidget *addTaskWindow;
GtkWidget *addtaskLbl;
GtkWidget *namelbl;
GtkWidget *descriptionlbl;
GtkWidget *duelbl,*assign;
GtkWidget *nameput,*descriptionput,*assignput,*dueput1;
GtkWidget *addtask;

char errname[50];
char errdue[50];

void showAddTaskWindow (GtkWidget *widget, gpointer data)
{
  
  addTaskWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title (GTK_WINDOW (addTaskWindow), "EasyCollab - Add Task");
  gtk_window_set_default_size (GTK_WINDOW (addTaskWindow), 800, 520);
  gtk_window_set_resizable (GTK_WINDOW (addTaskWindow), FALSE);
  gtk_window_set_position(GTK_WINDOW(addTaskWindow), GTK_WIN_POS_CENTER);
  gtk_widget_set_name(addTaskWindow, "addTaskWindow");

  addtaskLbl = gtk_label_new("Add Task");
  gtk_widget_set_name(addtaskLbl, "addtaskLbl");
  
  namelbl = gtk_label_new("Project Name");
  gtk_widget_set_name(namelbl, "namelbl");
  
  descriptionlbl = gtk_label_new("Project Description");
  gtk_widget_set_name(descriptionlbl, "descriptionlbl");
  
  duelbl = gtk_label_new("Due Date");
  gtk_widget_set_name(duelbl, "duelbl");
  
  assign = gtk_label_new("Assign To");
  gtk_widget_set_name(assign, "assign");
  
  nameput = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(nameput) , "Task Name");
  //gtk_entry_set_text(nameput,esm);
  gtk_widget_set_size_request (nameput, 1, 5);
  gtk_widget_queue_resize (nameput);
  gtk_widget_set_name(nameput, "nameput");
  
  descriptionput = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(descriptionput) , "About this task");
  //gtk_entry_set_text(descriptionput,descrip);
  gtk_widget_set_size_request (descriptionput, 5, 5);
  gtk_widget_set_name(descriptionput, "descriptionput");
  
  
  dueput1 = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(dueput1) , "JJ/MM/AAA");
  //gtk_entry_set_text(dueput1,due);
  gtk_entry_set_max_length (GTK_ENTRY(dueput1),10);
  gtk_widget_set_name(dueput1, "dueput1");
  
  
  assignput = gtk_combo_box_new_with_entry();
  gtk_widget_set_name(dueput1, "dueput1");
  
  addtask = gtk_button_new_with_label ("Add Task");
  gtk_widget_set_name(addtask, "addtask");
  //g_signal_connect (addtask, "clicked", G_CALLBACK (createTask), NULL);
  
  
  errornameLbl=gtk_label_new(errname);
  gtk_widget_set_name(errornameLbl, "errornameLbl");
  
  errordueLbl=gtk_label_new(errdue);
  gtk_widget_set_name(errordueLbl, "errordueLbl");
  
  fixed = gtk_fixed_new ();
  gtk_widget_set_size_request (fixed, 800, 520);
  gtk_widget_set_name(fixed, "fixed");
  gtk_fixed_put (GTK_FIXED (fixed), addtaskLbl, 30, 18);
  gtk_fixed_put (GTK_FIXED (fixed), namelbl, 40, 100);
  gtk_fixed_put (GTK_FIXED (fixed), nameput, 40, 130);
  gtk_fixed_put (GTK_FIXED (fixed), errornameLbl, 60, 180);
  gtk_fixed_put (GTK_FIXED (fixed), descriptionlbl, 40, 200);
  gtk_fixed_put (GTK_FIXED (fixed), descriptionput, 40, 230); 
  gtk_fixed_put (GTK_FIXED (fixed), duelbl, 40, 300); 
  gtk_fixed_put (GTK_FIXED (fixed), dueput1, 40, 330);
  gtk_fixed_put (GTK_FIXED (fixed), errordueLbl, 60, 380);
  gtk_fixed_put (GTK_FIXED (fixed), assign, 40, 400); 
  gtk_fixed_put (GTK_FIXED (fixed), assignput, 40, 430);
  gtk_fixed_put (GTK_FIXED (fixed), addtask, 250, 460);
  
  gtk_container_add(GTK_CONTAINER (addTaskWindow), fixed);

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
 
  GError *error = 0;
  gtk_css_provider_load_from_file(provider, g_file_new_for_path("./addtask/addtaskstyle.css"), &error);
  
  gtk_widget_show_all (addTaskWindow);

  if(widget != NULL)
  {
    previousWindow = gtk_widget_get_toplevel (widget);

    if (gtk_widget_is_toplevel (previousWindow))
    {
      gtk_widget_destroy (previousWindow);
    }
  }

}

  
  

  
  
  
  
  
  
