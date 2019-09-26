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
};
typedef struct person person_t;

/*******************************************************************************
 * Function prototypes.
*******************************************************************************/
void printMain();
void selectionMain(person_t users[MAX_NUM][MAX_NUM]);
void adminLogin();
void adminMenu();
void printAdmin();
void selectionAdmin();
void userLogin();
void userMenu();
void printUser();
void selectionUser();
int userRegister(person_t users[MAX_NUM][MAX_NUM], int size);
int userExists(person_t users[MAX_NUM][MAX_NUM], char name[], int size);
void removeMember();
void assignMembers();
void viewWishes();
void passEncrypt();
void sortByAlphabet();
void printList();
void editWishlist(person_t person);
int itemExists();

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void) {

	person_t users[MAX_NUM][MAX_NUM];
	/*subject to change, 2d array was discussed as a possibility*/

	while (1) {
		selectionMain(users);
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

void selectionMain(person_t users[MAX_NUM][MAX_NUM]) {
	printMain();
	char c;
	int size = 0;
	scanf(" %c", &c); /* This is so it takes inputs that aren't numbers*/

	switch (c)
	{
	case '1':
		adminLogin();
		break;

	case '2':
		userLogin();
		break;

	case '3':
		if (size == MAX_NUM) {
			puts("Max users reached. Returning to main menu.");
		}
		else {
			size = userRegister(users, size);
			size++;
		}
		break;

	case '4':
		exit(0);
		break;

	default:
		printf("Invalid choice\n");
		break;
	}
}

void adminLogin() {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];

	printf("Enter username>\n");
	scanf("%s", username);

	printf("Enter password>\n");
	scanf("%s", password);

	if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
		printf("Login success\n");
		adminMenu();
	}
	else {
		printf("Login failed\n");
		return;
	}
}

void adminMenu() {
	while (1) {
		printAdmin();
		selectionAdmin();
	}
}

void printAdmin() {
	printf("\n"
		"1. Display users\n"
		"2. Remove users\n"
		"3. Assign users\n"
		"4. Log out\n"
		"5. Exit the program\n"
		"Enter choice (number between 1-4)>\n");
}

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
		printf("Logged out\n");
		main();
		return;
		break;

	case 5:
		exit(0);
		break;

	default:
		printf("Invalid choice\n");
		break;
	}
}

void userLogin() {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];

	printf("Enter username>\n");
	scanf("%s", username);

	printf("Enter password>\n");
	scanf("%s", password);

	if (strcmp(username, "user") == 0 && strcmp(password, "user") == 0) {
		printf("Login success\n");
		userMenu();
	}
	else {
		printf("Login failed\n");
		return;
	}
}

void userMenu() {
	while (1) {
		printUser();
		selectionUser();
	}
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

void selectionUser() {
	int number; /* For the purpose of testing, let's stick with scanning int */
	scanf("%d", &number); /* Then change to char to deal with inputs not of same data type */

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
		printf("Logged out\n");
		main();
		return;
		break;

	case 5:
		exit(0);
		break;

	default:
		printf("Invalid choice\n");
		break;
	}
}

void editWishlist(person_t person) {


}

/*
Checks if item exists in wishlist
*/
int itemExists() {
	return 1;
}

/*******************************************************************************
*	This function adds a new member inputted by the user to the member list.
Main author: Danielle Alota
Contributors:
*******************************************************************************/
int userRegister(person_t users[MAX_NUM][MAX_NUM], int size) {
	char name[MAX_NAME_LEN + 1];
	char password[MAX_PASS_LEN + 1]; /* for future encryption*/
	int valid;

	printf("Enter your name (without spaces): ");
	scanf("%s", name);
	valid = userExists(users, name, size);

	while (valid == 1) {
		printf("User already exists! Please try again.\n");
		printf("Enter your name (without spaces): ");
		scanf("%s", name);
		valid = userExists(users, name, size);
	}

	if (valid == 0) {
		strcpy(users[size][size].name, name);
	}

	printf("Enter your password: ");
	scanf("%s", users[size][size].password);
	strcpy(users[size][size].password, password);
	puts("User has been registered successfully! Returning to main menu.");
	return size;
}

/*
This function checks if the inputted name already exists in the array of members

Main author: Danielle Alota
*/
int userExists(person_t users[MAX_NUM][MAX_NUM], char name[], int size) {
	int i, j, valid = 0;
	for (i = 0; i < size + 1; i++) {
		for (j = 0; j < size + 1; j++) {
			if (users[i][j].name == name) {
				printf("reached 1");
				valid = 1;
				break;
			}
		}
	}
	return valid;
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
	printf("assign\n");
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


