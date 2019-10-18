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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * List preprocessing directives.
*******************************************************************************/

/* Debug mode and administration **********************************************/
/*#define DEBUG_MODE 1*/
#define ADMIN_LOGIN "admin"
/******************************************************************************/

/* Field lengths **************************************************************/
#define MAX_NAME_LEN 10
#define MAX_PASS_LEN 20
#define MAX_LEN 99
#define MAX_WISHES 5
#define MAX_NUM 3
/******************************************************************************/

/* Encryption keys ************************************************************/
#define KEY 3
/*******************/

/* FIle processing ************************************************************/
#define DB_NAME "users"
/******************************************************************************/

/*Login messages **************************************************************/
#define LOGIN_ENTER_USERNAME "Please enter your username>\n"
#define LOGIN_ENTER_PASSWORD "Please enter your password>\n"
#define LOGIN_SUCCESSFUL "Login Successful! Redirecting to selection menu..."\
							"\n\n"
#define LOGIN_FAIL "Login failed. Returning to main menu.\n"
/******************************************************************************/

/* Admin menu messages ********************************************************/
#define ASSIGNING_MEMBERS "Assigning members...\n\n"
#define ASSIGN_MEMBERS_SUCCESS "Secret Santas have been assigned successfully!"\
								" Returning to admin menu...\n"
#define WELCOME_ADMIN "\n(¯`·._.·(¯`·._.· Ho Ho Ho, Welcome Admin ·._.·´¯)"\
							"·._.·´¯)\n"
#define NO_PARTICIPANTS "There are currently no participants."
#define DISPLAYING_ALL_PARTICIPANTS "Displaying all particpating "\
										  "members..."
#define ADMIN_USER_DOES_NOT_EXIST "This user does not exist. Returning to "\
								  "admin menu.\n"
#define ADMIN_REMOVE_MEMBER_SUCCESS "Member removed successfully. "\
										  "Returning to admin menu.\n"
#define ADMIN_MEMBER_DOES_NOT_EXIST "This member does not exist. Returning to "\
									"admin menu.\n"
#define SAVE_USERS_INFO_SUCCESS "Users info has been saved to 'users' " \
								"successfully!"
#define SAVE_USERS_INFO_FAIL "Failed to save users info. Please check and " \
							 "try again."
#define LOAD_USERS_INFO_SUCCESS "Users info has been loaded from 'users' " \
								"successfully!"
#define LOAD_USERS_INFO_FAIL "Failed to read file. Please check and try again."
#define REMOVING_MEMBER "Removing member. Please enter the name of the "\
						"member you wish to delete: "
#define DISPLAY_USER_HEADER "Username | Password | Index\n"								
/******************************************************************************/

/* Error messages *************************************************************/
#define ERROR_MAX_USERS_REACHED "Max users reached. Returning to main menu.\n"
#define ERROR_INVALID_CHOICE "Invalid choice! Please check and try again!\n"
#define ERROR_WISHLIST_INVALID_CHOICE "Invalid choice. Please try again"\
									  " or enter * to return to user menu.\n"
#define ERROR_USER_ALREADY_EXISTS "User already exists! Please try again or"\
								  " enter '*' to return to menu.\n"
#define ERROR_WISHLIST_ITEM_ALREADY_EXIST "This item already exists in your "\
											"list. Please enter a new item "\
											"or '*' to return to menu.\n"
#define ERROR_WISHLIST_ITEM_DOES_NOT_EXIST "This item does not exist in your "\
										   "wishlist. Please try again or "\
										   "enter '*' to return to user menu.\n"
#define ERROR_INCORRECT_PASSWORD "Incorrect password. Try again or enter * to "\
								 "go back to menu.\n"
#define ERROR_PASSWORDS_DO_NOT_MATCH "Passwords do not match. Try again or "\
									 "enter * to go back to menu.\n"
#define ERROR_NOT_ENOUGH_MEMBERS "There are not enough members. Please create" \
								 "more users!\n"
