#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include"..\Rest\Order.h"
#include <iostream>
using namespace std;
template <typename T>
class LinkedList
{
protected :
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;	//Number of nodes in the list
public:


	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////

	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	bool isEmpty() {
		if (Head == nullptr) return true; 
		return false; 
	}
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;

	}
	////////////////////////////////////////////////////////////////////////
	/*template<typename T>
	void insertpri( T &value,int pri) {
		Node<T>* node = new Node<T>;
		node->setItem(value);
		node->setKey(pri);
		Node<T>* p = Head;
		while (p->getNext() != nullptr &&
			p->getNext()->getKey() > node->getKey())
		{
			p = p->getNext();
		}
		node->setNext(p->getNext());
		p->setNext(node);
	}*/


	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		count = 0;
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions
	T Getkth(int k) {
		Node<T>* p = Head;
		if (k == 0) return Head->getItem();
		for (int i = 0; i < k; i++) {
			p = p->getNext();
		}
		T m = p->getItem();
			return m;
	}

	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T &data) {

		if (Head == nullptr) {
			InsertBeg(data);
			return;
		}
		else {
			Node<T> *p = Head;
			while (p->getNext()) {
				p = p->getNext();
			}
			Node<T> *R = new Node<T>(data);
			p->setNext(R);
			count++;
			return;

		}
	}
	//inserts a new node at end if the list
	
	T* toArray(int& count)
	{
		count = 0;

		if (!Head)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = Head;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = Head;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
		bool Find(int Key,Node<T>* r) {
			Node<T> *p = Head;
			while (p) {
				if (*(p->getItem()) == Key) {
					cout << "Found the element " << Key << endl;
					r = p;
					return true;
				}
				p = p->getNext();
			}
			cout << "\nElement " << Key << " not found" << endl;
			return false;
		}


		/*bool addpri(Node<T> it,int Key) {
			Node<T> *p = Head;
			while (p) {
				if (p->getKey() == Key) {
					
					return true;
				}
				p = p->getNext();
			}
			cout << "\nElement " << Key << " not found" << endl;
			return false;
		}*/
		

		//[3]CountOccurance
		//returns how many times a certain value appeared in the list
		int CountOccurance(const T &value) {
			int occs = 0;
			Node<T> *p = Head;
			while (p) {
				if (p->getItem() == value) {
					occs++;
				}
				p = p->getNext();
			}
			cout << "\nElement " << value << " was found " << occs << " times" << endl;
			return occs;
		}

		//[4] DeleteFirst
		//Deletes the first node in the list
		void DeleteFirst() {
			cout << "\nDeleting the first element" << endl;
			if (Head) {
				Node<T> *p = Head->getNext();
				delete Head;
				Head = p;
				count--;
			}
			return;
		}


		//[5] DeleteLast
		//Deletes the last node in the list
		void DeleteLast() {
			cout << "\nDeleting the last element" << endl;
			if (Head == nullptr) {
				return;
			}
			else if (Head->getNext() == nullptr) {
				DeleteFirst();
				return;
			}
			else {
				Node<T> *p = Head;
				Node<T> *q = p->getNext();
				while (q->getNext()) {
					p = q;
					q = p->getNext();
				}
				delete q;
				p->setNext(nullptr);
				count--;
				return;

			}
		}

		//[6] DeleteNode
		//deletes the first node with the given value (if found) and returns true
		//if not found, returns false
		//Note: List is not sorted
		bool DeleteNode(const T &value) {
			cout << "\nDeleting the element " << value << endl;
			if (Head == nullptr) {
				return false;
			}

			if (Head->getItem() == value) {
				DeleteFirst();
				return true;
			}
			Node<T> *p = Head;
			Node<T> *q = p->getNext();

			while (q) {
				if (q->getItem() == value) {
					p->setNext(q->getNext());
					delete q;
					count--;
					return true;
				}
				p = q;
				q = p->getNext();
			}
			return false;
		}

		//[7] DeleteNodes
		//deletes ALL node with the given value (if found) and returns true
		//if not found, returns false
		//Note: List is not sorted
		bool DeleteNodes(const T &value) {
			cout << "\nDeleting all the elements of value " << value << endl;
			if (Head == nullptr) { return false; }
			bool flag = false;
			while (Head->getItem() == value) {
				DeleteFirst();
				flag = true;
			}
			Node<T>* p = Head;
			while (p->getNext()) {
				if ((p->getNext())->getItem() == value) {
					Node<T>* R = (p->getNext())->getNext();
					delete p->getNext();
					p->setNext(R);
					flag = true;
					count--;

				}
				else {
					p = p->getNext();
				}
			}
			return flag;
		}


		//[8]Merge
		//Merges the current list to another list L by making the last Node in the current list 
		//point to the first Node in list L
		Node<T>* getHead() const {
			return Head;
		}

		int getCount() {
			return count;
		}

	};
#endif	
