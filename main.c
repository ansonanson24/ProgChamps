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
	char wishlist[MAX_WISHES + 1]; /* write to text file */
};
typedef struct person person_t;

void addMember();
void removeMember();
void assignMembers();
void viewWishes();

int main(void) {
	person_t persons[MAX_NUM][MAX_NUM];
	/* subject to change, 2d array was discussed as a possibility*/

	return 0;
}

/*
Add people to array persons
*/
void addMember() {
	
}

/*
Remove people to array persons
*/
void removeMember() {

}

void assignMembers() {

}

void viewWishes() {

}


