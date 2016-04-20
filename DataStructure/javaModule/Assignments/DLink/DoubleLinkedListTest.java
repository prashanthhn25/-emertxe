public class DoubleLinkedListTest
{

	public static void main(String[] args)
	{
        
		//creates head and tail = null
		DoubleLinkedList dlist = new DoubleLinkedList();
		
		dlist.addAtLast(10);
        dlist.addAtLast(20);
        dlist.addAtLast(30);
        dlist.addAtLast(40);
        dlist.printList();
        
        dlist.addAtFirst(60);
        dlist.addAtFirst(40);
        dlist.addAtFirst(50);
        dlist.printList();
		
		dlist.deleteFirst();
		dlist.printList();
		
        dlist.deleteElement(40);
        dlist.printList();
        dlist.deleteList();
        dlist.printList();
		
	}

}
