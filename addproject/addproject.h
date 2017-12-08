GtkWidget *addProjectWindow;
GtkWidget *previousWindow;
GtkWidget *fixed;
GtkWidget *vbox;
GtkWidget *hbox,*hboxd,*hboxf;


GtkWidget *namelbl;
GtkWidget *descriptionlbl;
GtkWidget *duelbl,*endlbl;
GtkWidget *addprojectLbl;


GtkWidget *nameput,*membre,*add;
GtkWidget *descriptionput,*memberlbl;
GtkWidget *dueput1,*endput1;
GtkWidget *dueput2,*endput2;
GtkWidget *dueput3,*endput3;
GtkWidget *duelbl1,*endlbl1;
GtkWidget *duelbl2,*endlbl2;
GtkWidget *test,*createproj;
GtkWidget *errorLbl,*errorendLbl,*errordueLbl,*errornameLbl;

GtkCssProvider *provider;
GdkDisplay *display;
GdkScreen *screen;
int n=0;
char tab[50][50];
FILE *usersf,*projectsf;
User user;
char err[50];
char errname[50];
char errdue[50];
char errend[50];
char esm[50];
char descrip[500];
char due[10];
char end[10];

void showAddProjectWindow (GtkWidget *widget, gpointer data);

static void addMember (GtkWidget *widget, gpointer data)
{
	usersf = fopen("./files/users.txt", "r");
	
	if(usersf != NULL) {
		int test=0;

    while((fscanf(usersf, "%d %s %s %s %s %s %s %d", &user.id, user.name, user.firstName, user.username, user.password, user.email, user.role, &user.connected) == 8)&&(test==0))
     {
		 if(strcmp(user.username,gtk_entry_get_text (GTK_ENTRY (membre))) == 0)
		 {
			 test=1;
			 n++;
		 }
	 }
	 if(test==1)
	 {
		 strcpy(tab[n-1],gtk_entry_get_text (GTK_ENTRY (membre)));
		 printf("%s",tab[n-1]);
		 strcpy(err,"");
	     gtk_entry_set_text (GTK_ENTRY (membre), ""); 
	 }
	 else
	 {
		 strcpy(err,"* wrong member!");
		 
	     gtk_entry_set_text (GTK_ENTRY (membre), "");
	 }
	 
	 strcpy(esm,gtk_entry_get_text (GTK_ENTRY (nameput)));
	 strcpy(descrip,gtk_entry_get_text (GTK_ENTRY (descriptionput)));
	 strcpy(due,gtk_entry_get_text (GTK_ENTRY (dueput1)));
	 strcpy(end,gtk_entry_get_text (GTK_ENTRY (endput1)));
	 
	 showAddProjectWindow(NULL,NULL);
     gtk_widget_destroy (gtk_widget_get_toplevel (widget));
	
	
	
}
else
{
	printf("Error while opening the file.\n");
}

}

int verifdate(const char *dat)
{
	int i;
	for(i=0;i<=1;i++)
	{
		if ((dat[i]<48) || (dat[i]>57))
		{
			return 0;
		}
	}
	for(i=3;i<=4;i++)
	{
		if ((dat[i]<48) || (dat[i]>57))
		{
			return 0;
		}
	}
	for(i=6;i<=9;i++)
	{
		if ((dat[i]<48) || (dat[i]>57))
		{
			return 0;
		}
	}
	if((dat[2]!=47)||(dat[5]!=47))
	{
		return 0;
	}
	char ji[2];
	ji[0]=dat[0];
	ji[1]=dat[1];
	char mi[2];
	mi[0]=dat[3];
	mi[1]=dat[4];
	char ai[4];
	ai[0]=dat[6];
	ai[1]=dat[7];
	ai[2]=dat[8];
	ai[3]=dat[9];
	int j=atoi(ji);
	int m=atoi(mi);
	int a=atoi(ai);
	if((j==0)||(m==0)||(a==0)||(j>31)||(m>12)||(a<2017))
	{
		return 0;
	}
	return 1;
	
}



