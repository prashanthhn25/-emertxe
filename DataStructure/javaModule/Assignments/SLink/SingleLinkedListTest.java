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
        slist.addAtFirst(60);
        slist.addAtFirst(40);
        slist.addAtFirst(50);
        slist.printList();
		
		slist.deleteFirst();
		slist.printList();
        
		slist.deleteLast();
		slist.printList();
		
        slist.deleteElement(30);
        slist.printList();
        slist.deleteList();
        slist.printList();
		
	}

}
