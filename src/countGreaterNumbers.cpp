/*
OVERVIEW: You are given a bank statement where transactions are ordered by date. Write a function that finds the number of transactions in that statement after a given date.
-- find the count of numbers greater than a given number in a sorted array.
E.g.: Input: A[3] = { { 10, "09-10-2003", "First" }, { 20, "19-10-2004", "Second" }, { 30, "03-03-2005", "Third" } };
date = "19-10-2004"
Output: 1 (as there is only one transaction { 30, "03-03-2005", "Third" })

INPUTS: One bank statement (array of transactions) and date.

OUTPUT: Return the number of transactions in that statement after a given date.

ERROR CASES: Return NULL for invalid inputs.

NOTES:
*/

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
struct date Get_Date(char*);
int Decide(struct date *To_compare, struct date *Ref);
int countGreaterNumbers(struct transaction *Arr, int len, char *date) {
	struct date ref = Get_Date(date);
	int count = 0;
	for (int i = 0; i < len; i++){
		if (Decide(&Get_Date(Arr[i].date), &ref))
			count++;
	}
	return count;
}
int Decide(struct date *To_compare, struct date *Ref){
	//check year
	if (To_compare->year > Ref->year) return 1;
	else if (To_compare->year < Ref->year) return 0;

	// check month
	if (To_compare->month > Ref->month) return 1;
	else if (To_compare->month < Ref->month) return 0;

	//check day
	if (To_compare->day > Ref->day) return 1;
	else if (To_compare->day < Ref->day) return 0;

	//default
	return 0;
}
struct date Get_Date(char *d){
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