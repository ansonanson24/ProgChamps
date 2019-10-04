/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Names:
 * Bilal Ali
 * Anson Kwok
 * Danielle Alota
 * Zhongzhuo Wu
 * Yuekai Sun
 *
 * Student ID:
 * 13205657
 * 12954121
 *
 *
 * 13001589
 *
 *
 * Date of submission:
*******************************************************************************/

/*******************************************************************************
 * List header files
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * List preprocessing directives.
*******************************************************************************/

#define MAX_NAME_LEN 20
#define MAX_PASS_LEN 99
#define MAX_WISHES 5
#define MAX_NUM 50

/*******************************************************************************
 * List structs.
*******************************************************************************/
struct person
{
	char name[MAX_NAME_LEN + 1];
	int age;
	char password[MAX_PASS_LEN + 1]; /* Gonna see if we can use other
					libraries besides those for limits.h */
	char wishlist[MAX_WISHES + 1]; /* will be written to text file */
	int santa; /* assigned santa */
};
typedef struct person person_t;

/*******************************************************************************
 * Function prototypes.
*******************************************************************************/
void adminLogin();
void adminMenu();
void printAdmin();
void selectionAdmin();
void userLogin(person_t users[], int size);
void userMenu(person_t user);
void printUser();
void selectionUser();
int userRegister();
void addMember();
void removeMember();
void assignMembers();
void viewWishes();
void passEncrypt();
void sortByAlphabet();
void printList();
int checkUser(person_t users[], int size, char username[], char password[]);
void personsDataInit();

person_t persons[MAX_NUM];



/*******************************************************************************
 * Main
*******************************************************************************/
int main(int argc, char* argv[])
{
	personsDataInit();
	int test_result = userRegister();
	printf("test_result = %d", test_result);
	int size = 0;
	/*Change back to zero*/

	if (!strcmp(argv[1], "admin"))
	{
		adminLogin();
	}
	else if (!strcmp(argv[1], "login"))
	{
		userLogin(persons, size); /* size undefined*/
	}
	else if (!strcmp(argv[1], "register"))
	{
		userRegister();
	}


	return 0;
}

/*
Main author: Bilal
*/
void adminLogin() {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];

	printf("Enter username>\n");
	scanf("%s", username);

	printf("Enter password>\n");
	scanf("%s", password);

	if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
		printf("Login success!\n"); /* infinite loop if success*/
		adminMenu();
	}
	else {
		printf("Login failed.\n");
		return;
	}
}

/*
Main author: Bilal
*/
void adminMenu() {
	printf("\n(¯`·._.·(¯`·._.· Ho Ho Ho, Welcome Admin ·._.·´¯)·._.·´¯)\n");
	printAdmin();
	selectionAdmin();
}

void printAdmin() {
	printf("\n"
		"1. Display users\n"
		"2. Remove users\n"
		"3. Assign users\n"
		"4. Exit the program\n"
		"Enter choice (number between 1-4)>\n");
}

/*
Main author: Bilal
*/
void selectionAdmin() {
	int number;
	scanf("%d", &number);

	switch (number)
	{
	case 1:
		printf("displaying...\n");
		return;
		break;

	case 2:
		printf("removing...\n");
		return;
		break;

	case 3:
		printf("assigning...\n");
		return;
		break;

	case 4:
		exit(0);
		break;

	default:
		printf("Invalid choice\n");
		break;
	}
}

/*
Main author: Bilal
*/
void userLogin(person_t users[], int size) {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];
	int userIndex;
	person_t user;

	printf("Enter username>\n");
	scanf("%s", username);

	printf("Enter password>\n");
	scanf("%s", password);

	/* checks array for login, returns index of user if found, returns -1 otherwise. */
	userIndex = checkUser(users, size, username, password);

	if (userIndex != -1) {
		user = users[userIndex];
		printf("Login success!\n");
		userMenu(user);
	}
	else {
		printf("Login failed.\n");
	}
}

