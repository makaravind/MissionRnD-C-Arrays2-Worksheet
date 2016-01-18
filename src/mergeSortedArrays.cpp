/*
OVERVIEW: You are given 2 bank statements that are ordered by date -
Write a function that produces a single merged statement ordered by dates.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
B[2] = { { 10, "09-10-2003", "First" }, { 220, "18-01-2010", "Sixth" } };
Output: { { 10, "09-10-2003", "First" }, { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" },  30, "03-03-2005", "Third" }, { 220, "18-01-2010", "Sixth" } }

INPUTS: Two bank statements (array of transactions).

OUTPUT: Combined statement ordered by transaction date.

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
struct date Get_Date_Merge(char*);
int Compare(struct date *First, struct date *Second);
void Merge(struct transaction *A, int *ALen, struct transaction *B, int *BLen, struct transaction *result);
struct transaction * mergeSortedArrays(struct transaction *A, int ALen, struct transaction *B, int BLen) {
	//init checking
	if (ALen <= 0 || B <= 0) return NULL;
	if (A == NULL || B == NULL) return NULL;

	struct transaction *result = (struct transaction*)malloc(sizeof(struct transaction)*(ALen + BLen));
	Merge(A, &ALen, B, &BLen, result);
	return result;
}
void  Merge(struct transaction *A, int *ALen, struct transaction *B, int *BLen, struct transaction *result){

	int i = 0, j = 0; // pointers to A and B
	int r = 0;//pointer for result
	int com = NULL;
	while (1){
		com = Compare(&Get_Date_Merge(A[i].date), &Get_Date_Merge(B[j].date));
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
int Compare(struct date *First, struct date *Second){
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
struct date Get_Date_Merge(char *d){
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