#define ERROR_WISHLIST_IS_FULL "Your list is currently full!\n"
#define ERROR_INVALID_USERNAME "Invalid username. Please check and try again!\n\n"
#define ERROR_INVALID_PASSWORD "Invalid password. Please check and try again!\n\n"
/******************************************************************************/

/*userRegister messags*********************************************************/
#define REGISTER_ENTER_USERNAME "Please enter your name (without spaces)>\n"
#define REGISTER_ENTER_PASSWORD "Enter your password>\n"
#define REGISTER_SUCCESSFUL "User has been registered successfully! "\
							"Returning to main menu.\n"
/******************************************************************************/

/* viewGiftee *****************************************************************/
#define YOU_DONT_HAVE_A_GIFTEE_YET "\nYou don't have a giftee yet! Please "\
								   "contact the admin and try again!\n"
/******************************************************************************/

/* Logout messages ************************************************************/
#define LOGGED_OUT_SUCCESSFULLY "Logged out successfully! Return to the "\
								"previous menu...\n"
#define RETURNING_TO_USER_MENU "Returning to user menu.\n"
/******************************************************************************/

/* Edit wishlist messages *****************************************************/
#define WISHLIST_RETURN_TO_MENU "Returning to user menu.\n"
#define WISHLIST_IS_EMPTY "Your list is currently empty.\n"
#define WISHLIST_ADDING_AN_ITEM "Adding an item.\n"
#define WISHLIST_REMOVING_AN_ITEM "Removing an item.\n"
#define WISHLIST_ENTER_ADD_ITEM_NAME "What item would you like to add to your "\
									 "wishlist?\n"
#define WISHLIST_ADD_MORE_ITEMS_Y_N "Would you like to add more items ? "\
									"(y / n) "
#define WISHLIST_ENTER_REMOVE_ITEM_NAME "Enter the item name you wish to "\
										"delete: "
#define WISHLIST_REMOVE_ITEM_SUCCESS "Item successfully removed from your "\
									 "wishlist.\n"
/******************************************************************************/

/******************************************************************************/
#define ENTER_YOUR_CURRENT_PASSWORD	"Please enter your current password: "
#define ENTER_NEW_PASSWORD "Please enter a new password: "
#define CONFIRM_PASSWORD "Confirm new password: "
/******************************************************************************/

/******************************************************************************/
#define ENTER_VIEW_WISHES_NAME "Please enter the username you want to check: "
#define USER_HAS_NO_ITEMS "This user currently has no items in their " \
						  "wishlist.\n"
#define GIFTEE_HAS_NO_ITEMS "\n....but they don't have anything on their wishlist yet.\n"
/******************************************************************************/

/*******************************************************************************
 * List structs.
*******************************************************************************/

struct wishlist {
	char name[MAX_LEN];
};
typedef struct wishlist wishlist_t;