int checkUser(person_t users[], int size, char username[], char password[]) {
	int i;

	for (i = 0; i < size; i++) {
		if (strcmp(username, users[i].name) == 0 && strcmp(password, users[i].password) == 0)
			return i;
	}
	return -1;
}
/*
Main author: Bilal
*/
void userMenu(person_t user) {
	printf("\n(¯`·._.·(¯`·._.· Ho Ho Ho, Welcome %s ·._.·´¯)·._.·´¯)\n", user.name);
	while (1) {
		printUser();
		selectionUser();
	}
}

void printUser() {
	printf("\n"
		"1. Edit wishlist\n"
		"2. Change password\n"
		"3. View assigned\n"
		"4. Exit the program\n"
		"Enter choice (number between 1-4)>\n");
}

/*
Main author: Bilal
*/
void selectionUser() {
	int number;
	scanf("%d", &number);

	switch (number)
	{
	case 1:
		printf("Editing...\n");
		return;
		break;

	case 2:
		printf("password cant be changed atm...\n");
		return;
		break;

	case 3:
		printf("nothing assigned yet...\n");
		return;
		break;

	case 4:
		exit(0);
		break;

	default:
		printf("Invalid choice\n");
		break;
	}
}

/*author: Jack*/
int userRegister() {
	int i = 0;
	char username[200];
	
	printf("entner username(less than 20 character)\n");
	/*scanf*/
	scanf("%s", username);
	/*check username*/
	printf("%ld\n", strlen(username));
	/*printf*/
	if (strlen(username) > MAX_NAME_LEN) {
		printf("re-entner username(less than 21 characters)\n");
		return -1; /*username is more than 20 characters*/
	}
	for (i = 0; i < MAX_NUM; i++) {
		if (strcmp(username, persons[i].name) == 0) {
			printf("this username is already exist, please enter another username\n");
			return -2; /*username is already exist*/
		}
	}


	/* password */
	char password1[200];
	char password2[200];
	/* scanf */
	printf("enter password(less than 10 character)\n");
	scanf("%s", password1);
	printf("enter password again\n");
	scanf("%s", password2);
	/* check password */
	if (strlen(password1) > 10 || strlen(password2) > 10) {
		printf("re-entner username(less than 10 characters)\n");
		return -3; /*password is more than 10 characters*/
	}
	if (strcmp(password1, password2) != 0) {
		printf("two passwords are not same, please re-enter\n");
		return -4; /*two passwords are not same*/
	}


	/*find position*/
	for ( i = 0; i < MAX_NUM; i++) {
		if (strcmp(persons[i].name, " ") == 0) {
			strcpy(persons[i].name, username);
			strcpy(persons[i].password, password1);
			return 0;
		}
	}
	/*reach the maximum user number*/
	return -5;

}

/*author: Jack*/
void personsDataInit() {
	int i = 0;
	for ( i = 0; i < MAX_NUM; i++) {
		persons[i].age = 0;
		persons[i].santa = 0;
		strcpy(persons[0].name, " ");
		strcpy(persons[0].password, " ");
		strcpy(persons[0].wishlist, " ");
	}

	strcpy(persons[0].name, "Santa"); 				/*Dummy data*/
	persons[0].age = 7;					 	/*Dummy data*/
	strcpy(persons[0].password, "Rudolph");				/*Dummy data*/
	strcpy(persons[0].wishlist, "High Distinction");
}

/*******************************************************************************
*	This function removes an existing member inputted by the user from the
*	member list.
*******************************************************************************/
void removeMember() {
	printf("remove\n");
}

/*******************************************************************************
*	This function assigns a random member's wishlist to another member.
*******************************************************************************/
void assignMembers() {
	printf("Members assigned\n");
}

/*******************************************************************************
*	This function handles the displaying of a member's wishlist.
*******************************************************************************/
void viewWishes() {
	printf("view\n");
}

/*******************************************************************************
*	This function encrypts a given password.
*******************************************************************************/
void passEncrypt() {
	printf("encrypt\n");
}

/*******************************************************************************
*	This function sorts the member list by their names in alphabetical order.
*******************************************************************************/
void sortByAlphabet() {
	printf("sort\n");
}

/*******************************************************************************
*	This function prints a given wishlist.
*******************************************************************************/
void printList() {
	printf("print\n");
}


