import java.util.*;
import java.io.*;

public class QueueSort<E extends Comparable<E>> {

    private ArrayQueue<ArrayQueue<E>> Q;
    public static final int CAPACITY = 10;  // default queue capacity
    private int n;    
    private boolean trace;
	
    public QueueSort(){this(CAPACITY);}
	
    public QueueSort(int capacity){
	n = capacity;
	Q = new ArrayQueue<ArrayQueue<E>>(n);
    }

    private ArrayQueue<E> merge(ArrayQueue<E> q1,ArrayQueue<E> q2) throws ArrayQueueException {
    ArrayQueue<E> q3 = new ArrayQueue<E>(q1.size() + q2.size());		//create a new array queue with the correct size which will be the sum of the two smaller queues
	while (!q1.isEmpty() && !q2.isEmpty()) q3.enqueue((q1.front().compareTo(q2.front()) < 0) ? q1.dequeue() : q2.dequeue());	//this loop only runs if both queues have elememnts in them since that is the only situation where comparing is necessary
	while (!q1.isEmpty()) q3.enqueue(q1.dequeue());		//these next two loops run once one of the queues has no more elements and then the orderd contents are put into the third queue 
	while (!q2.isEmpty()) q3.enqueue(q2.dequeue());
	return q3;
    }
    //
    // IMPLEMENT ME
    // Take two sorted queues and merge them to produce a third
    // sorted queue
    //

    public void sort(){
	   while (Q.size() > 1){
		  Q.enqueue(merge(Q.dequeue(), Q.dequeue()));		//not much to explain, while there is more than one queue in Q, merge sort and add to Q
	   }
	   int i = Q.front().size();		//update the size
    }
    //
    // IMPLEMENT ME
    // given a queue Q of queues
    // (1) if Q is of size 1 deliver the first queue in Q
    // (2) if Q is of size 2 or more 
    //     - get the first and second queues off Q
    //     - merge these two queues to create a third queue
    //     - add the third queue to the queue
    //     - go back to (1)
    //

    public void add(E element){
        ArrayQueue<E> small = new ArrayQueue<E>(1);
        small.enqueue(element);	//comments below explain the functionality exactly
        Q.enqueue(small);
    }
    //
    // IMPLEMENT ME
    // create an ArrayQueue<E> that contains the element
    // enqueue it onto Q
    //
    
    public String toString(){return Q.toString();}

    public void trace(){trace = !trace;}

    public static void main(String[] args) throws IOException {
	Scanner sc = new Scanner(new File(args[0]));
	ArrayList<String> data = new ArrayList<String>();
	while (sc.hasNext()) data.add(sc.next());
	int n = data.size();
	QueueSort<String> QS = new QueueSort<String>(n);
	for (String s : data) QS.add(s);
	if (args.length > 1) QS.trace();
	QS.sort();
	System.out.println(QS);		//here i'm not too sure of the format for the output since there are no details about it in the notes so the "[[.........]]" is just a bi-product of the nested queues
    }
}
