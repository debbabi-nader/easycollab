typedef struct User User;
typedef struct Users Users;
typedef struct GroupMember GroupMember;

typedef struct Project Project;

typedef struct Task Task;
typedef struct TaskList TaskList;

typedef struct Document Document;
typedef struct DocumentList DocumentList;

typedef struct Discussion Discussion;
typedef struct Message Message;

typedef struct Date Date;

typedef struct ProjectDashboardParam ProjectDashboardParam;


struct Date
{
	int jj;
	int mm;
	int aa;
	int hh;
	int mn;
};

struct User
{
	int id;
	char name[50];
	char firstName[50];
	char username[50];
	char password[50];
	char email[50];
	char role[50];
	int connected;
};

struct Users
{
	User *user;
	Users *nextUser;
};

struct GroupMember
{
	User *member;
	GroupMember *nextMember;
};

struct Project
{
	int id;
	char label[100];
	char description[1000];
	Date start;
	Date finish;
	int projectLength;
	char state[20];
	Discussion *discussion;
	User *admin;
	GroupMember *members;
	TaskList *tasks;
	DocumentList *documents;
};

struct Message
{
	int id;
	char text[200];
	User *sender;
	Date sentDate;
};

struct Discussion
{
	Message message;
	Discussion *next;
};

struct Task
{
	int id;
	char label[50];
	char description[1000];
	Date start;
	Date finish;
	int taskLength;
	char state[20];
	User *assignedTo;
};

struct TaskList
{
	Task task;
	TaskList *next;
};

struct Document
{
	int id;
	char label[50];
	char url[100];
	Date addedDate;
	User *addedBy;
};

struct DocumentList
{
	Document document;
	DocumentList *next;
};

struct ProjectDashboardParam
{
	int connectedUserID;
	char selectedProjectName[100];
};
