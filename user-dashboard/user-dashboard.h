GtkWidget *userDashboardWindow;
GtkWidget *previousWindow;
GtkWidget *fixed;
GtkWidget *vbox;
GtkWidget *hbox;

GtkWidget *dashboardLbl;
GtkWidget *projectLbl;
GtkWidget *createProjectBtn;
GtkWidget *projectBtn;
GtkWidget *projectNameLbl;

GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;

FILE *usersf;
User user;

FILE *projectsf;
Project project;

char projectStartDate[100];
char projectFinishDate[100];
char projectDiscussion[100];
char projectGroupMembers[100];
char projectTaskList[100];
char projectDocumentList[100];
int adminID;

int *arg;
int userID;

ProjectDashboardParam param;


static void goToProjectDashboard (GtkWidget *widget, gpointer data)
{

  GtkWidget *buttonChild = gtk_bin_get_child (GTK_BIN(widget));

  const char *clickedProjectName = gtk_label_get_text (GTK_LABEL (buttonChild));

  printf("Clicked Project: %s\n", clickedProjectName);

  param.connectedUserID = user.id;
  strcpy(param.selectedProjectName, clickedProjectName);

  showProjectDashboardWindow(widget, &param);

}


static void showUserDashboardWindow (GtkWidget *widget, gpointer data)
{

  arg = data;
  userID = *arg;
  printf("%d\n", userID);

  /* get the connected user using the userID param passed from the login interface */

  usersf = fopen("./files/users.txt", "r");
  
  if(usersf != NULL) {

    while(fscanf(usersf, "%d %s %s %s %s %s %s %d", &user.id, user.name, user.firstName, user.username, user.password, user.email, user.role, &user.connected) == 8) {
      
      if(user.id == userID) {

        //printf("%s\n", user.name);
	//printf("%d - %d\n", user.id, userID);
        break;

      }
 
    }

  }
  else {
    printf("Error while opening users file.\n");
  }

  //fclose(usersf);

  printf("%s\n", user.name);

  /* end: get the connected user */


  /* initialize the interface */

  userDashboardWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title (GTK_WINDOW (userDashboardWindow), "EasyCollab - User Dashboard");
  gtk_window_set_default_size (GTK_WINDOW (userDashboardWindow), 800, 520);
  gtk_window_set_resizable (GTK_WINDOW (userDashboardWindow), FALSE);
  gtk_window_set_position(GTK_WINDOW(userDashboardWindow), GTK_WIN_POS_CENTER);
  gtk_widget_set_name(userDashboardWindow, "userDashboardWindow");

  fixed = gtk_fixed_new ();
  gtk_widget_set_size_request (fixed, 800, 520);
  gtk_widget_set_name(fixed, "fixed");

  vbox = gtk_box_new(TRUE, 2);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(vbox), GTK_ORIENTATION_VERTICAL);
  gtk_widget_set_size_request (vbox, 720, 280);
  gtk_box_set_homogeneous (GTK_BOX (vbox), FALSE);
  gtk_widget_set_name(vbox, "vbox");

  hbox = gtk_box_new(TRUE, 0);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(hbox), GTK_ORIENTATION_HORIZONTAL);
  gtk_box_set_homogeneous (GTK_BOX (hbox), FALSE);
  gtk_widget_set_name(hbox, "hbox");

  dashboardLbl = gtk_label_new("Dashboard");
  gtk_widget_set_name(dashboardLbl, "dashboardLbl");

  projectLbl = gtk_label_new("");
  gtk_widget_set_name(projectLbl, "projectLbl");

  if(strcmp(user.role, "PM") == 0) {

    gtk_label_set_text(GTK_LABEL (projectLbl), "Your Projects");

    createProjectBtn = gtk_button_new_with_label ("+ Add Project");
    gtk_widget_set_name(createProjectBtn, "createProjectBtn");
    //g_signal_connect (createProjectBtn, "clicked", G_CALLBACK (showAddProjectWindow), NULL);

    gtk_box_pack_start(GTK_BOX(hbox), projectLbl, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), createProjectBtn, FALSE, FALSE, 0);

  }
  else if(strcmp(user.role, "EM") == 0) {

    gtk_label_set_text(GTK_LABEL (projectLbl), "Your Collaborations");

    gtk_box_pack_start(GTK_BOX(hbox), projectLbl, FALSE, FALSE, 0);

  }

  gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 10);

  /* get the users projects whether his is a project manager or an employee */

  projectsf = fopen("./files/projects.txt", "r");
  
  if(projectsf != NULL)
  {

    while(fscanf(projectsf,
		 "projectID:%d\n"
		 "projectName:%[^\n]\n"
		 "projectDescription:%[^\n]\n"
		 "projectStartDate:%[^\n]\n"
 		 "projectFinishDate:%[^\n]\n"
		 "projectLength:%d\n"
		 "projectState:%[^\n]\n"
		 "projectDiscussion:%[^\n]\n"
		 "projectAdmin:%d\n"
		 "projectGroupMembers:%[^\n]\n"
		 "projectTaskList:%[^\n]\n"
		 "projectDocumentList:%[^\n]\n"
		 "$\n",
		 &project.id,
		 project.label,
		 project.description,
		 projectStartDate,
		 projectFinishDate,
		 &project.projectLength,
		 project.state,
		 projectDiscussion,
		 &adminID,
		 projectGroupMembers,
		 projectTaskList,
		 projectDocumentList) == 12) {


      if(strcmp(user.role, "PM") == 0) {

        //printf("Connected user is a project manager, his projects:\n\n");

        if(user.id == adminID) {

	  printf("projectID:%d\n"
		 "projectName:%s\n"
                 "projectDescription:%s\n"
		 "projectStartDate:%s\n"
		 "projectFinishDate:%s\n"
		 "projectLength:%d\n"
		 "projectState:%s\n"
		 "projectDiscussion:%s\n"
		 "projectAdmin:%d\n"
		 "projectGroupMembers:%s\n"
		 "projectTaskList:%s\n"
		 "projectDocumentList:%s\n\n\n",
		 project.id,
		 project.label,
		 project.description,
		 projectStartDate,
		 projectFinishDate,
		 project.projectLength,
		 project.state,
	 	 projectDiscussion,
		 adminID,
		 projectGroupMembers,
		 projectTaskList,
		 projectDocumentList);

	  projectBtn = gtk_button_new();
	  gtk_widget_set_name(projectBtn, "projectBtn");

	  projectNameLbl = gtk_label_new(project.label);

	  gtk_container_add(GTK_CONTAINER (projectBtn), projectNameLbl);
	  gtk_widget_set_halign (GTK_WIDGET(projectNameLbl), GTK_ALIGN_START);

          g_signal_connect (projectBtn, "clicked", G_CALLBACK (goToProjectDashboard), NULL);

	  gtk_box_pack_start(GTK_BOX(vbox), projectBtn, FALSE, FALSE, 1);
               
	  gtk_widget_show (projectBtn);

        }

      }
      else if(strcmp(user.role, "EM") == 0) {

        //printf("Connected user is an employee, his collaborations:\n\n");

        int i = 0;
        int j = 0;
        int k = 0;
        char c[5];
        int membersID[25] = {};

        while(i < strlen(projectGroupMembers)) {

          if(projectGroupMembers[i] != ',') {
            c[k] = projectGroupMembers[i];
            k = k+1;
            i = i+1;
          }
          else {
            c[k] = '\0';
            membersID[j] = atoi(c);
            memset(c, 0, strlen(c));
            i = i+1;
            j = j+1;
            k = 0;
          }

        }


        for(i = 0 ; i < 25 ; i++) {

	  if(user.id == membersID[i]) {

	    printf("projectID:%d\n"
		   "projectName:%s\n"
		   "projectDescription:%s\n"
		   "projectStartDate:%s\n"
		   "projectFinishDate:%s\n"
		   "projectLength:%d\n"
		   "projectState:%s\n"
		   "projectDiscussion:%s\n"
		   "projectAdmin:%d\n"
		   "projectGroupMembers:%s\n"
		   "projectTaskList:%s\n"
		   "projectDocumentList:%s\n\n\n",
		   project.id,
		   project.label,
		   project.description,
		   projectStartDate,
		   projectFinishDate,
		   project.projectLength,
		   project.state,
	 	   projectDiscussion,
		   adminID,
		   projectGroupMembers,
		   projectTaskList,
		   projectDocumentList);

	    projectBtn = gtk_button_new();
	    gtk_widget_set_name(projectBtn, "projectBtn");

	    projectNameLbl = gtk_label_new(project.label);

	    gtk_container_add(GTK_CONTAINER (projectBtn), projectNameLbl);
	    gtk_widget_set_halign (GTK_WIDGET(projectNameLbl), GTK_ALIGN_START);

            g_signal_connect (projectBtn, "clicked", G_CALLBACK (goToProjectDashboard), NULL);

	    gtk_box_pack_start(GTK_BOX(vbox), projectBtn, FALSE, FALSE, 1);
               
	    gtk_widget_show (projectBtn);

          }

        }

      printf("\n");

      }

    }

  }
  else
  {
    printf("Error while opening projects file.\n");
  }

  //fclose(projectsf);
  
  /* end: get the users projects */


  gtk_fixed_put (GTK_FIXED (fixed), dashboardLbl, 30, 18);
  gtk_fixed_put (GTK_FIXED (fixed), vbox, 40, 100);

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
