/*
OVERVIEW: Given an array where every element occurs three times, except one element which occurs only
once. Find the element that occurs once.
E.g.: Input: arr = 12, 1, 12, 3, 12, 1, 1, 2, 3, 3
ouput: 2

INPUTS: Integer array and length of the array.

OUTPUT: Element that occurs only once.

ERROR CASES: Return -1 for invalid inputs.

NOTES:
*/

#include <stdio.h>
#include<malloc.h>
struct node
{
	int value;
	int count;
	node* left;
	node* right;
};
struct node* insert(struct node* r, int data)
{
	if (r == NULL)
	{
		r = (struct node*) malloc(sizeof(struct node));
		r->count = 1;
		r->value = data;
		r->left = NULL;
		r->right = NULL;
	}
	else if (data == r->value){
		r->count++;
		return r;
	}
	else if (data < r->value){
		r->left = insert(r->left, data);
	}
	else {
		r->right = insert(r->right, data);
	}
	return r;

}
void Find(struct node* r, int *result)
{

	if (r != NULL){
		if (r->count == 1) *result = r->value;

		Find(r->left, result);
		Find(r->right, result);
	}
}
int findSingleOccurenceNumber(int *A, int len) {

	//init checking
	if (A == NULL) return -1;
	if (len < 0) return -1;

	struct node* root;
	root = NULL;
	int result = 0;

	for (int i = 0; i < len; i++) {
		root = insert(root, A[i]);
	}

	Find(root, &result);

	return result;

}