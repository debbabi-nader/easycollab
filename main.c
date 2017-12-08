#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "./struct.h"
#include "./signup/signup.h"
#include "./project-dashboard/project-dashboard.h"
#include "./user-dashboard/user-dashboard.h"
#include "./login/login.h"
#include "./addproject/addproject.h"


//int i = 1;

int main (int argc, char **argv)
{

  gtk_init (&argc, &argv);
  //showProjectDashboardWindow(NULL, NULL);
  //showUserDashboardWindow(NULL, &i);
  //showSignupWindow(NULL, NULL);
  showLoginWindow(NULL, NULL);
  //showAddProjectWindow(NULL, NULL);
  gtk_main ();
  return 0;

}
