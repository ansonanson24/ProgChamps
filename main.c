#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 10
#define MAX_PASS_LEN 99
#define MAX_WISHES 5
#define MAX_NUM 50


struct person
{
	char name[MAX_NAME_LEN + 1];
	int age;
	char password[MAX_PASS_LEN + 1]; /* Gonna see if we can use other libraries besides those for limits.h */
	char wishlist[MAX_WISHES + 1]; /* will be written to text file */
};
typedef struct person person_t;

void addMember();
void removeMember();
void assignMembers();
void viewWishes();
void passEncrypt();
void sortByAlphabet();
void printList();

int main(void) {
	person_t persons[MAX_NUM][MAX_NUM];
	/* subject to change, 2d array was discussed as a possibility*/

	return 0;
}

/*******************************************************************************
*	This function adds a new member inputted by the user to the member list.
*******************************************************************************/
void addMember() {
	
}

/*******************************************************************************
*	This function removes an existing member inputted by the user from the 
*	member list.
*******************************************************************************/
void removeMember() {

}

/*******************************************************************************
*	This function assigns a random member's wishlist to another member.
*******************************************************************************/
void assignMembers() {

}

/*******************************************************************************
*	This function handles the displaying of a member's wishlist.
*******************************************************************************/
void viewWishes() {

}

/*******************************************************************************
*	This function encrypts a given password.
*******************************************************************************/
void passEncrypt() {

}

/*******************************************************************************
*	This function sorts the member list by their names in alphabetical order.
*******************************************************************************/
void sortByAlphabet() {

}

/*******************************************************************************
*	This function prints a given wishlist.
*******************************************************************************/
void printList() {

}



