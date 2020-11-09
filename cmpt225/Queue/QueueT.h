#pragma once
#include<cstdlib>
#include<stdexcept>
#include<iostream>
using namespace std;

//Node class
template <class T>
class  NodeT{
    public:
        //Attributes
        T data;
        NodeT<T>* next;
        //consrtuctors and destructors
        NodeT(T value, NodeT<T>* nextNode): data(value), next(nextNode){};
        NodeT(T value): data(value), next(NULL){};
        ~ NodeT(){};
};
// Queue class
template <class T>
class QueueT{
    private:
        /* data */
        NodeT<T>* front;
        NodeT<T>* back;
        int size;
    public:
        // default constructor
        QueueT();
        // copy constructor
        QueueT(const QueueT& qt);
        // destructor
        ~QueueT();

        // accessor 
        // get the front pointer of the QueueT
        NodeT<T>* getFront() const;
        // get the back pointer of the QueueT
        NodeT<T>* getBack() const;
        // returns the number of items stored in the QueueT
        int getSize() const;

        // mutator
        // overload operator
        QueueT<T>& operator= (const QueueT<T>& qt);
        // insert value at the back of QueueT
        void enqueue (T value);
        // remove and return the value at the front of QueueT
        T dequeue ();
        // prints the contents of the QueueT, one value per line, from front to back
        void print() const;
        //returns true if the QueueT is empty, false otherwise
        bool empty();
        // adds the first n values stored in its QueueT parameter 
        // to the end of the calling object, the resulting QueueT
        // therefore contains its original content
        void concatenate( QueueT<T>& qt, int n);
        // merge calling object and parameter, return a QueueT object
        QueueT<T> merge(const QueueT<T>& qt );


        // helper
        void copyQueue(const QueueT<T>&qt);
        void deleteQueue();
};
// default constructor
// PARAM:
// PRE:
// POST: Creates an empty list 
template <class T>
QueueT<T>::QueueT(){
    front = nullptr;
    back = nullptr;
    size = 0;
}
// copy constructor
// PARAM: the QueueT qt to be copied
// PRE:
// POST: Creates an QueueT 
template <class T>
QueueT<T>::QueueT(const QueueT& qt){
    copyQueue(qt);
}
// destructor
// PARAM:
// PRE:
// POST: clear the QueueT 
template <class T>
QueueT<T>::~QueueT(){
    deleteQueue();
}
//get front pointer 
// PARAM:
// PRE:
// POST: return the address of front of QueueT
template <class T>
NodeT<T>* QueueT<T>::getFront() const{
    return front;
}
// get back pointer
// PARAM:
// PRE:
// POST: return the address of back of QueueT
template <class T>
NodeT<T>* QueueT<T>::getBack() const{
    return back;
}
// get the size of Queue
// PARAM:
// PRE:
// POST: return how many nodeT in QueueT
template <class T>
int QueueT<T>::getSize() const{
    return size;
}
// mutator
// overload operator=
// PARAM: QueueT qt to be deep copied
// PRE:
// POST: return the QueueT which is deep copied from qt
template <class T>
QueueT<T>& QueueT<T>::operator= (const QueueT& qt){
    if(this != &qt){
        deleteQueue();
        copyQueue(qt);
    }
    return *this;
}
// insert value at the back of QueueT
// PARAM: the value is going to be inserted
// PRE:
// POST: size get increment by 1 and the QueueT inserted a new NodeT at the end of QueueT
template <class T>
void QueueT<T>::enqueue (T value){
    if(front == nullptr){
        front = new NodeT<T>(value, nullptr);
        back = front;
        size++;
    }
    else{
        NodeT<T>* temp = back;
        temp->next = new NodeT<T>(value, nullptr);
        back = temp->next;
        size++;
    }
}
// remove and return the value at the front of QueueT
// PARAM:
// PRE: the QueueT can not be empty, otherwise return the runtime error
// POST: return the value at the front QueueT and the size of QueueT decrease by 1
template <class T>
T QueueT<T>::dequeue (){
    NodeT<T>* temp = front;
    T value;
    if (front != nullptr){
        front = temp->next;
        value = temp->data;
        delete temp;
        size = size-1;
        return value;
    }
    else{
        throw runtime_error("You can not dequeue because it is emptys");
    }
   

}
// prints out data in NodeT of QueueT Link list
// PARAM:
// PRE:
// POST: prints the contents of the QueueT, one value per line, from front to back
template <class T>
void QueueT<T>::print() const{
    NodeT<T>* temp = front;
    if( temp == nullptr)
        cout<<"The queue has nothing"<<endl;
    cout<<"{";
    while(temp != nullptr){
        cout<<temp->data;
        if(temp->next != nullptr)
            cout<<",";
        temp = temp->next;
    }
    cout<<"}"<<endl;

}
// check if the calling object is empty
// PARAM:
// PRE:
// POST: returns true if the QueueT is empty, false otherwise
template <class T>
bool QueueT<T>::empty(){
    return (size == 0); 
}


