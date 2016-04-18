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
	
	//override: method to delete Node from the last of the List
	public void deleteLast()
	{
		//take a local reference of head
		Node temp = head;
		//if empty list
        if (head == null)
        {
            System.out.println("List is Empty");
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
				while(temp.getLink != null)
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
