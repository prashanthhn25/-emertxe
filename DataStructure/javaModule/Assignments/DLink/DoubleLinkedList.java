public class DoubleLinkedList implements DoubleLink
{
	//reference to head
	protected DNode head;
	
	//constructor
	public DoubleLinkedList()
	{
		//initially head is null
		head = null;
	}

	//override: method to add newNode at the end of the List
	public void addAtLast(Object _data)
	{
		//create new node with given data
		DNode newNode = new DNode(_data);
        
        //keep a local reference to th head for iteration
        DNode temp = head;
        
        //if empty list
		if (head == null)
		{
            head = newNode;
		}
		else
		{
			//iterate till the last node
            while(temp.getNext() != null)
            {
                temp = temp.getNext();
            }
            //add the new node
            temp.setNext(newNode);
            newNode.setPrev(temp);
		}
		
	}	

    //override: method to add newNode at the first of the List
    public void addAtFirst(Object _data)
    {
        //create new node with given data
        DNode newNode = new DNode(_data);
        
        //if empty list
        if (head == null)
        {
            head = newNode;
        }
        else
        {
            //establish links between newNode + first
            head.setPrev(newNode);
            newNode.setNext(head);
            //update the list's first node to newNode
            head = newNode;
        
        }
    }
	
	//override: method to delete Node from the first of the List
	public void deleteFirst()
	{
        
        //if empty list
        if (head == null)
        {
            System.out.println("List is empty");
            return;
        }
        
        //check for if list has only one node
        if (head.getNext() == null)
        {
            head = null;
        }
        //check for multi nodes
        else
        {
            //set head to next node
            head = head.getNext();
            //unlink the first node and set head -prev to null
            head.setPrev(null);
        }
        
	}	
	
	//override: method to delete Node from the last of the List
	public void deleteLast()
	{
        //keep a local reference to the head for iteration
        DNode temp = head;
        
        //if empty list
        if (head == null)
        {
            System.out.println("List is empty");
            return;
        }
        
        //check for if list has only one node
        if (head.getNext() == null)
        {
            head = null;
        }
        //check for multi nodes
        else
        {
            //iterate till the last node
            while(temp.getNext() != null)
            {
                temp = temp.getNext();
            }
            // update last - 1's next link to null
            temp.getPrev().setNext(null);
            temp = null;
            
        }
        
	}
    
    //override: Methhd to delete the element if present
    public void deleteElement(Object _data)
    {
        //keep a local reference to the head for iteration
        DNode temp = head;
        DNode temp2;
        
        //if empty list
        if (head == null)
        {
            System.out.println("List is empty");
            return;
        }
        //check for if list has only one node
        if (head.getNext() == null)
        {
            if (head.getData() == _data)
            {
                head = null;
                return;
            }
            else
            {
                System.out.println("No such element");
                return;
            }
        }
        //check for multi nodes
        else
        {
            //If the element is in the head then check for next values
            if (head.getData() == _data)
            {
                //update the head to next value
                head = head.getNext();
                //unlink the previous node and free
                head.getPrev().setNext(null);
                temp2 = head.getPrev();
                temp2 = null;
            }
            //iterate till the last Node
            else
            {
                while(temp != null)
                {
                    // check if next node is given element
                    if (temp.getData() != _data)
                    {
                        //if no element is found at all
                        if (temp.getNext() == null)
                        {
                            System.out.println("No such element");
                            return;
                        }
                    }
                    else
                    {
                        //element is present
                        break;
                    }
                    temp = temp.getNext();
                }
                //check when element is end node
                if (temp.getNext() == null)
                {
                    //unlink the node
                    temp.getPrev().setNext(null);
                    temp = null;
                }
                //check when element in the middle
                else
                {
                    //update that node's link, free the node that contains element
                    temp.getPrev().setNext(temp.getNext());
                    temp.getNext().setPrev(temp.getPrev());
                    //unlink the node that has element and free
                    temp.setPrev(null);
                    temp.setNext(null);
                    temp = null;
                }
            }
        }

    }
    
    //override: method to delete all Nodes from the List
    public void deleteList()
    {
        //keep a local reference to the head for iteration
        DNode temp = head;
        DNode temp2;
        
        //if empty list
        if (head == null)
        {
            System.out.println("List is empty");
            return;
        }
        else
        {
            //iterate through the list and delete from the head till the end
            while(temp.getNext() != null)
            {
                //temp is referenced to next node
                temp = temp.getNext();
                //unlink the previous node from the list
                temp.getPrev().setNext(null);
                //unreference the freed node
                temp2 = temp.getPrev();
                temp2 = null;
            }
            head = null;
        }
        
    }
    
	
	//override: method to print the list
	public void printList()
	{
        //keep a local reference to the head for iteration
		DNode temp = head;
        
		while(temp != null)
		{
			System.out.print( temp.getData() + " ");
            temp = temp.getNext();
		}
        System.out.println( " ");
	} 		
}	