static void createProject (GtkWidget *widget, gpointer data)
{
	int erreur=0;
	projectsf = fopen("./files/projects.txt", "a+");
	Project project;
	char projectStartDate[20];
	char projectFinishDate[20];
	char projectDiscussion[300];
	char projectGroupMembers[50];
	char projectTaskList[50];
	char projectDocumentList[50];
	int adminID;
	int dernier;
	int i;
	
	
	if(projectsf!= NULL)	
	{
		int test=0;
		while((fscanf(projectsf,
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
		 projectDocumentList) == 12)&&(test==0)) 
		 {
			 if(strcmp(project.label,gtk_entry_get_text (GTK_ENTRY (nameput)))==0)
			 {
				 test=1;
			 }
		 }
		 
		 if(test==1)
		 {
			 strcpy(errname,"create another name plz");
			 erreur++;
		 }
		 else
		 {
			 strcpy(errname," ");
		 }
	
	
	
	if(verifdate(gtk_entry_get_text (GTK_ENTRY (dueput1)))==0)
	{
		strcpy(errdue,"you must respect the form JJ/MM/AAAA ");
		erreur++;
		
	}
	else
	{
		strcpy(errdue," ");
	}
	if(verifdate(gtk_entry_get_text (GTK_ENTRY (endput1)))==0)
	{
		strcpy(errend,"you must respect the form JJ/MM/AAAA ");
		erreur++;
	}
	else
	{
		strcpy(errend," ");
	}
	if(erreur>0)
	{
		showAddProjectWindow(NULL,NULL);
		gtk_widget_destroy (gtk_widget_get_toplevel (widget));
	}
	else
	{
		fprintf(projectsf,"chaine de caracter:%s","firaz");
		/*dernier=project.id;
		fprintf(projectsf,"projectID:%d\nprojectName:%s\nprojectDescription:%s\nprojectStartDate:%s\n"
		"projectFinishDate:%s\nprojectLength:%d\nprojectState:%s\nprojectDiscussion:%s\nprojectAdmin:%d\n"
		"projectGroupMembers:",dernier+1,gtk_entry_get_text (GTK_ENTRY (nameput)),gtk_entry_get_text (GTK_ENTRY (descriptionput)),gtk_entry_get_text (GTK_ENTRY (dueput1)),gtk_entry_get_text (GTK_ENTRY (endput1)),0,"IN PROGRESS","",1);
		for(i=0;i<n;i++)
		{
			fprintf(projectsf,"%d,",tab[i]);
		}
		fprintf(projectsf,"\nprojectTaskList:%s\nprojectDocumentList:%s\n$","","");*/
		showUserDashboardWindow(NULL, NULL);
		gtk_widget_destroy (gtk_widget_get_toplevel (widget));
	}
	
	}
	else
	{
		printf("Error while opening the file.\n");
	}
	
	
	
	
	
	
	
}





 void showAddProjectWindow (GtkWidget *widget, gpointer data)
{
  
  addProjectWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title (GTK_WINDOW (addProjectWindow), "EasyCollab - Add Project");
  gtk_window_set_default_size (GTK_WINDOW (addProjectWindow), 800, 520);
  gtk_window_set_resizable (GTK_WINDOW (addProjectWindow), FALSE);
  gtk_window_set_position(GTK_WINDOW(addProjectWindow), GTK_WIN_POS_CENTER);
  gtk_widget_set_name(addProjectWindow, "addProjectWindow");

  addprojectLbl = gtk_label_new("Add Project");
  gtk_widget_set_name(addprojectLbl, "addprojectLbl");
  
  
  hbox = gtk_box_new(FALSE, 5);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(hbox), GTK_ORIENTATION_HORIZONTAL);
  gtk_box_set_homogeneous (GTK_BOX (hbox), FALSE);
  gtk_widget_set_size_request (hbox, 1, 1);
  gtk_widget_set_name(hbox, "hbox");
  
  errorLbl=gtk_label_new(err);
  gtk_widget_set_name(errorLbl, "errorLbl");
  
  errornameLbl=gtk_label_new(errname);
  gtk_widget_set_name(errornameLbl, "errornameLbl");
  
  errordueLbl=gtk_label_new(errdue);
  gtk_widget_set_name(errordueLbl, "errordueLbl");
  
  errorendLbl=gtk_label_new(errend);
  gtk_widget_set_name(errorendLbl, "errorendLbl");
  
  namelbl = gtk_label_new("Project Name");
  gtk_widget_set_name(namelbl, "namelbl");
  
  descriptionlbl = gtk_label_new("Project Description");
  gtk_widget_set_name(descriptionlbl, "descriptionlbl");
  
  duelbl = gtk_label_new("Due Date");
  gtk_widget_set_name(duelbl, "duelbl");
  
  
  nameput = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(nameput) , "Project Name");
  gtk_entry_set_text(GTK_ENTRY(nameput),esm);
  gtk_widget_set_size_request (nameput, 1, 5);
  gtk_widget_queue_resize (nameput);
  gtk_widget_set_name(nameput, "nameput");
  
  descriptionput = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(descriptionput) , "Project Description");
  gtk_entry_set_text(GTK_ENTRY(descriptionput),descrip);
  gtk_widget_set_size_request (descriptionput, 5, 5);
  gtk_widget_set_name(descriptionput, "descriptionput");
  
  
  dueput1 = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(dueput1) , "JJ/MM/AAA");
  gtk_entry_set_text(GTK_ENTRY(dueput1),due);
  gtk_entry_set_max_length (GTK_ENTRY(dueput1),10);
  gtk_widget_set_name(dueput1, "dueput1");
  
  
  endlbl= gtk_label_new("End Date");
  gtk_widget_set_name(endlbl, "endlbl");
  
  hboxf = gtk_box_new(FALSE, 5);
  gtk_orientable_set_orientation(GTK_ORIENTABLE(hboxf), GTK_ORIENTATION_HORIZONTAL);
  gtk_box_set_homogeneous (GTK_BOX (hboxf), FALSE);
  gtk_widget_set_name(hboxf, "hboxf");
  
  endput1 = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(endput1) , "JJ/MM/AAAA");
  gtk_entry_set_text(GTK_ENTRY(endput1),end);
  gtk_widget_set_size_request (endput1, 1, 5);
  gtk_entry_set_max_length (GTK_ENTRY(endput1),10);
  gtk_widget_set_name(endput1, "dueput1");
  
  
  
  
  
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
  g_signal_connect (add, "clicked", G_CALLBACK (addMember), NULL);
  gtk_box_pack_start(GTK_BOX(hboxd), membre, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hboxd), add, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(hboxd), errorLbl, FALSE, FALSE, 0);
  
  createproj = gtk_button_new_with_label ("Create Project");
  gtk_widget_set_name(createproj, "createproj");
  g_signal_connect (createproj, "clicked", G_CALLBACK (createProject), NULL);
  
  
  fixed = gtk_fixed_new ();
  gtk_widget_set_size_request (fixed, 800, 520);
  gtk_widget_set_name(fixed, "fixed");
  gtk_fixed_put (GTK_FIXED (fixed), addprojectLbl, 30, 18);
  gtk_fixed_put (GTK_FIXED (fixed), vbox, 450, 80); 
  gtk_fixed_put (GTK_FIXED (fixed), namelbl, 40, 100);
  gtk_fixed_put (GTK_FIXED (fixed), nameput, 40, 130);
  gtk_fixed_put (GTK_FIXED (fixed), errornameLbl, 60, 180);
  gtk_fixed_put (GTK_FIXED (fixed), descriptionlbl, 40, 200);
  gtk_fixed_put (GTK_FIXED (fixed), descriptionput, 40, 230); 
  gtk_fixed_put (GTK_FIXED (fixed), duelbl, 40, 300); 
  gtk_fixed_put (GTK_FIXED (fixed), dueput1, 40, 330);
  gtk_fixed_put (GTK_FIXED (fixed), errordueLbl, 60, 380);
  gtk_fixed_put (GTK_FIXED (fixed), endlbl, 40, 400); 
  gtk_fixed_put (GTK_FIXED (fixed), endput1, 40, 430);
  gtk_fixed_put (GTK_FIXED (fixed), errorendLbl, 60, 480);
  gtk_fixed_put (GTK_FIXED (fixed), memberlbl, 350, 100); 
  gtk_fixed_put (GTK_FIXED (fixed), createproj, 630, 450);
  
  
  int i;
  int j=-30;
  for(i=1;i<=n;i++)
  {
	  j+=30;
    test = gtk_label_new(tab[i-1]);
  gtk_widget_set_name(test, "nameput");
  gtk_fixed_put (GTK_FIXED (fixed), test, 350, 130+j);
  }
  gtk_fixed_put (GTK_FIXED (fixed), hboxd, 350, 130+j+30);
  
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
