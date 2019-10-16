/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Names:
 * Bilal Ali
 * Yat Ho Kwok
 * Danielle Alota
 * Zhongzhuo Wu
 * Yuekai Sun
 *
 * Student ID:
 * 13205657
 * 12879779
 * 12954121
 * 13023748
 * 13001589
 *
 * Date of submission: 18/10/2019
*******************************************************************************/

/*******************************************************************************
 * List header files
*******************************************************************************/
#define _CRT_SECURE_NO_WARNINGS /* remember to delete!!!*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*******************************************************************************
 * List preprocessing directives.
*******************************************************************************/
#define MAX_NAME_LEN 10
#define MAX_PASS_LEN 20
#define MAX_LEN 99
#define MAX_WISHES 5
#define MAX_NUM 3
#define KEY 3
#define DB_NAME "users"
/* #define DEBUG_MODE 1 */

/*******************************************************************************
 * List structs.
*******************************************************************************/

struct wishlist {
	char name[MAX_LEN];
	int priority;
}; typedef struct wishlist wishlist_t;

struct person
{
	char name[MAX_NAME_LEN + 1];
	char password[MAX_LEN + 1]; /* Gonna see if we can use other
					libraries besides those for limits.h */
	wishlist_t list[MAX_WISHES + 1]; /* will be written to text file */
	int listSize;
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
void passEncrypt(person_t users[MAX_NUM], int* size, char password[MAX_LEN]);
int passDecrypt(person_t users[MAX_NUM], int index, char pass[10]);
int viewWishes(person_t users[MAX_NUM], int* size);
void sortByAlphabet(person_t users[MAX_NUM], int *size);
int printList(person_t users[MAX_NUM], int* size, person_t* user);
int addItem(person_t* user);
void removeItem(person_t* user);
int itemExists(char itemName[MAX_LEN], person_t* user);
void printMain();
void printUser();
void printAdmin();
void changePassword(person_t users[MAX_NUM], person_t* user, int* size);
int checkPass(person_t* user, char password[MAX_LEN]);
int passMatch(char pass1[MAX_LEN], char pass2[MAX_LEN]);
void printEditMenu();
void displayUser(person_t users[], int* size);
char* strCompress(char myStr[]);
void saveUsers (person_t users[], int size);
int loadUsers (person_t users[]);

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
				printf("Max users reached. Returning to main menu.");
			}
			else {
				*size = userRegister(users, size);
				printf("User has been registered successfully! Returning to main menu.");
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
	char compressed[MAX_NAME_LEN + 1];
	char password[MAX_LEN];
	/* char password[MAX_PASS_LEN + 1];  for future encryption*/
	int valid;

	printf("Enter your username (without spaces)> \n");
	scanf("%s", name);


	strcpy(compressed, name);
	strCompress(compressed);
	
	#ifdef DEBUG_MODE
	printf("compressed name: %s\n", compressed);
	#endif
	
	valid = nameTaken(users, name, size);

	while (valid == 1) {
		printf("User already exists! Please try again.\n");
		printf("Enter your username (without spaces)> \n");
		scanf("%s", name);
		valid = nameTaken(users, name, size);
	}

	if (valid == 0) {
		strcpy(users[*size].name, name);
		users[*size].listSize = 0;

		printf("Enter your password: ");
		scanf("%s", password);
    
		passEncrypt(users, size, password);
		*size = *size + 1;
		printf("Register Success! Returning to main menu.\n");
		printf("Username: %s - Password: %s\n", name, users[*size-1].password);
		selectionMain(users, size);
	}
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

	printf("Enter your username> \n");
	scanf("%s", username);

	printf("Enter your password> \n");
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
			printf("Displaying all members...");
			sortByAlphabet(users, size);
			displayUser(users, size);
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
			if (assignMember(users,size) == -1) {
				printf("person_index >= MAX_NUM\n");
			}
			else if(assignMember(users,size) == -2) {
				printf("users[person_index].name = 0\n");
			}
			else if(assignMember(users,size) == -3) {
				printf("not enough people\n");
			}	
			else {
				printf("success\n");
			}
            break;
		case '4':
			saveUsers(users, *size);
			break;
		case '5':
			*size = loadUsers(users);
			break;
		case '6':
			printf("Logged out\n");
			selectionMain(users, size);
			break;
		case '7':
			exit(0);
			break;
		default:
			printf("Invalid choice\n");
			break;
		}
	}
}

/* Contributor: Yat Ho Kwok */
void displayUser(person_t users[], int* size) {
	int i, j;
	printf("Username | Password\n");
	for (i = 0; i < *size; i++) {
		printf("%s %s\n", users[i].name, users[i].password);
	}
	printf("\n");
}

