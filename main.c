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
	int santa; /* assigned santa */
};
typedef struct person person_t;

/*******************************************************************************
 * Function prototypes.
*******************************************************************************/
void printMain();
void selectionMain(person_t users[], int size);
void adminLogin();
void adminMenu();
void printAdmin();
void selectionAdmin();
void userLogin(person_t users[], int size);
void userMenu();
void printUser();
void selectionUser();
void userRegister();
void addMember();
void removeMember();
void assignMembers();
void viewWishes();
void passEncrypt();
void sortByAlphabet();
void printList();
int checkUser(person_t users[], int size, char username[], char password[]);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void) {
	
	person_t persons[MAX_NUM];
	/* 1d */
	int size = 0;

	while(1) {
		printMain();
		selectionMain(persons, size);
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

/*
Main author: Bilal
*/
void selectionMain(person_t users[], int size) {
	int number;
	scanf("%d", &number);
	
	switch(number)
	{
		case 1:
		adminLogin();
		break;
		
		case 2:
		userLogin(users, size);
		break;
		
		case 3:
		userRegister();
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
void adminLogin() {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];

	printf("Enter username>\n");
	scanf("%s", username);

	printf("Enter password>\n");
	scanf("%s", password);
	
	if(strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
		printf("Login success\n");
		adminMenu();
	} else {
	printf("Login failed\n");
	return;
	}
}

/*
Main author: Bilal
*/
void adminMenu() {
	while(1) {
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

/*
Main author: Bilal
*/

void selectionAdmin() {
	int number;
	scanf("%d", &number);
	
	switch(number)
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

/*
Main author: Bilal
*/
void userLogin(person_t users[], int size) {
	char username[MAX_NAME_LEN];
	char password[MAX_PASS_LEN];
	int i, userIndex;
	person_t user;

	printf("Enter username>\n");
	scanf("%s", username);

	printf("Enter password>\n");
	scanf("%s", password);
	
	/* checks array for login, returns index of user is found, returns 0 otherwise. */
	userIndex= checkUser(users, size, username, password);
	
	if (userIndex) {
		user = users[userIndex];
		printf("Login success\n");
		userMenu();
	} else printf("Login failed.\n");
}

int checkUser(person_t users[], int size, char username[], char password[]) {
	int i;

	for (i = 0; i < size; i++) {
		if (strcmp(username, users[i].name) == 0 && strcmp(password, users[i].password) == 0)
			return i;
	}
	return 0;
}
/*
Main author: Bilal
*/
void userMenu() {
	while(1) {
	printUser();
	selectionUser();
	}
}

void printUser() {
	printf("\n"
    "1. Edit wishlist\n"
    "2. Change password\n"
    "3. View assigned\n"
    "4. Log out\n"
    "5. Exit the program\n"
    "Enter choice (number between 1-4)>\n");
}

/*
Main author: Bilal
*/
void selectionUser() {
	int number;
	scanf("%d", &number);
	
	switch(number)
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

//author: Jack
void userRegister() {
	char temp[20];
	printf("User register\n");
	printf("enter username\n");
	scanf("%s", person_t.username, "r");
	
	//check if name is already exist in array
	if (fp != NULL) {
		printf("this username is already exist\n");
		fclose(fp);
		printf("continue?(Y/N)\n");
		if(getch() == 'Y') {
			return userRegister();
		} else {
			return userLogin();
		}
	}	
	
	while(1) {
		//check username lengh
		if(strlen(username) <= 10) {
			while(1) {
				//enter password
				printf("enter password(10 character)\n");
				scanf("%s", person_t.password);
				printf("enter password again\n");
				scanf("%s", temp);
				//check if both given passwords match
				//check password lengh
				if(strcmp(person_t.password, temp) != 0) {
					printf("Two passwords are inconsistent, please re-enter\n");
				} 
				else {
					if(strlen(password) == 10) {
						printf("registration success\n");
						break;
					} 
					else {
						printf("The length of the password is %d, please enter again", strlen(password));
					}
				}
			}
			break;
		} 
		else {
			printf("The length of the username is %d, please enter again",strlen(username));
		}
	}	
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


