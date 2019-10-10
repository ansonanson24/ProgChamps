/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Names:
 * Bilal Ali
 * Anson Kwok
 * Danielle Alota -12954121
 * Zhongzhuo Wu
 * Yuekai Sun
 *
 * Student ID:
 * 13205657
 *
 *
 *
 *
 *
 * Date of submission:
*******************************************************************************/

/*******************************************************************************
 * List header files
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * List preprocessing directives.
*******************************************************************************/
#define MAX_NAME_LEN 10
#define MAX_LEN 99
#define MAX_WISHES 5
#define MAX_NUM 3

/*******************************************************************************
 * List structs.
*******************************************************************************/

struct wishlist {
	char name[99];
	int priority;
}; typedef struct wishlist wishlist_t;

struct person
{
	char name[MAX_NAME_LEN + 1];
	char password[MAX_LEN + 1]; /* Gonna see if we can use other
					libraries besides those for limits.h */
	wishlist_t list; /* will be written to text file */
	int index; /* santa*/
};
typedef struct person person_t;

/*******************************************************************************
 * Function prototypes.
*******************************************************************************/

void selectionMain(person_t users[MAX_NUM], int* size);
void adminLogin(person_t users[MAX_NUM], int* size);
void selectionAdmin(person_t users[MAX_NUM], int* size);
void userLogin(person_t users[MAX_NUM], int* size);
void selectionUser(person_t users[MAX_NUM], int* size, person_t* user_p);
int userRegister(person_t users[MAX_NUM], int* size);
int nameTaken(person_t users[MAX_NUM], char name[], int* size);
int removeMember(person_t users[MAX_NUM], int* size);
void assignMembers();
int viewWishes(person_t users[MAX_NUM], int* size);
void passEncrypt();
void sortByAlphabet();
int printList(person_t users[MAX_NUM], int* size);
void addItem();
void removeItem();
int itemExists();
void printMain();
void printUser();
void printAdmin();
void changePassword(person_t users[MAX_NUM], person_t* user, int* size);
int checkPass(person_t* user, char password[MAX_LEN]);
int passMatch(char pass1[MAX_LEN], char pass2[MAX_LEN]);
void printEditMenu();

/*******************************************************************************
 * Main
*******************************************************************************/
int main(int argc, char* argv[]) {
	int size = 0;
	int* size_p = &size;
	person_t users[MAX_NUM];

	if (argc == 1)
	{
		selectionMain(users, size_p);
	}
	else if (!strcmp(argv[1], "login"))
	{
		userLogin(users, size_p); /* size undefined*/
	}
	else if (!strcmp(argv[1], "register"))
	{
		userRegister(users, size_p);
	}
	else if (!strcmp(argv[1], "admin"))
	{
		adminLogin(users, size_p);
	}


	return 0;
}

/*
Contributors: Danielle Alota
*/
void selectionMain(person_t users[MAX_NUM], int* size) {
	char c;
	while (1) {
		printMain();
		scanf(" %c", &c); /* This is so it takes inputs that aren't numbers*/
		switch (c)
		{
		case '1':
			adminLogin(users, size);
			break;

		case '2':
			userLogin(users, size);
			break;

		case '3':
			if (*size == MAX_NUM) {
				puts("Max users reached. Returning to main menu.");
			}
			else {
				*size = userRegister(users, size);
				*size = *size + 1;
				puts("User has been registered successfully! Returning to main menu.");
			}
			break;
		case '4':
			exit(0);
			break;

		default:
			printf("Invalid choice!\n");
			break;
		}
	}

}

/*******************************************************************************
*	This function adds a new member inputted by the user to the member list.
Contributors:  Danielle Alota
*******************************************************************************/
int userRegister(person_t users[MAX_NUM], int* size) {
	char name[MAX_NAME_LEN + 1];
	/* char password[MAX_PASS_LEN + 1];  for future encryption*/
	int valid;

	printf("Enter your name (without spaces): ");
	scanf("%s", name);
	valid = nameTaken(users, name, size);

	while (valid == 1) {
		printf("User already exists! Please try again.\n");
		printf("Enter your name (without spaces): ");
		scanf("%s", name);
		valid = nameTaken(users, name, size);
	}

	if (valid == 0) {
		strcpy(users[*size].name, name);
	}

	printf("Enter your password: ");
	scanf("%s", users[*size].password);

	return *size;
}

/*
This function checks if the inputted name already exists in the array of members
Contributors: Danielle Alota
*/
int nameTaken(person_t users[MAX_NUM], char name[], int* size) {
	int i;
	for (i = 0; i < *size + 1; i++) {
		if (strcmp(users[i].name, name) == 0) {
			return 1;
		}
	}
	return 0;
}

