public class DNode
{
	//Object to save data
	protected Object data;

	//reference to the next node
	protected DNode next;

    //reference to the prev node
    protected DNode prev;
    
	//Node Constructor
 	public DNode()
    {
        data = 0;
        next = null;
        prev = null;
    }
	
    //for New Node
	public DNode(Object _data)
	{
		data = _data;
		next = null;
        prev = null;
	}
	//for New Node with links
	public DNode(Object _data, DNode _next, DNode _prev)
	{
		data = _data;
		next = _next;
        prev = _prev;
	}

	//setters and getters
	public Object getData()
	{
		return data;
	}

	public DNode getNext()
	{
		return next;
	}
	
    public DNode getPrev()
    {
        return prev;
    }
    
	public void setData(Object _data)
	{
		data = _data;
	}

	public void setNext(DNode _next)
	{
		next = _next;
	}
    
    public void setPrev(DNode _prev)
    {
        prev = _prev;
    }
}
