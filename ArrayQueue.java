import java.util.*;
import java.io.*;

public class ArrayQueue<E> {

    public static final int CAPACITY = 10;  // default queue capacity
    private E[] Q;                          // E array used to implement the queue
    private int n;                          // actual capacity of queue
    private int front;                      // index for the top of queue
    private int rear;                       // rear of the queue
    private int size;                       // size of the queue


    public ArrayQueue(){this(CAPACITY);}

    @SuppressWarnings("unchecked")
    public ArrayQueue(int capacity){
        n = capacity;
        Q = (E[]) new Object [n];
        front = rear = size = 0;
    }
    //
    // NOTE: java does not allow creation of array with parametrised type!
    //

    public int size(){return size;}


    public boolean isEmpty(){return (size == 0);}


    public E front() throws ArrayQueueException {
      if(isEmpty()) throw new ArrayQueueException("Queue underflow");        // checks if the queue is empty before returning the object
      return Q[front];
    }


    public void enqueue(E element) throws ArrayQueueException {

    if(rear == front && !isEmpty()) throw new ArrayQueueException("Queue overflow");
    size ++;
    Q[rear] = element;        //the rear is pointing to the place after the last element so first add the element at the back of the queue and then move the pointer
    rear = (rear + 1 )%n;        //make sure the pointer loops around the array as to not get an index error
    }




    public E dequeue() throws ArrayQueueException {

    if(isEmpty()) throw new ArrayQueueException("Queue underflow");

    E elem = Q[front];
    size --;                //decrease the size
    front = (front + 1)%n;    //very similar to enqueue() but here we have to store the element in a temporary variable as to return it after moving the pointer.
    return elem;

    }


    public String toString(){
    String str = "[";
    boolean override = (size ==n);        //the reason this var is here is to tell the loop to execute one first pass when the queue is full as when all the array slota are full, the front and rear are equal and confuses the for loop below with the % opperator. This var only returns true when the array is full and returns to false after the first pass of the loop as to not run for ever.
    for(int i = front;(i != rear || override); i =(i+1)%n){
    override = false;
    str += Q[i] + ",";                //the rest of the function is pretty self explanatory, cycle through the elements in the queue (taking into account the looping of elements with the % operator) and then add them to the string with a comma after
    }
    if (str != "[") str = str.substring(0, str.length() - 1);        //remove the last character of the string, which will be a comma so the format is correct
    return str + "]";
    }
    
}
