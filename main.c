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
	int  age;
	char password[MAX_PASS_LEN + 1]; /* Gonna see if we can use other
					libraries besides those for limits.h */
	char wishlist[MAX_WISHES + 1]; /* will be written to text file */
};
typedef struct person person_t;

/*******************************************************************************
 * Function prototypes.
*******************************************************************************/

void selectionMain(person_t users[MAX_NUM][MAX_NUM], int size);
void adminLogin(person_t users[MAX_NUM][MAX_NUM], int size);
void selectionAdmin(person_t users[MAX_NUM][MAX_NUM], int size);
void userLogin(person_t users[MAX_NUM][MAX_NUM], int size);
void selectionUser(person_t users[MAX_NUM][MAX_NUM], int size, person_t user);
int userRegister(person_t users[MAX_NUM][MAX_NUM], int size);
int nameTaken(person_t users[MAX_NUM][MAX_NUM], char name[], int size);
void removeMember();
void assignMembers();
void viewWishes();
void passEncrypt();
void sortByAlphabet();
void printList();
void editWishlist(person_t person);
int itemExists();
void printMain();
void printUser();
void printAdmin();

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void) {
	int size = 0;
	person_t users[MAX_NUM][MAX_NUM];
	/*subject to change, 2d array was discussed as a possibility*/
	selectionMain(users, size);
	return 0;
}

/*
Contributors: Danielle Alota
*/
void selectionMain(person_t users[MAX_NUM][MAX_NUM], int size) {
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
			if (size == MAX_NUM) {
				puts("Max users reached. Returning to main menu.");
			}
			else {
				size = userRegister(users, size);
				size++;
				puts("User has been registered successfully! Returning to main menu.");
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

}

/*******************************************************************************
*	This function adds a new member inputted by the user to the member list.
Contributors:  Danielle Alota
*******************************************************************************/
int userRegister(person_t users[MAX_NUM][MAX_NUM], int size) {
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
		strcpy(users[size][size].name, name);
	}

	printf("Enter your password: ");
	scanf("%s", users[size][size].password);

	return size;
}

/*
This function checks if the inputted name already exists in the array of members

Contributors: Danielle Alota
*/
int nameTaken(person_t users[MAX_NUM][MAX_NUM], char name[], int size) {
	int i, j;
	for (i = 0; i < size + 1; i++) {
		for (j = 0; j < size + 1; j++) {
			if (strcmp(users[i][j].name, name) == 0) {
				return 1;
			}
		}
	}
	return 0;
}

/*
Contributor: Bilal
*/
void adminLogin(person_t users[MAX_NUM][MAX_NUM], int size) {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];

	printf("Enter username>\n");
	scanf("%s", username);

	printf("Enter password>\n");
	scanf("%s", password);

	if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
		printf("Login success\n");
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
void selectionAdmin(person_t users[MAX_NUM][MAX_NUM], int size) {
	char c;
	scanf("%c", &c);
	while (1) {
		printMain();
		switch (c)
		{
		case 1:
			printf("displaying...\n");
			break;
		case 2:
			printf("removing...\n");
			break;
		case 3:
			printf("assigning...\n");
			break;
		case 4:
			printf("Logged out\n");
			selectionMain(users, size);
			break;
		case 5:
			exit(0);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	}
}

/*
Contributor: Danielle Alota
*/
void userLogin(person_t users[MAX_NUM][MAX_NUM], int size) {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];
	int i, j, valid = 0;
	person_t foundUser;

	printf("Enter username>\n");
	scanf("%s", username);

	printf("Enter password>\n");
	scanf("%s", password);

	/* change into function*/
	for (i = 0; i < size + 1; i++) {
		for (j = 0; j < size + 1; j++) {
			if (strcmp(username, users[i][j].name) == 0 && strcmp(password, users[i][j].password) == 0) {
				valid = 1;
				foundUser = users[i][j];
				break;
			}
		}
	}
	

	/* pass logged in user */
	if (valid) {
		printf("Successful login! Redirecting to user menu.\n"); /* Maybe add a hello <name>?*/
		selectionUser(users, size, foundUser);
	} else {
		printf("Login failed. Returning to main menu."); /* to be changed to while*/
		selectionMain(users, size);
	}
}


/*
Contributor: Danielle Alota
*/
void selectionUser(person_t users[MAX_NUM][MAX_NUM], int size, person_t user) {
	int number; /* For the purpose of testing, let's stick with scanning int */
	/* Then change to char to deal with inputs not of same data type */
	int i, j, userX, userY;
	
	for (i = 0; i < size + 1; i++) {
		for (j = 0; j < size + 1; j++) {
			if (strcmp(username, users[i][j].name) == 0 && strcmp(password, users[i][j].password) == 0) {
				userX = i;
				userY = j;
				break;
			}
		}
	}

	while (1) {
		printUser();
		scanf("%d", &number);
		switch (number)
		{
		case 1:
			printf("Editing...\n");
			break;

		case 2:
			printf("changing password...\n");
			changePassword(users, size);
			break;
		case 3:
			printf("nothing assigned yet...\n");
			break;

		case 4:
			printf("Logged out\n");
			selectionMain(users, size);
			break;

		case 5:
			exit(0);
			break;

		default:
			printf("Invalid choice\n");
			break;
		}
	}

}

void changePassword()

void editWishlist(person_t person) {


}

/*
Checks if item exists in wishlist
*/
int itemExists() {
	return 1;
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
		"1. Display users\n"
		"2. Remove users\n"
		"3. Assign users\n"
		"4. Log out\n"
		"5. Exit the program\n"
		"Enter choice (number between 1-4)>\n");
}