// adds the first n values stored in its QueueT parameter 
// to the end of the calling object, the resulting QueueT
// therefore contains its original content
// PARAM: A QueueT qt contains NodeT to be taken by the calling object, 
//        and n is the how many it's going to take
// PRE:
// POST: calling object extend the length of first n NodeT, and qt reduce the length of first n NodeT
template <class T>
void QueueT<T>::concatenate(QueueT& qt, int n){
    int i = 0;
    if( n > qt.getSize())
        throw runtime_error(" N is greater than the size of parameter qt");
    if(n <= 0)
        return;
    back->next = qt.getFront();
    NodeT<T>* temp = back;
    while ( i < n ){
        temp = temp->next;
        i++;
    }
    size+=n;
    qt.size = qt.size - n;
    qt.front = temp->next;
    temp->next = nullptr;
    back = temp;
}
// merge calling object and parameter, return a QueueT object
// PARAM: a const QueueT object 
// PRE:
// POST: return a QueueT object with starting calling object 
template <class T>
QueueT<T> QueueT<T>::merge(const QueueT& qt ){
    QueueT queue;
    if(front == nullptr && qt.getFront() == nullptr)
        return queue;
    else if(qt.front == nullptr)
        return *this;
    else if(front == nullptr)
        return qt;
    else{
        NodeT<T>* temp1=front;
        NodeT<T>* temp2=qt.front;

        while (temp1 != nullptr  ||  temp2 != nullptr){
            if(temp1 != nullptr  &&  temp2!= nullptr){
                queue.enqueue(temp1->data);
                queue.enqueue(temp2->data);
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            if(temp1 != nullptr){
                queue.enqueue(temp1->data);
                temp1 = temp1->next;
            }
            if(temp2 != nullptr){
                queue.enqueue(temp2->data);
                temp2 = temp2->next;
            }
        }  
        return queue;
    } 
}


// copy QueueT helper
// PARAM: a const QueueT reference parameter to be copied
// PRE:
// POST: calling object is deep copy of qt
template <class T>
void QueueT<T>::copyQueue(const QueueT&qt){
    front = nullptr;
    back = nullptr;
    size = 0;

    if(qt.front != nullptr){
        NodeT<T>* originalFront = qt.front;
        size = qt.size;

        NodeT<T>* copyFront = new NodeT<T>(originalFront->data, nullptr);
        front = copyFront;                                              
        originalFront = originalFront->next;
        
        while(originalFront != nullptr){
            copyFront->next = new NodeT<T>(originalFront->data, nullptr);
            copyFront = copyFront ->next;
            originalFront = originalFront->next;  
        }
        back = copyFront;
    }     
}
// delete the QueueT
// PARAM:
// PRE:
// POST: delete the QueueT 
template <class T>
void QueueT<T>::deleteQueue(){
    NodeT<T>* temp = front;
    
    while(temp != nullptr){
        temp = front->next;
        delete front;
        front = temp;
    }
    front = nullptr;
}