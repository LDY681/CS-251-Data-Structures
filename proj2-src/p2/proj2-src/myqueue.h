#ifndef MYQUEUE_H
#define MYQUEUE_H
#define MAX_SIZE 10000

template <class T>
class myqueue{
  private:
		int ffront;	//index of the front element
		int rear;	//index immediately past the rear element
		int ssize;	//number of items in the queue
		T *array;	//array to store elements
  public:
        myqueue(){
		ffront = 0;
		rear = 0;
		ssize = 0;
		array = new T[1000];
	};
    	void enqueue(T x);
    	T front();
        T dequeue();
    	bool empty();
        int size();

};

//void myqueue<T>::enqueue(T x)
//not void template<T> enqueue(T x)
//Be careful!
template <class T>
void myqueue<T>::enqueue(T x){	//insert at the end of queue
	array[rear] = x;
	rear++;
	ssize++;
}

template <class T>
T myqueue<T>::front(){
	return array[ffront];
}

//remove and return the element at the front of the queue
template <class T>
T myqueue<T>::dequeue(){
	int oldfront = ffront;
	ffront++;
	ssize--;
	return array[oldfront];	
}

template <class T>
bool myqueue<T>::empty(){	//Dont forget () parameter bracket after function
	return (ssize==0?true:false);
} 

template <class T>
int myqueue<T>::size(){
	return ssize;
} 
#endif
