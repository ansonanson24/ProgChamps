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

/*
Add people to the persons array
*/
void addMember() {
	
}

/*
Remove people from persons array
*/
void removeMember() {

}

/*
Assign a wishlist to each person
*/
void assignMembers() {

}

/*
Print wishlist to view
*/
void viewWishes() {

}

/*
Encrypt the password of the person
*/
void passEncrypt() {

}

/*
Sort names alphabetically
*/
void sortByAlphabet() {

}

/*
???
*/
void printList() {

}



