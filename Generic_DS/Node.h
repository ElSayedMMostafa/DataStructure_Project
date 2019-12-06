
#ifndef __NODE_H_
#define __NODE_H_

template < typename T>
class Node
{
private :
	T item; // A data item
	Node<T>* next; // Pointer to next node
	int key;
public :
	Node();
	Node( const T & r_Item);	//passing by const ref.
	Node( const T & r_Item, Node<T>* nextNodePtr);
	Node(const T & r_Item, int k );	//passing by const ref.
	Node(const T & r_Item, Node<T>* nextNodePtr, int k);
	void setItem( const T & r_Item);
	void setKey(int k);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const ;
	int getKey() const;
	Node<T>* getNext() const ;
}; // end Node


template < typename T>
Node<T>::Node() 
{
	next = nullptr;
	key = 0;
} 

template < typename T>
Node<T>::Node( const T& r_Item)
{
	item = r_Item;
	next = nullptr;
	key = 0;
} 

template < typename T>
Node<T>::Node( const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
	key = 0;
}
template < typename T>
Node<T>::Node(const T& r_Item, int k)
{
	item = r_Item;
	key = k;
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr, int k)
{
	item = r_Item;
	next = nextNodePtr;
	key = k;
}
template < typename T>
void Node<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 
template < typename T>
void Node<T>::setKey(int k)
{
	key = k;
	
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
int Node<T>::getKey() const
{
	return key;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
} 



#endif