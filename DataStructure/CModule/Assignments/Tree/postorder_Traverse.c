#include "tree.h"

void postorder_Traverse(TreeLink * root)
{
	
	//print data while post order Traversing
	if(root)
	{
		postorder_Traverse(root -> left);		
		postorder_Traverse(root -> right);
		printf("%d ", root -> data);
		
	}
}
