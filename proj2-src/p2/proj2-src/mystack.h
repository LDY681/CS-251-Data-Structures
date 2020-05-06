#ifndef MYSTACK_H
#define MYSTACK_H
#define MAX_SIZE 10000

template <class T>
class mystack{
	private:
		// Lets store our stack value into an array of type T
		T* stack;	//stack array
		int pos;
	public:
		mystack() {
			pos = 0;	//initialize pos to 0
			stack = new T[1000];	//initialize stack array 
		}
        void push(T x);
        T top();
        T pop();
        bool empty();
        int size();
};


template <class T>
void mystack<T>::push(T x) {
	stack[pos] = x;
	pos++;
}

template <class T>
T mystack<T>::top() {
	return stack[pos-1];
}

template <class T>
T mystack<T>::pop(){
	T popele = stack[pos - 1];
	pos--;
	return popele;
}

template <class T>
bool mystack<T>::empty() {
	return (pos == 0 ?1:0);	//return 1 if empty, 0 if not
}

template <class T>
int mystack<T>::size() {
	return pos;
}


#endif
