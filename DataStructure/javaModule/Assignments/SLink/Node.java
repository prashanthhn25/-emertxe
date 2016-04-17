public class Node
{
	//Object to save data
	protected Object data;

	//reference to the next node /link
	protected Node link;

	//Node Constructor
 	public Node()
    {
            data = 0;
            link = null;
    }
	
    //for New Node
	public Node(Object _data)
	{
		data = _data;
		link = null;
	}
	//for New Node with link
	public Node(Object _data, Node _link)
	{
		data = _data;
		link = _link;
	}

	//setters and getters
	public Object getData()
	{
		return data;
	}

	public Node getLink()
	{
		return link;
	}
	
	public void setData(Object _data)
	{
		data = _data;
	}

	public void setLink(Node _link)
	{
		link = _link;
	} 
}