/*
Contributors: Danielle Alota, Yat Ho Kwok
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
	for (i = 0; i < *size; i++) {
		if (strcmp(username, users[i].name) == 0 && passDecrypt(users, i, password) == 1) {
			valid = 1;
			foundUser_p = &users[i];
			break;
		}
	}

	/* pass logged in user */
	if (valid) {
		printf("Successful login! Redirecting to user menu.\n\n");
		printf("\n(¯`·._.·(¯`·._.· Ho Ho Ho, Welcome %s ·._.·´¯)·._.·´¯)\n", foundUser_p->name);
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
					printf("Returning to user menu.\n");
					break;
				}
			}

			if (editCh == '1') {
				if (user->listSize == MAX_WISHES) {
					printf("Your list is currently full!");
				}
				else {
					printf("Adding an item.\n");
					addItem(user);
				}
			}
			else if (editCh == '2') {
				if (user->listSize == 0) {
					printf("Your list is currently empty.");
				}
				else {
					printf("Removing an item.\n");
					removeItem(user);
				}
			}
			break;

		case '2':
			changePassword(users, user, size);
			break;

		case '3': /* view santa's wishlist*/
			printf("nothing yet...");
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

/*
Contributor: Danielle Alota
*/
int addItem(person_t* user) {
	char itemName[MAX_LEN], addMore;
	int itemCheck;

	while (1) { /* addresses the "add more items" option*/
		if (user->listSize == MAX_WISHES) {
			printf("Your wishlist is currently full! Redirecting to user menu.\n");
			break;
		}
		printf("What item would you like to add to your wishlist? ");
		scanf(" %s", itemName);
		itemCheck = itemExists(itemName, user);

		while (itemCheck == 1) {
			printf("This item already exists in your list. Please enter a new item or '*' to return to user menu.\n");
			printf("What item would you like to add to your wishlist? ");
			scanf(" %s", itemName);
			if (strcmp(itemName, "*") == 0) {
				return -1;
			}
			itemCheck = itemExists(itemName, user);
		}

		if (itemCheck == 0 && user->listSize != MAX_WISHES) {
			strcpy(user->list[user->listSize].name, itemName);
			user->listSize++;
			printf("%s added successfully! Would you like to add more items? (y / n) ", itemName);
			scanf(" %c", &addMore);

			while (addMore != 'y' && addMore != 'n') {
				printf("Invalid choice. Please try again or enter * to return to user menu.\n");
				printf("Would you like to add more items ? (y / n) ");
				scanf(" %c", &addMore);
			}

			if (addMore == 'y') {
				addItem(user);
			}
			else if (addMore == 'n') {
				printf("Returning to user menu.\n");
				break;
			}
		}
		break;
	}
	return user->listSize;
}

void removeItem(person_t* user) {
	int itemCheck;
	char itemName[MAX_LEN];

	printf("Enter the item name you wish to delete: ");
	scanf(" %s", itemName);
	itemCheck = itemExists(itemName, user);

	while (itemCheck == 0) {
		printf("This item does not exist in your wishlist. Please try again or enter '*' to return to user menu.");
		printf("Enter the item name you wish to delete: ");
		scanf(" %s", itemName);
		itemCheck = itemExists(itemName, user);

		if (strcmp(itemName, "*") == 0) {
			return;
		}
	}

	/*
	more to be added..just not bothered atm
	*/

}

int itemExists(char itemName[MAX_LEN], person_t* user) {
	int i;
	for (i = 0; i < user->listSize; i++) {
		if (strcmp(itemName, user->list[i].name) == 0) {
			return i; /* if item exists return the position of the item*/
		}
	}
	return -1; /* if it doesn't exists return -1*/
}

