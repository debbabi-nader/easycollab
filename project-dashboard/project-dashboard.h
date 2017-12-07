GtkWidget *projectDashboardWindow;
GtkWidget *previousWindow;
GtkWidget *fixed;

GtkWidget *dashboardLbl;

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

ProjectDashboardParam *initialData;


static void showProjectDashboardWindow (GtkWidget *widget, gpointer data)
{

	initialData = (ProjectDashboardParam *)data;
  printf("Connected user ID: %d\n", initialData->connectedUserID);
  printf("Selected project name: %s\n", initialData->selectedProjectName);

  projectDashboardWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title (GTK_WINDOW (projectDashboardWindow), "EasyCollab - Project Dashboard");
  gtk_window_set_default_size (GTK_WINDOW (projectDashboardWindow), 1000, 520);
  gtk_window_set_resizable (GTK_WINDOW (projectDashboardWindow), FALSE);
  gtk_window_set_position(GTK_WINDOW(projectDashboardWindow), GTK_WIN_POS_CENTER);
  gtk_widget_set_name(projectDashboardWindow, "projectDashboardWindow");

  fixed = gtk_fixed_new ();
  gtk_widget_set_size_request (fixed, 1000, 520);
  gtk_widget_set_name(fixed, "fixed");

  dashboardLbl = gtk_label_new(initialData->selectedProjectName);
  gtk_widget_set_name(dashboardLbl, "dashboardLbl");


	/* start: get connected user */

  usersf = fopen("./files/users.txt", "r");
  
  if(usersf != NULL) {

    while(fscanf(usersf, "%d %s %s %s %s %s %s %d", &user.id, user.name, user.firstName, user.username, user.password, user.email, user.role, &user.connected) == 8) {
      
      if(user.id == initialData->connectedUserID) {

        //printf("%s\n", user.name);
				//printf("%d - %d\n", user.id, initialData->connectedUserID);
        break;

      }
 
    }

  }
  else {
    printf("Error while opening users file.\n");
  }

  //fclose(usersf);

  printf("Connected user name: %s\n", user.name);

	/* end: get connected user */


	/* start: get selected project */

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
								 projectDocumentList) == 12)
		{

			if(strcmp(project.label , initialData->selectedProjectName) == 0) {

				break;

			}

    }

  }
  else
  {
    printf("Error while opening projects file.\n");
  }

	printf("Selected project details: \n\n");
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

  //fclose(projectsf);

	/* end: get selected project */


  gtk_fixed_put (GTK_FIXED (fixed), dashboardLbl, 30, 18);

  gtk_container_add(GTK_CONTAINER (projectDashboardWindow), fixed);

  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
 
  GError *error = 0;
  gtk_css_provider_load_from_file(provider, g_file_new_for_path("./project-dashboard/project-dashboard-style.css"), &error);
  
  gtk_widget_show_all (projectDashboardWindow);

  
  if(widget != NULL)
  {
    previousWindow = gtk_widget_get_toplevel (widget);

    if (gtk_widget_is_toplevel (previousWindow))
    {
      gtk_widget_destroy (previousWindow);
    }
  }

}
