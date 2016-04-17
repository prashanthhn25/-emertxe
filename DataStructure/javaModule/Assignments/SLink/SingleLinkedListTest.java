public class SingleLinkedListTest
{

	public static void main(String[] args)
	{
        
		//creates head and tail = null
		SingleLinkedList slist = new SingleLinkedList();
		
		slist.addAtLast(10);
        slist.addAtLast(20);
        slist.addAtLast(30);
        slist.addAtLast(40);
		
        slist.printList();
        slist.addAtFirst(30);
        slist.addAtFirst(40);
        slist.printList();
	}

}
