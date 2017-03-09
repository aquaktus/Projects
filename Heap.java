
public class Heap <E extends Comparable<E>> {

    private Object H[];   // contains the objects in the heap
    private int last;     // index of last element in heap
    private int capacity; // max number of elements in heap

    public Heap(int n){
	capacity = n;
	H        = new Object[capacity+1];
	last     = 0;
    }
    //
    // create a heap with capacity n
    // NOTE: H is an array of objects
    //       must use casting when delivering the minimum
    //       See min() below.
    //       This must also be done in removeMin()
    //

    public Heap(){this(15);}
    //
    // by default, create a new heap with capacity 15
    //

    @SuppressWarnings("unchecked")
    private int compare(Object x,Object y){return ((E)x).compareTo((E)y);}

    public int size(){return last;}
    //
    // returns the number of elements in the heap
    //

    public boolean isEmpty(){return last==0;}
    //
    // is the heap empty?
    //

    @SuppressWarnings("unchecked")
    public E min() throws HeapException {
	if (isEmpty()) throw new HeapException("underflow");
	return (E) H[1];
    }
    //
    // returns element with smallest key, without removal
    // NOTE: must use casting to class (E)
    //


    public void insert(E e) throws HeapException {
      if (last == capacity) throw new HeapException("overflow");
      last++;
      H[last] = e;
      if(last > 1) upHeapBubble();
    }
  

    private void upHeapBubble(){
      int index = last;
      while (index > 1){
        int parent = index/2;
        if (compare(H[index],H[parent]) >= 0) return ;
        swap(index,parent);
        index = parent;

      }
    }

    private void swap(int i, int j){
      Object temp = H[i];
      H[i] = H[j];
      H[j] = temp;
    }

    @SuppressWarnings("unchecked")
    public E removeMin() throws HeapException {
      if (isEmpty()) throw new HeapException("underflow");
      E value = (E) H[1];
      H[1] = H[last];
      last--;
      dowmHeapBubble();
    	return value;
    }


    public void dowmHeapBubble(){
      int index = 1;
      while (true){
        int child = index*2;
        if (!hasLeft(index)) return;
        if (hasRight(index)) if (compare(H[child],H[child + 1]) >= 0) child = child + 1;
        if (compare(H[child],H[index]) >= 0) return;
        swap(index,child);
        index = child;
      }
    }

    public void isHeap(){
      if (isEmpty()) return;

    }

    private boolean hasLeft(int parent){
      return (parent*2 <= last);
    }

    private boolean hasRight(int parent){
      return (parent*2 + 1 <= last);
    }

    public String toString(){
      String str = "[";
      for (int i = 1; i <= last; i++) {
        str += H[i].toString() + ",";
      }
      if (str != "[") str = str.substring(0, str.length() - 1);
	return str + "]";
    }
    //
    // outputs the entries in H in the order H[1] to H[last]
    // in same style as used in ArrayQueue
    //
    //

}