void displayUser(person_t users[], int* size) {
	int i;
	printf("Username | Password\n");
	for (i = 0; i < *size; i++) {
		printf("%-10s %s\n", users[i].name, users[i].password);
	}
	printf("\n");
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
	validPass = checkPass(user, passEncrypt(password));

	while (!validPass) {
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
		strcpy(user->password, passEncrypt(newPass2));

		passEncrypt(users, size, newPass2);
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

	int i;

	for(i = 0; i < strlen(user->password); i++)
	{
		password[i] = password[i] + KEY;
	}

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
			strcpy(users[i].list[users->listSize].name, users[*size - 1].list[users->listSize].name);
			users[i].list[0].priority = users[*size - 1].list[0].priority;
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
/*contributor: Jack */
int assignMembers(person_t users[MAX_NUM], int* size) {
	int person_index;
	/* person_index validate*/
	if(person_index >= MAX_NUM) {
		return -1;
	}
	if(strcmp(" ", users[person_index].name) == 0) {
		return -2;
	}

	/* check how many pp, if less than 2, then return -3*/
	int i = 0;
	int vaild_user_number = 0;
	for (i = 0; i < MAX_NUM; i++) {
		if(strcmp(" ", users[person_index].name) != 0) {
			vaild_user_number++;
		}
	}

	if(vaild_user_number < 2) {
		return -3;
	}
	
	/* while get random num*/
	int random_user;
	while(1) {
		random_user = rand() % 19;
		if((strcmp(" ", users[random_user].name)) != 0 && (random_user != person_index)) {
			/* assign wishlist*/
			for(i = 0; i < MAX_WISHES; i++) {
				users[random_user].list[i].priority = users[person_index].list[i].priority;
				strcpy(users[random_user].list[i].name, users[person_index].list[i].name);
			}
		}
		break;
	}
	/* success*/
	return 0;
}

/*******************************************************************************
*	This function encrypts a given password.
*******************************************************************************/

=======
void passEncrypt(person_t users[MAX_NUM], int* size, char password[MAX_LEN]) {
	int j;

	for (j = 0; j < strlen(password); j++)
	{
		users[*size].password[j] = password[j] + KEY;
	}

}

/*******************************************************************************
*	This function handles the displaying of a member's wishlist.
*******************************************************************************/

int passDecrypt(person_t users[MAX_NUM], int index, char pass[MAX_PASS_LEN]) {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];
	int j;

	strcpy(password, users[index].password);
	strcpy(username, users[index].name);

	for (j = 0; j < strlen(password); j++)
	{
		password[j] = users[index].password[j] - KEY;
	}
	password[strlen(password)] = '\0';
	
#ifdef DEBUG_MODE
	printf("decrypt: %s\n", password);
#endif
	if(strcmp(password, pass) == 0)
	{
		return 1;
	}
	return 0;
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
			printf("The following shows the wish list of %s\n%s\n", username, users[i].list[0].name);
			return 0;
		}
	}
	/*username not exist*/
	return -1;
}

/*******************************************************************************
*	This function sorts the member list by their names in alphabetical order.

Contributors:
Zhongzhuo Wu
Danielle Alota
*******************************************************************************/

void sortByAlphabet(person_t users[MAX_NUM], int *size) {
 char temp[MAX_NAME_LEN];
 
    int i, j; /* index of the array */
 int k=0; /* index of alph*/
    for(i = 0; i < *size+1; i++){
        for(j = i + 1; j<*size; j++){
			while(users[i].name[k] == users[j].name[k]){ /*  checks the length of the names*/
			k++;/* change names to user */
			if( users[i].name[k] != users[j].name[k]){
				break;
			}
		}
		if(users[j].name[k] < users[i].name[k]) {
			strcpy(temp, users[i].name); /*  if the letter is > */
			strcpy(users[i].name, users[j].name);
			strcpy(users[j].name, temp);
			}   
        }
    }
 
 return;
}

/*******************************************************************************
*	This function prints a given wishlist.
*******************************************************************************/
/*author: Jack*/
int printList(person_t users[MAX_NUM], int* size, person_t* user) {
	int i, j;
	printf("all of the wishlist is below\n");
	/*show all wishlist*/
	for (i = 0; i < *size + 1; i++) {
		if (strcmp(users[i].name, user->name) == 0) {
			for (j = 0; j < user->listSize; j++) {
				printf("%s\n", user->list[j].name);
			}
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
		"4. Save user info\n"
		"5. Load user info\n"
		"6. Log out\n"
		"7. Exit the program\n"
		"Enter choice (number between 1-4)>\n");
}

void printEditMenu() {
	printf("\nEditing wishlist.\n"
		"1. Add an item.\n"
		"2. Remove an item.\n"
		"Enter choice: ");
}

/*******************************************************************************
*	This function compresses (RLE) a given string by eliminating the duplicates
*	with the number of duplicates.
*******************************************************************************/
char* strCompress(char myStr[])
{
	char *s, *in;
	for (s = myStr, in = myStr; *s; s++)
	{
		int count = 1;
		in[0] = s[0];
		in++;
		while (s[0] == s[1])
		{
			count++;
			s++;
		}
		if (count > 1)
		{
			in[0] = '0' + count;
			in++;
		}
	}
	in[0] = 0;
	return myStr;
}

/* Anson */
void saveUsers(person_t users[], int size) {
	FILE* saveFile = fopen(DB_NAME, "w");

	int index;
	if (saveFile) {
		for (index = 0; index < size; index++)
			fwrite(&users[index], sizeof(person_t), 1, saveFile);
		printf("Users info has been saved to 'users' successfully!");
	}
	else printf("Failed to save users info. Please check and try again.");
	printf("\n");
	fclose(saveFile);
}

/* Anson */
int loadUsers(person_t users[]) {
	FILE* loadFile = fopen(DB_NAME, "rb");

	int index = 0;
	if (loadFile) {
		while(!feof(loadFile)) {
			/* Read file line by line */
			fread(&users[index], sizeof(person_t), 1, loadFile);
			index++;
		}
		printf("Users info has been loaded from 'users' successfully!");
		fclose(loadFile);
	} else printf("Failed to read file. Please check and try again.");

	printf("\n");
	return index - 1;
}