struct person
{
	char name[MAX_NAME_LEN + 1];
	char password[MAX_LEN + 1];
	wishlist_t list[MAX_WISHES + 1];
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
void assignMembers(person_t users[], int* size);
void passEncrypt(person_t* user, char password[MAX_PASS_LEN]);
int passDecrypt(person_t users[MAX_NUM], int index, char pass[MAX_PASS_LEN]);
int viewWishes(person_t users[MAX_NUM], int* size);
void sortByAlphabet(person_t users[MAX_NUM], int* size);
void printList(person_t users[MAX_NUM], int* size, person_t* user);
int addItem(person_t* user);
void removeItem(person_t* user);
int itemExists(char itemName[MAX_LEN], person_t* user);
void changePassword(person_t users[MAX_NUM], person_t* user, int* size);
int checkPass(person_t* user, char password[MAX_PASS_LEN]);
int passMatch(char pass1[MAX_PASS_LEN], char pass2[MAX_PASS_LEN]);
void printEditMenu();
void editWishlist(person_t users[MAX_NUM], int* size, person_t* user);
void displayUser(person_t users[], int* size);
char* strCompress(char myStr[]);
void saveUsers(person_t users[], int size);
int loadUsers(person_t users[]);
person_t* checkUserLogin(char username[], char password[], person_t users[], int* size);
void printMain();
void printUser();
void printAdmin();
void viewGiftee(person_t users[], int* size, person_t user);
int usernameIsValid(char* username);
int passwordIsValid(char* password);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(int argc, char* argv[]) {
	int size = 0;
	int* size_p = &size;
	person_t users[MAX_NUM + 1];

	if (argc)
		selectionMain(users, size_p);
	else if (!strcmp(argv[1], "login"))
		userLogin(users, size_p);
	else if (!strcmp(argv[1], "register"))
		userRegister(users, size_p);
	else if (!strcmp(argv[1], "admin"))
		adminLogin(users, size_p);

	return 0;
}

/*
Contributors: Danielle Alota
*/
void selectionMain(person_t users[MAX_NUM], int* size) {
	char c;
	while (1) {
		printMain();
		scanf(" %c", &c); /* This is so it doesn't go into an infinite loop */
		switch (c) /* when input aren't numbers*/
		{
		case '1':
			adminLogin(users, size);
			break;
		case '2':
			userLogin(users, size);
			break;
		case '3':
			if (*size == MAX_NUM)
				printf(ERROR_MAX_USERS_REACHED);
			else {
				*size = userRegister(users, size);

			}
			break;
		case '4':
			exit(0);
			break;

		default:
			printf(ERROR_INVALID_CHOICE);
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
	char password[MAX_PASS_LEN];
	int valid;

	printf("Create a username no more than %d characters, numbers and " \
			   "letters are accepted (without spaces).\n", MAX_NAME_LEN);
	printf(REGISTER_ENTER_USERNAME);
	scanf("%s", name);

	while (!usernameIsValid(name)) {
		printf(ERROR_INVALID_USERNAME);
		printf(REGISTER_ENTER_USERNAME);
		scanf("%s", name);
	}

	strcpy(compressed, name);
	strCompress(compressed);

#ifdef DEBUG_MODE
	printf("Compressed name = %s\n", compressed);
#endif

	valid = nameTaken(users, name, size);
	while (valid) {
		printf(ERROR_USER_ALREADY_EXISTS);
		printf(REGISTER_ENTER_USERNAME);
		scanf("%s", name);
		if (strcmp(name, "*")) {
			return -1;
		}
		valid = nameTaken(users, name, size);
	}

	if (valid == 0) {
		strcpy(users[*size].name, name);
		users[*size].listSize = 0;
		users[*size].index = -1;

		printf("Create a password no more than %d characters, numbers and " \
			   "letters are accepted (without spaces).\n", MAX_PASS_LEN);
		printf(REGISTER_ENTER_PASSWORD);
		scanf("%s", password);

		while(!passwordIsValid(password)) {
			printf(ERROR_INVALID_PASSWORD);
			printf(REGISTER_ENTER_PASSWORD);
			scanf("%s", password);
		}

		strcpy(users[*size].password, password);
		passEncrypt(&users[*size], password);

		*size = *size + 1;
		printf(REGISTER_SUCCESSFUL);
	}

#ifdef DEBUG_MODE
	printf("//Username: %s - Password: %s\n", name, users[*size - 1].password);
#endif
	return *size;
}

/* Anson */
int usernameIsValid(char* username) {
	return strlen(username) <= MAX_NAME_LEN;
}

/* Anson */
int passwordIsValid(char* password) {
	return strlen(password) <= MAX_PASS_LEN;
}

/*
This function checks if the inputted name already exists in the array of members
Contributors: Danielle Alota
*/
int nameTaken(person_t users[MAX_NUM], char name[], int* size) {
	int i;
	for (i = 0; i < *size + 1; i++) {
		if (!strcmp(users[i].name, name)) {
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
	char password[MAX_PASS_LEN];

	printf(LOGIN_ENTER_USERNAME);
	scanf("%s", username);

	printf(LOGIN_ENTER_PASSWORD);
	scanf("%s", password);

	if (!strcmp(username, ADMIN_LOGIN) && !strcmp(password, ADMIN_LOGIN)) {
		printf(LOGIN_SUCCESSFUL);
		printf(WELCOME_ADMIN);
		selectionAdmin(users, size);
	}
	else {
		printf(LOGIN_FAIL);
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
			if (*size == 0) {
				printf(NO_PARTICIPANTS);
			}
			else {
				printf(DISPLAYING_ALL_PARTICIPANTS);
				sortByAlphabet(users, size);
				displayUser(users, size);
			}
			break;
		case '2':
			if (viewWishes(users, size) == -1) {
				puts(ADMIN_USER_DOES_NOT_EXIST);
			}
			break;
		case '3':
			if (removeMember(users, size) != -1)
				printf(ADMIN_REMOVE_MEMBER_SUCCESS);
			else
				printf(ADMIN_MEMBER_DOES_NOT_EXIST);
			break;
		case '4':
			assignMembers(users, size);
			break;
		case '5':
			saveUsers(users, *size);
			break;
		case '6':
			*size = loadUsers(users);
			break;
		case '7':
			printf(LOGGED_OUT_SUCCESSFULLY);
			selectionMain(users, size);
			break;
		case '8':
			exit(0);
			break;
		default:
			printf(ERROR_INVALID_CHOICE);
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
	char password[MAX_PASS_LEN];
	person_t* foundUser_p = NULL;

	printf(LOGIN_ENTER_USERNAME);
	scanf("%s", username);
	printf(LOGIN_ENTER_PASSWORD);
	scanf("%s", password);

	foundUser_p = checkUserLogin(username, password, users, size);

	if (foundUser_p != NULL) {
		printf(LOGIN_SUCCESSFUL);
		printf("\n(¯`·._.·(¯`·._.· Ho Ho Ho, Welcome %s ·._.·´¯)·._.·´¯)\n", foundUser_p->name);
		selectionUser(users, size, foundUser_p);
	}
	else {
		printf(LOGIN_FAIL);
		selectionMain(users, size);
	}
}

/* Anson, returns position of logged in user or -1 */
person_t* checkUserLogin(char username[], char password[], person_t users[], int* size) {
	int i;

	for (i = 0; i < *size + 1; i++) {
		if (!strcmp(username, users[i].name) && passDecrypt(users, i, password)) {
			return &users[i];
		}
	}

	return NULL;
}


/*
Contributor: Danielle Alota
*/
void selectionUser(person_t users[MAX_NUM], int* size, person_t* user) {
	char choice;

	while (1) {
		printUser();
		scanf(" %c", &choice);
		switch (choice)
		{
		case '1':
			editWishlist(users, size, user);
			break;

		case '2': /* changees current password*/
			changePassword(users, user, size);
			break;

		case '3': /* view your assigned's member's wishlist*/
			viewGiftee(users, size, *user);
			break;

		case '4':
			printf(LOGGED_OUT_SUCCESSFULLY);
			selectionMain(users, size);
			break;

		case '5':
			exit(0);
			break;

		default:
			printf(ERROR_INVALID_CHOICE);
			break;
		}
	}
}

void editWishlist(person_t users[MAX_NUM], int* size, person_t* user) {
	char c;

	while (1) {
		printEditMenu();
		scanf(" %c", &c);
		switch (c) {
		case '1':
			if (user->listSize == MAX_WISHES) {
				printf(ERROR_WISHLIST_IS_FULL);
			}
			else {
				printf(WISHLIST_ADDING_AN_ITEM);
				addItem(user);
			}
			break;
		case '2':
			if (user->listSize == 0) {
				printf(WISHLIST_IS_EMPTY);
			}
			else {
				printf(WISHLIST_REMOVING_AN_ITEM);
				removeItem(user);
			}
			break;
		case '3':
			if (user->listSize == 0) {
				printf(WISHLIST_IS_EMPTY);
			}
			else {
				printList(users, size, user);
			}
			break;
		case '4':
			printf(WISHLIST_RETURN_TO_MENU);
			return;
		case '*':
			printf(WISHLIST_RETURN_TO_MENU);
			break;
		default: printf(ERROR_WISHLIST_INVALID_CHOICE); break;
		}
	}

}
/* Anson */
void viewGiftee(person_t users[], int* size, person_t user) {
	if (user.index == -1) printf(YOU_DONT_HAVE_A_GIFTEE_YET);
	else {
		printf("\n(¯`·._.· Ho Ho Ho, you're %s's Secret Santa ·._.·´¯)\n", users[user.index].name);
		printList(users, size, &users[user.index]);
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
			printf(ERROR_WISHLIST_IS_FULL);
			break;
		}
		printf(WISHLIST_ENTER_ADD_ITEM_NAME);
		scanf("%s", itemName);
		itemCheck = itemExists(itemName, user);

		while (itemCheck != -1) {
			printf(ERROR_WISHLIST_ITEM_ALREADY_EXIST);
			printf(WISHLIST_ENTER_ADD_ITEM_NAME);
			scanf("%s", itemName);
			if (strcmp(itemName, "*") == 0) {
				return -1;
			}
			itemCheck = itemExists(itemName, user);
		}

		if (itemCheck == -1 && user->listSize != MAX_WISHES) {
			strcpy(user->list[user->listSize].name, itemName);
			user->listSize++;
			printf("%s added successfully! Would you like to add more items? (y / n) ", itemName);
			scanf(" %c", &addMore);

			while (addMore != 'y' && addMore != 'n') {
				printf(ERROR_WISHLIST_INVALID_CHOICE);
				printf(WISHLIST_ADD_MORE_ITEMS_Y_N);
				scanf(" %c", &addMore);
			}

			if (addMore == 'y') {
				addItem(user);
			}
			else if (addMore == 'n') {
				printf(RETURNING_TO_USER_MENU);
				break;
			}
		}
		break;
	}
	return user->listSize;
}

/*
Contributor: Danielle Alota
*/
void removeItem(person_t* user) {
	int itemCheck;
	char itemName[MAX_LEN];

	printf(WISHLIST_ENTER_REMOVE_ITEM_NAME);
	scanf(" %s", itemName);
	itemCheck = itemExists(itemName, user);

	while (itemCheck == -1) {
		printf(ERROR_WISHLIST_ITEM_DOES_NOT_EXIST);
		printf(WISHLIST_ENTER_REMOVE_ITEM_NAME);
		scanf(" %s", itemName);
		itemCheck = itemExists(itemName, user);

		if (strcmp(itemName, "*") == 0) {
			return;
		}
	}

	if (itemCheck != -1) {
		strcpy(user->list[itemCheck].name, user->list[user->listSize - 1].name);
		user->listSize--;
		printf(WISHLIST_REMOVE_ITEM_SUCCESS);
		return;
	}

}

/*
Contributor: Danielle Alota
*/
int itemExists(char itemName[MAX_LEN], person_t* user) {
	int i;

	for (i = 0; i < user->listSize; i++) {
		if (!strcmp(itemName, user->list[i].name))
			return i; /* if item exists return the position of the item*/
	}
	return -1; /* if it doesn't exists return -1*/
}

void displayUser(person_t users[], int* size) {
	int i;
	printf(DISPLAY_USER_HEADER);

	for (i = 0; i < *size; i++)
		printf("%-10s %-20s %d\n", users[i].name, users[i].password, users[i].index);

	printf("\n");
}

/*
Contributor: Danielle Alota
*/
void changePassword(person_t users[MAX_NUM], person_t* user, int* size) {
	char password[MAX_PASS_LEN];
	char newPass1[MAX_PASS_LEN];
	char newPass2[MAX_PASS_LEN];
	int validPass;

	printf(ENTER_YOUR_CURRENT_PASSWORD);
	scanf("%s", password);
	if (!strcmp(password, "*")) return;

	validPass = checkPass(user, password);

	while (validPass) {
		printf(ERROR_INCORRECT_PASSWORD);
		printf(ENTER_YOUR_CURRENT_PASSWORD);
		scanf("%s", password);
		validPass = checkPass(user, password);
		if (!strcmp(password, "*")) return;
	} /* checks for correct password*/

	printf(ENTER_NEW_PASSWORD);
	scanf("%s", newPass1); /* add: check for max length (fgets/sscanf isnt working for me)*/
	printf(CONFIRM_PASSWORD); /* have not checked if inputted nothing*/
	scanf("%s", newPass2);

	while (strcmp(newPass1, newPass2)) {
		printf(ERROR_PASSWORDS_DO_NOT_MATCH);
		printf(ENTER_NEW_PASSWORD);

		scanf("%s", newPass1); /* add: check for max length (fgets/sscanf isnt working for me)*/
		if (!strcmp(newPass1, "*")) return;

		printf(CONFIRM_PASSWORD);

		scanf("%s", newPass2);
		if (!strcmp(newPass2, "*")) break;
	}
#ifdef DEBUG_MODE
	printf("//newPass1 = %s - newPass2 = %s\n", newPass1, newPass2);
#endif
	passEncrypt(user, newPass2);
}

/*
Contributor: Danielle Alota
*/
int passMatch(char pass1[MAX_PASS_LEN], char pass2[MAX_PASS_LEN]) {
	return !strcmp(pass1, pass2);
}

/*
Contributor: Danielle Alota
*/
int checkPass(person_t* user, char password[MAX_PASS_LEN]) {
	int i;

	for (i = 0; i < strlen(user->password); i++)
		password[i] = password[i] + KEY;

	return strcmp(user->password, password);
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
	printf(REMOVING_MEMBER);
	scanf(" %s", name);

	/*if exist delete*/
	for (i = 0; i < *size + 1; i++) {
		if (!strcmp(name, users[i].name)) {
			strcpy(users[i].name, users[*size - 1].name);
			strcpy(users[i].password, users[*size - 1].password);

			users[i].index = users[*size - 1].index;

			strcpy(users[i].list[users->listSize].name, users[*size - 1].list[users->listSize].name);
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
void assignMembers(person_t users[], int* size) {
	printf(ASSIGNING_MEMBERS);

	if (*size <= 1) printf(ERROR_NOT_ENOUGH_MEMBERS);
	else {
		int userAssigned[*size];
		int i;

		/* Initialise flag array */
		for (i = 0; i < *size; i++) userAssigned[i] = 0;

		for (i = 0; i < *size; i++) {
			int randIndex = rand() % *size;
			while (userAssigned[randIndex] == 1 || randIndex == i) {
#ifdef DEBUG_MODE
				printf("//randIndex = %d", randIndex);
#endif
				randIndex = rand() % *size;

			}


			users[i].index = randIndex;
			userAssigned[randIndex] = 1;
#ifdef DEBUG_MODE
			printf("//users[%d].index = %d\n", i, randIndex);
#endif
		}


		printf(ASSIGN_MEMBERS_SUCCESS);
		/* randomly generate 0 - size by size times */
			/* check if number is taken, if not: index = num else keep generating */
	}
}

/*******************************************************************************
*	This function encrypts a given password.
*******************************************************************************/
void passEncrypt(person_t* user, char password[MAX_PASS_LEN]) {
#ifdef DEBUG_MODE
	printf("//passEncrypt has been called!\n//password = %s\n", password);
#endif
	int j;

	for (j = 0; j < strlen(password); j++)
		user->password[j] = password[j] + KEY;

#ifdef DEBUG_MODE
	printf("//Encrypted password = %s\n", user->password);
#endif
}

/*******************************************************************************
*	This function handles the displaying of a member's wishlist.
*******************************************************************************/

int passDecrypt(person_t users[MAX_NUM], int index, char pass[MAX_PASS_LEN]) {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];
	int j;

	/* Get user username & password */
	strcpy(password, users[index].password);
	strcpy(username, users[index].name);

	for (j = 0; j < strlen(password); j++)
		password[j] = users[index].password[j] - KEY;
	password[strlen(password)] = '\0';

#ifdef DEBUG_MODE
	printf("Decrypted password: %s\n", password);
#endif
	return !strcmp(password, pass);
}

/*******************************************************************************
*	This function allows the admin to display a given member's wishlist.
*******************************************************************************/
/*contributors: Jack
Danielle */
int viewWishes(person_t users[MAX_NUM], int* size) {
	int i, j;
	char username[MAX_NAME_LEN];

	/*enter username then show the wishlist*/
	printf(ENTER_VIEW_WISHES_NAME);
	scanf("%s", username);
	for (i = 0; i < *size; i++) {
		if (strcmp(username, users[i].name) == 0) {
			if (users[i].listSize == 0) {
				printf(USER_HAS_NO_ITEMS);
				return 0;
			}
			else {
				printf("The following shows the wishlist of %s", username);
				for (j = 0; j < users[i].listSize; j++) {
					printf("\n%s\n", users[i].list[j].name);
				}
			}
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
void sortByAlphabet(person_t users[MAX_NUM], int* size) {
	char temp[MAX_NAME_LEN];

	int i, j; /* index of the array */
	int k = 0; /* index of alphabet*/
	for (i = 0; i < *size + 1; i++) {
		for (j = i + 1; j < *size; j++) {
			while (users[i].name[k] == users[j].name[k]) { /*  checks the length of the names*/
				k++;
				if (users[i].name[k] != users[j].name[k]) {
					break;
				}
			}
			if (users[j].name[k] < users[i].name[k]) {
				strcpy(temp, users[i].name);
				strcpy(users[i].name, users[j].name);
				strcpy(users[j].name, temp);
			}
		}
	}
}


/*******************************************************************************
*	This function compresses (RLE) a given string by eliminating the duplicates
*	with the number of duplicates.

Contributor: Bilal
*******************************************************************************/
char* strCompress(char myStr[]) {
	char* s, * in;
	for (s = myStr, in = myStr; *s; s++)
	{
		int count = 1;
		in[0] = s[0];
		in++;
		while (s[0] == s[1]) {
			count++;
			s++;
		}
		if (count > 1) {
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
		printf(SAVE_USERS_INFO_SUCCESS);
	}
	else printf(SAVE_USERS_INFO_FAIL);
	printf("\n");
	fclose(saveFile);
}

/* Anson */
int loadUsers(person_t users[]) {
	FILE* loadFile = fopen(DB_NAME, "rb");

	int index = 0;
	if (loadFile) {
		while (!feof(loadFile)) {
			/* Read file line by line */
			fread(&users[index], sizeof(person_t), 1, loadFile);
			index++;
		}
		printf(LOAD_USERS_INFO_SUCCESS);
		fclose(loadFile);
	}
	else printf(LOAD_USERS_INFO_FAIL);

	printf("\n");
	return index - 1;
}

/*******************************************************************************
*	This function prints the user's wishlist.
******************************************************************************/
/*author: Jack*/
void printList(person_t users[MAX_NUM], int* size, person_t* user) {
	int i, j;

	if (user->listSize == 0) {
		printf(GIFTEE_HAS_NO_ITEMS);
		return;
	}

	printf("\n(¯`·._.·(¯`·._.· %s's Wishlist ·._.·´¯)·._.·´¯)\n", user->name);

	/*show all wishlist*/
	for (i = 0; i < *size + 1; i++)
		if (!strcmp(users[i].name, user->name))
			for (j = 0; j < user->listSize; j++)
				printf("%s\n", user->list[j].name);
}


void printMain() {
	printf("\n(¯`·._.·(¯`·._.· Ho Ho Ho, Welcome to Secret Santa ·._.·´¯)"\
		"·._.·´¯)\n\n"
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
		"2. View a user's wishlist\n"
		"3. Remove a user\n"
		"4. Assign users\n"
		"5. Save user info\n"
		"6. Load user info\n"
		"7. Log out\n"
		"8. Exit the program\n"
		"Enter choice (number between 1-4)>\n");
}

void printEditMenu() {
	printf("\nEditing wishlist.\n"
		"1. Add an item.\n"
		"2. Remove an item.\n"
		"3. View my wishlist.\n"
		"4. Return to user menu.\n"
		"Enter choice: ");
}