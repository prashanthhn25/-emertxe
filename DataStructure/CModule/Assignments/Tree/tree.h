#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAILURE -1
#define NOELEMENT -2
#define DUPLICATE -3

typedef int data_t;

typedef struct treenode
{
	struct treenode *left;
	data_t data;
	struct treenode *right;
}TreeLink;

int insert_BST(TreeLink **, data_t);
void inorder_Traverse(TreeLink * root);
void preorder_Traverse(TreeLink * root);
void postorder_Traverse(TreeLink * root);

