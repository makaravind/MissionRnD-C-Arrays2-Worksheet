/*
OVERVIEW: You are given 2 bank statements that are ordered by date.
Write a function that returns dates common to both statements
(ie both statements have transactions in these dates).
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[3] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" }, { 320, "27-08-2015", "Seventh" } };
Output: { { 10, "09-10-2003", "First" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Transactions having same dates.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

#include <iostream>
#include<stdio.h>
#include<malloc.h>
struct date
{
	int day;
	int month;
	int year;
};
struct transaction {
	int amount;
	char date[11];
	char description[20];
};
struct node
{
	struct transaction value;
	int count;
	node* left;
	node* right;
};

struct date Get_Date_Common(char*);
int Compare_Common(struct date *First, struct date *Second);
void  Merge_Common(struct transaction *A, int *ALen, struct transaction *B, int *BLen, struct transaction *result);
void Find_Common(struct node* r, struct transaction *result, int size, int *status);
struct node* insert(struct node* r, struct transaction data)
{
	int com;
	if (r != NULL)
		com = Compare_Common(&Get_Date_Common(data.date), &Get_Date_Common(r->value.date));
	if (r == NULL)
	{
		r = (struct node*) malloc(sizeof(struct node));
		r->count = 1;
		r->value = data;
		r->left = NULL;
		r->right = NULL;
	}

	else if (com == 0){
		//return r;
		r->count++;
		return r;
	}
	else if (com == -1){
		//data < r->value
		r->left = insert(r->left, data);
	}
	else if (com == 1) {
		//data > r->value
		r->right = insert(r->right, data);
	}
	return r;

}
struct transaction * sortedArraysCommonElements(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	//init checking
	if (ALen <= 0 || B <= 0) return NULL;
	if (A == NULL || B == NULL) return NULL;

	static int size = 0;
	int status = 0;
	struct transaction *result1 = (struct transaction*)malloc(sizeof(struct transaction)*(ALen + BLen));
	struct transaction *result = (struct transaction*)malloc(sizeof(struct transaction)*(ALen + BLen));
	struct node* root;
	root = NULL;

	Merge_Common(A, &ALen, B, &BLen, result);

	for (int i = 0; i < (ALen + BLen); i++){
		root = insert(root, result[i]);
	}

	Find_Common(root, result1, size, &status);

	if (status == 0) return NULL;
	return result1;
}
void Find_Common(struct node* r, struct transaction *result, int size, int *status)
{

	if (r != NULL){
		if (r->count == 2) {
			result[size++] = r->value;
			*status = 1;
		}

		Find_Common(r->left, result, size, status);
		Find_Common(r->right, result, size, status);
	}
}
void  Merge_Common(struct transaction *A, int *ALen, struct transaction *B, int *BLen, struct transaction *result){

	int i = 0, j = 0; // pointers to A and B
	int r = 0;//pointer for result
	int com = NULL;
	while (1){
		com = Compare_Common(&Get_Date_Common(A[i].date), &Get_Date_Common(B[j].date));
		if (com == 1){//if second is less than first
			result[r] = B[j];
			j++;
			r++;
			if (j == *BLen) break;
		}
		else if (com == -1){
			//first is less than second
			result[r] = A[i];
			i++;
			r++;
			if (i == *ALen) break;
		}
		else if (com == 0){
			// equal
			result[r] = A[i];
			r++;
			result[r] = B[j];
			r++;
			i++;
			j++;
			if (i == *ALen || j == *BLen)break;
		}
	}

	if (i == *ALen){
		for (int t = j; t < *BLen; t++)
		{
			result[r] = B[t];
			r++;
		}
	}
	else{
		for (int t = i; t < *ALen; t++)
		{
			result[r] = A[t];
			r++;
		}
	}
}
int Compare_Common(struct date *First, struct date *Second){
	//check year
	if (First->year > Second->year) return 1;
	else if (First->year < Second->year) return -1;

	// check month
	if (First->month > Second->month) return 1;
	else if (First->month < Second->month) return -1;

	//check day
	if (First->day > Second->day) return 1;
	else if (First->day < Second->day) return -1;

	//default//Equal
	return 0;
}
struct date Get_Date_Common(char *d){
	struct date *new_date = (struct date*)malloc(sizeof(struct date));
	//init
	new_date->day = 0;
	new_date->month = 0;
	new_date->year = 0;
	char temp;
	bool flag = false;

	//get day
	for (int i = 0; i <= 1; i++){
		temp = d[i];
		if ((temp - '0') == 0 && flag == false) {
			continue;
		}
		flag = true;
		new_date->day += (temp - '0');
		if (i != 1)
			new_date->day *= 10;
	}

	//get month
	for (int i = 3, flag = false; i <= 4; i++){
		temp = d[i];
		if ((temp - '0') == 0 && flag == false) {
			continue;
		}
		flag = true;
		new_date->month += (temp - '0');
		if (i != 4)
			new_date->month *= 10;
	}

	//get year
	for (int i = 6, flag = false; i <= 9; i++){
		temp = d[i];
		if ((temp - '0') == 0 && flag == false) {
			continue;
		}
		flag = true;
		new_date->year += (temp - '0');
		if (i != 9)
			new_date->year *= 10;
	}

	return *new_date;
}