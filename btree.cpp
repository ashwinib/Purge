#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include "btree.h"

#define RED 1
#define BLACK 0

using namespace std;
void LeftRotate(TreeNode *);
void RightRotate(TreeNode *);
void InsertFix(TreeNode *);
TreeNode *root , *nil;
void LeftRotate(TreeNode *x){
	//cout<<"\nLeftRotating";
	TreeNode *y;
	y = x->right;
	x->right =  y->left;
	y->left->parent = x;
	y->parent = x->parent; 
	if(x->parent == nil)
		root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else x->parent->right = y;
	y->left = x;
	x->parent = y;
}
void RightRotate(TreeNode *x){
	//cout<<"\nRightRotating";
	TreeNode *y;
	y = x->left;
	x->left = y->right;
	y->right->parent = x;

	//if(y->right != nil)
	y->parent = x->parent; 
	if(x->parent == nil)
		root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else x->parent->right = y;
	y->right = x;
	x->parent = y;	
}

void InsertFix(TreeNode *z){
	TreeNode *x,*y;
	//cout<<"\nInsertFixing";
	while(z->parent->color==RED){
		if(z->parent == z->parent->parent->left){
			y = z->parent->parent->right;
			if(y->color == RED){
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				if(z == z->parent->right){
					z= z->parent;
					LeftRotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				RightRotate(z->parent->parent);
				
			}
		}
		else{
			y = z->parent->parent->left;
			if(y->color == RED){
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else {
				if(z == z->parent->left){
					z= z->parent;
					RightRotate(z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				LeftRotate(z->parent->parent);
				
			}
		}
	}
	root->color = BLACK;
}

TreeNode *insertinRB(TreeNode *z){
	TreeNode *x,*y;
	//cout<<"\nInserting..";
	y = nil;
	x = root;
	//cout<<"\n\nRoot is :"<<x->entry;
	//cout<<"\nCHecking for :"<<z->entry;
	while(x != nil){
		y = x;
		//cout<<"\nInstead Found :"<<x->entry;
		if(z->entry == x->entry)//Return copy on duplicate
			return x;
		else if(z->entry > x->entry)
			//cout<<"\nMoving right";
			x=x->right;
		else x= x->left;
	}
	z->parent = y;
	if(y == nil)
		root= z;//cout<<"Setting root: " << z->entry;
	else if(z->entry < y->entry)
	 	y->left = z;
	else if(z->entry == y->entry)//Return copy on duplicate
		return y;
	else y->right = z;
	z->left = nil;
	z->right = nil;
	z->color = RED;
	InsertFix(z);
	return z;
}

void initRB(){
	nil = new TreeNode;
	nil->left = NULL;
	nil->right = NULL;
	nil->entry = "I am Nil";
	nil->color = BLACK;
	nil->parent = nil;
	root = nil;
}


