#include "tree.h"

int main()
{
	int result, data;
	int choice, i = 0;
	char option;
	TreeLink * root = NULL;

	do
	{
	
	printf("Enter the option:\n");
	printf("1. insert BST\n");	
	printf("2. in order Traversal\n");	
	printf("3. pre order Traversal\n");	
	printf("4. post order Traversal\n");
	
	printf("Choice: ");
	scanf("%d", &choice);

	switch(choice)
	{
		case 1:
			printf("Enter the element to be inserted: ");
			scanf("%d", &data);
			result = insert_BST(&root, data);
			(result == SUCCESS)? printf("insert_BST SUCCESS\n"): printf("insert_BST FAILURE\n") ;
			if (result == DUPLICATE)
    			{
      			  	printf("Duplicate found\n");
    			}
				
			break;
		case 2:
			inorder_Traverse(root);	
			printf("\n");
			break;
		case 3: 
			preorder_Traverse(root);	
			printf("\n");	
			break;
		case 4: 
			postorder_Traverse(root);	
			printf("\n");	
			break;
		default:
			printf("Invalid entry.\n");
			break;
	}

	/* check for continue */
        printf("Continue (y/n): ");
        scanf("\n%c", &option);
        
        if ( option == 'y' )
        {
            continue;
        } else
        {
            break;
        }
        
    } while (1);
		
    return 0;
}
