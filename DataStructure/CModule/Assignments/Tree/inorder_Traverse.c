#include "tree.h"

void inorder_Traverse(TreeLink * root)
{
	
	//print data while inorder Traversing
	if(root)
	{
		inorder_Traverse(root -> left);
		printf("%d ", root -> data);
		inorder_Traverse(root -> right);
	}
}
