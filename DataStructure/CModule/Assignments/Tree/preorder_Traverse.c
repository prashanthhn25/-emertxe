#include "tree.h"

void preorder_Traverse(TreeLink * root)
{
	
	//print data while pre order Traversing
	if(root)
	{
		printf("%d ", root -> data);
		preorder_Traverse(root -> left);		
		preorder_Traverse(root -> right);
	}
}
