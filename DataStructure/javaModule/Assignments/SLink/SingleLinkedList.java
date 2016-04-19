public class SingleLinkedList implements SingleLink
{
	//reference to head and tail
	protected Node head;
	protected Node tail;
    
	//constructor
	public SingleLinkedList()
	{
		//initially head and tail is null
		head = null;
		tail = null;
	}

	//override: method to add newNode at the end of the List
	public void addAtLast(Object _data)
	{
		//create new node
		Node newNode = new Node(_data);
        
        //if empty list
		if (head == null)
		{
            head = newNode;
			tail = head;
		}
		else
		{
			//establish link between last+newNode
			tail.setLink(newNode);
			//update tail
			tail = newNode;
		}
		
	}	

    //override: method to add newNode at the first of the List
    public void addAtFirst(Object _data)
    {
        //create new node
        Node newNode = new Node(_data);
        
        //if empty list
        if (head == null)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            //establish link between newNode+first
            newNode.setLink(head);
            //update head
            head = newNode;
        }
        
    }
	
	//override: method to delete Node from the first of the List
	public void deleteFirst()
	{
		//if empty list
        if (head == null)
        {
            System.out.println("List is Empty");
            return;
        }
		else
		{
			//Single node list
			if (head == tail)
			{	
				head = null;
				tail = null;
			}
			else
			{
				head = head.getLink();
			}	
		}
			
	}	
	
    //override: Methhd to delete the element if present
    public void deleteElement(Object _data)
    {
        //take a local reference of head
        Node temp = head;
        Node temp2;
        
        //if empty list
        if (head == null)
        {
            System.out.println("List is Empty");
            return;
        }
        else
        {
            //Single node list
            if (head == tail)
            {
                if (head.getData() == _data)
                {
                    head = null;
                    tail = null;
                }
                else
                {
                     System.out.println("No such Element");
                    return;
                }
            }
            else
            {
                //if element is head node
                if (head.getData() == _data)
                {
                    temp2 = head;
                    head = head.getLink();
                    temp2 = null;
                }
                else
                {
                    //in middle or end
                    while(temp.getLink() != null)
                    {
                        //check if next node is given element
                        if ((temp.getLink()).getData() != _data)
                        {
                            if (temp.getLink() == tail)
                            {
                                System.out.println("No such Element");
                                return;
                            }
                            temp = temp.getLink();
                        }
                        else
                        {
                            // if element is present break
                            break;
                        }
                    }
                    // take a local reference to the element node
                    temp2 = temp.getLink();
                    
                    // update that node's link, free the next node that contains element
                    temp.setLink(temp2.getLink());
                    temp2 = null;
                }
            }
        }
    }
    
	//override: method to delete Node from the last of the List
	public void deleteLast()
	{
		//take a local reference of head
		Node temp = head;
		//if empty list
        if (head == null)
        {
            System.out.println("List is Empty");
            return;
        }
		else
		{
			//Single node list
			if (head == tail)
			{	
				head = null;
				tail = null;
			}
			else
			{
				//iterate till tail - 1 node in the link
				while(temp.getLink() != tail )
				{
					temp = temp.getLink();
				}
				//update the temp link to null
				temp.setLink(null);
				//update tail value to this temp
				tail = temp;	
			}	
		}		
	}
    
    //override: method to delete all Nodes from the List
    public void deleteList()
    {
        Node temp = head;
        Node temp2;
        
        //if empty list
        if (head == null)
        {
            System.out.println("List is Empty");
            return;
        }
        else
        {
            //Single node list
            if (head == tail)
            {
                head = null;
                tail = null;
            }
            else
            {
                while(temp != null)
                {
                    temp2 = temp;
                    temp = temp.getLink();
                    temp2 = null;
                }
                head = null;
                tail = null;
            }
        }
        
    }	
    
	
	//override: method to print the list
	public void printList()
	{
		Node temp = head;
        
		while(temp != null)
		{
			System.out.print( temp.getData() + " ");
            temp = temp.getLink();
		}
        System.out.println( " ");
	} 		
}	
