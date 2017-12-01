#include <stdio.h>
#include <string.h>

#include <gtk/gtk.h>
#include <gdk/gdk.h>

#include "./struct.h"
#include "./signup/signup.h"
#include "./user-dashboard/user-dashboard.h"
#include "./login/login.h"


int main (int argc, char **argv)
{

  gtk_init (&argc, &argv);
  //showUserDashboardWindow(NULL, NULL);
  //showSignupWindow(NULL, NULL);
  showLoginWindow(NULL, NULL);
  gtk_main ();
  return 0;

}