/*
Contributor: Bilal
*/
void adminLogin(person_t users[MAX_NUM], int* size) {
	char username[MAX_NAME_LEN];
	char password[MAX_LEN];

	printf("Enter username>\n");
	scanf("%s", username);

	printf("Enter password>\n");
	scanf("%s", password);

	if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
		printf("Login success\n");
		printf("\n(¯`·._.·(¯`·._.· Ho Ho Ho, Welcome Admin ·._.·´¯)·._.·´¯)\n");
		selectionAdmin(users, size);
	}
	else {
		printf("Login failed\n");
		return;
	}
}


/*
Contributor: Danielle Alota
*/
void selectionAdmin(person_t users[MAX_NUM], int* size) {
	char c;
	while (1) {
		printAdmin();
		scanf(" %c", &c);
		switch (c) {
		case '1':
			printf("displaying...\n");
			break;
		case '2':
			if (removeMember(users, size) != -1) {
				printf("Member removed successfully. Returning to admin menu.\n");
			}
			else {
				printf("This member does not exist. Returning to admin menu.\n");
			}
			break;
		case '3':
			printf("assigning...\n");
			break;
		case '4':
			printf("Logged out\n");
			selectionMain(users, size);
			break;
		case '5':
			exit(0);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	}
}

/*
Contributors: Danielle Alota
Anson Kwok
*/
void userLogin(person_t users[MAX_NUM], int* size) {
	char username[MAX_NAME_LEN];
	char password[MAX_LEN];
	int i, valid = 0;
	person_t* foundUser_p = NULL;


	printf("Enter username>\n");
	scanf("%s", username);
	/* need to catch errors for over the length limit*/
	printf("Enter password>\n");
	scanf("%s", password);

	/* change into function*/
	for (i = 0; i < *size + 1; i++) {
		if (strcmp(username, users[i].name) == 0 && strcmp(password, users[i].password) == 0) {
			valid = 1;
			foundUser_p = &users[i];
			break;
		}
	}

	/* pass logged in user */
	if (valid) {
		printf("Successful login! Redirecting to user menu.\n"); /* Maybe add a hello <name>?*/
		selectionUser(users, size, foundUser_p);
	}
	else {
		printf("Login failed. Returning to main menu.\n"); /* to be changed to while*/
		selectionMain(users, size);
	}
}

/*
Contributor: Danielle Alota
*/
void selectionUser(person_t users[MAX_NUM], int* size, person_t* user) {
	char choice; /* For the purpose of testing, let's stick with scanning int */
	/* Then change to char to deal with inputs not of same data type */
	char editCh;

	while (1) {
		printUser();
		scanf(" %c", &choice);
		switch (choice)
		{
		case '1':
			editCh = ' ';
			printEditMenu();
			scanf(" %c", &editCh);

			while (editCh != '1' && editCh != '2') {
				printf("%c\n", editCh);
				printf("Invalid choice. Please try again or enter * to return to user menu.\n");
				printEditMenu();
				scanf(" %c", &editCh);
				if (editCh == '*') {
					break;
				}
			}

			if (editCh == '1') {
				printf("add");
				addItem();
			}
			else if (editCh == '2') {
				printf("remove");
				removeItem();
			}
			break;

		case '2':
			changePassword(users, user, size);
			break;

		case '3': /* view santa's wishlist*/
			printf("nothing assigned yet...\n");
			break;

		case '4':
			printf("Successfully logged out. Returning to main menu.\n");
			selectionMain(users, size);
			break;

		case '5':
			exit(0);
			break;

		default:
			printf("Invalid choice\n");
			break;
		}
	}

}

void addItem() {

}

void removeItem() {

}

int itemExists() {
	return 0;
}

/*
Contributor: Danielle Alota
*/
void changePassword(person_t users[MAX_NUM], person_t* user, int* size) {
	char password[MAX_LEN];
	char newPass1[MAX_LEN];
	char newPass2[MAX_LEN];
	int validPass, validNew;

	printf("Please enter your current password: ");
	scanf("%s", password);
	if (strcmp(password, "*") == 0) {
		return;
	}
	validPass = checkPass(user, password);

	while (validPass == 1) {
		printf("Incorrect password. Try again or enter * to go back to menu.\n");
		printf("Please enter your current password: ");
		scanf("%s", password);
		validPass = checkPass(user, password);
		if (strcmp(password, "*") == 0) {
			return;
		}
	} /* checks for correct password*/

	printf("Please enter a new password: ");
	scanf("%s", newPass1); /* add: check for max length (fgets/sscanf isnt working for me)*/
	printf("Confirm password: "); /* have not checked if inputted nothing*/
	scanf("%s", newPass2);
	validNew = passMatch(newPass1, newPass2);

	while (validNew == 1) {
		printf("Passwords do not match. Try again or enter * to go back to menu\n.");
		printf("Please enter a new password: ");
		scanf("%s", newPass1); /* add: check for max length (fgets/sscanf isnt working for me)*/
		if (strcmp(newPass1, "*") == 0) {
			return; 
		}
		printf("Confirm password: ");
		scanf("%s", newPass2);
		if (strcmp(newPass2, "*") == 0) {
			break;
		}
		validNew = passMatch(newPass1, newPass2);
	}

	if (validNew == 0) {
		strcpy(user->password, newPass2);
		printf("%s", user->password);
		printf("Password changed successfully! Redirecting to user menu.\n");
		selectionUser(users, size, user);
	}
}

/*
Contributor: Danielle Alota
*/
int passMatch(char pass1[MAX_LEN], char pass2[MAX_LEN]) {
	if (strcmp(pass1, pass2) == 0) {
		return 0;
	}
	else {
		return 1;
	}

}

/*
Contributor: Danielle Alota
*/
int checkPass(person_t* user, char password[MAX_LEN]) {
	if (strcmp(user->password, password) == 0) {
		return 0;
	}
	else {
		return 1;
	}

}

/*******************************************************************************
*	This function removes an existing member inputted by the user from the
*	member list.

Contributors:
Jack
Danielle
*******************************************************************************/
int removeMember(person_t users[MAX_NUM], int* size) {
	int i;
	char name[MAX_NAME_LEN];
	printf("Removing member. Please enter the name of the member you wish to delete: ");
	scanf(" %s", name);

	/*if exist delete*/
	for (i = 0; i < *size + 1; i++) {
		if (strcmp(name, users[i].name) == 0) { /* further testing required*/
			strcpy(users[i].name, users[*size - 1].name);
			strcpy(users[i].password, users[*size - 1].password);
			users[i].index = users[*size - 1].index;
			strcpy(users[i].list.name, users[*size - 1].list.name);
			users[i].list.priority = users[*size - 1].list.priority;
			*size = *size - 1;
			return *size;
		}
	}
	/*not exist return -1*/
	return -1;
}

/*******************************************************************************
*	This function assigns a random member's wishlist to another member.
*******************************************************************************/
void assignMembers() {
	printf("assign\n");
}

/*******************************************************************************
*	This function encrypts a given password.
*******************************************************************************/
void passEncrypt() {
	printf("encrypt\n");
}

/*******************************************************************************
*	This function handles the displaying of a member's wishlist.
*******************************************************************************/
/*contributors: Jack
Danielle */
int viewWishes(person_t users[MAX_NUM], int* size) {
	int i;
	char username[MAX_NAME_LEN];
	printf("\nview\n");
	/*enter username then show the wishlist*/
	printf("Please enter the username you want to check\n");
	scanf("%s", username);
	for (i = 0; i < *size; i++) {
		if (strcmp(username, users[i].name) == 0) {
			printf("The following shows the wish list of %s\n%s\n", username, users[i].list.name);
			return 0;
		}
	}
	/*username not exist*/
	return -1;
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
/*author: Jack*/
int printList(person_t users[MAX_NUM], int* size) {
	printf("\nprint\n");
	int i = 0;
	printf("all of the wishlist is below\n");
	/*show all wishlist*/
	for (i = 0; i < MAX_NUM; i++) {
		if (strcmp(users[i].name, " ") == 1) {
			printf("%s\n", users[i].list.name);
		}
	}
	return 0;
}

void printMain() {
	printf("\n"
		"1. Login as Admin\n"
		"2. Login as User\n"
		"3. Register\n"
		"4. Exit the program\n"
		"Enter choice (number between 1-4)>\n");
}

void printUser() {
	printf("\n"
		"1. Edit my wishlist\n"
		"2. Change my password\n"
		"3. View my Secret Santa\n"
		"4. Log out\n"
		"5. Exit the program\n"
		"Enter choice (number between 1-4)>\n");
}

void printAdmin() {
	printf("\n"
		"1. Display all users' info \n"
		"2. Remove a user\n"
		"3. Assign users\n"
		"4. Log out\n"
		"5. Exit the program\n"
		"Enter choice (number between 1-4)>\n");
}

void printEditMenu() {
	printf("Editing wishlist.\n"
		"1. Add an item.\n"
		"2. Remove an item.\n"
		"3. Enter choice: ");
}
