#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;	//Number of nodes in the list
public:

	struct diction {
		T data;
		int rep;
	};

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
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		cout << "\nList has " << count << " nodes";
		cout << "\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;

	}
	////////////////////////////////////////////////////////////////////////
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

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key) {
		Node<T> *p = Head;
		while (p) {
			if (p->getItem() == Key) {
				cout << "Found the element " << Key << endl;
				return true;
			}
			p = p->getNext();
		}
		cout << "\nElement " << Key << " not found" << endl;
		return false;
	}

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

	void Merge(const LinkedList& L) {
		Node<T> *p = Head;
		if (Head == nullptr) {
			Head = L->getHead();
			return;
		}
		while (p->getNext()) {
			p = p->getNext();
		}
		p->setNext(L->getHead());
		count = count + L->getCount();
		return;
	}

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse() {
		cout << "\nReversing the list" << endl;
		if (Head == nullptr) { return; }
		Node<T>* p = Head;
		Node<T>* nextP = Head->getNext();
		Head->setNext(nullptr);
		while (nextP) {
			Node<T>* temp = nextP->getNext();
			nextP->setNext(p);
			p = nextP;
			nextP = temp;
		}
		Head = p;
		return;
	}

	//[10] Insert Kth
	void InsertKth(int index, T data) {
		if (index<1 || index > count) cout << "Beyond List Length!" << endl;
		else {
			Node<T>* p = Head;
			for (int i = 1; i < index; i++) {
				p = p->getNext();
			}
			p->setItem(data);
		}
	}

	//[11] InsertSorted 
	bool InsertSorted(LinkedList<T>* UL, T element) {
		Node<T>* nodey = UL->getHead();
		for (int i = 1; i < UL->count; i++) {
			if (element == nodey->getItem()) return false;
			else if (element < nodey->getItem()) {
				nodey->setItem(element);
				return true;
			}
			nodey = nodey->getNext();
		}
	}

	//[12] Remove Min 
	Node<T>* RemoveMin() {
		Node<T>* temp = Head;
		Node<T>* temp2 = NULL;
		T min = temp->getItem();
		for (int i = 1; i < count; i++) {
			if (temp->getItem() < min) {
				min = temp->getItem();
			}
			else {
				temp2 = temp;  temp = temp->getNext();
			}
			temp2->setNext(temp->getNext());
		}
		return temp;
	}
	// [13] Clone List  
	LinkedList<T> CloneList(LinkedList<T> userList) {
		LinkedList<T> newList;
		Node<T>* temp, temp2;
		temp2 = userList.getHead();
		for (int i = 1; i < userList.count; i++) {
			if (temp2->getNext() != NULL) {
				temp->setItem(temp2->getItem());
				temp->setNext(temp2->getNext());
				temp2 = temp2->getNext();
				temp = temp->getNext();
			}
		}
		newList = &temp;
		return newList;
	}

	//[14] Sign Split
	void SignSplit(LinkedList<T> userList, LinkedList<T> Lpos, LinkedList<T> Lneg) {
		Node<T>* temp, posTemp, negTemp;
		temp = userList.getHead();
		posTemp = Lpos->getHead();
		negTemp = Lneg->getHead();
		T data;
		for (int i = 1; i < userList.count; i++) {
			if (temp->getNext() != NULL) {
				data = temp->getItem();
				if (data > 0) {
					posTemp->setItem(data);
					posTemp->setNext(new Node<T>*);
					posTemp = posTemp->getNext();
					userList.DeleteNode(data);
				}
				else if (data < 0) {
					negTemp->setItem(data);
					negTemp->setNext(new Node<T>*);
					negTemp = negTemp->getNext();
					userList.DeleteNode(data);
				}
				temp = temp->getNext();
			}
		}
	}

	//[15] Merge Sorted
	LinkedList<T> MergeSorted(LinkedList<T> sorted1, LinkedList<T> sorted2, LinkedList<T> newSorted) {
		Node<T>* temp1, temp2, newtemp;
		temp1 = sorted1.getHead();
		temp2 = sorted2.getHead();
		newtemp = newSorted.getHead();
		T data1, data2;
		while (temp1->getNext() != NULL && temp2->getNext() != NULL) {
			data1 = temp1->getItem();
			data2 = temp2->getItem();
			if (data1 >= data2) {
				newtemp->setItem(data1);
				temp1 = temp1->getNext();
			}
			else {
				newtemp->setItem(data2);
				temp2 = temp2->getNext();
			}
			newtemp->setNext(new Node<T>*);
			newtemp = newtemp->getNext();
		}
		// after we finish the while loop, I put the remained data in the new linkedList
		if (temp1->getNext() == NULL) {
			newSorted.Merge(temp2);
		}
		else if (temp2->getNext() == NULL) {
			newSorted.Merge(temp1);
		}
		return newSorted;
	}

	//[16] Sum Lists
	LinkedList<T> SumLists(LinkedList<T> list1, LinkedList<T> list2) {
		LinkedList<T> newList;
		Node<T>* temp;
		newList.Head = temp;

		if (list1.getCount() != list2.getCount()) return NULL; //If the 2 lists are not the same size
		Node<T>* temp1 = list1.getHead(); Node<T>* temp2 = list2.getHead();
		for (int i = 1; i < list1.getCount(); i++) {
			temp->setItem(temp1->getItem() + temp2->getItem());
			temp->setNext(new Node<T>*);
			temp = temp->getNext();
			temp1 = temp1->getNext(); temp2 = temp2->getNext();
		}
		return newList;
	}

	//[17] Reorder_X
	void Reorderd_X(LinkedList<T> list, T X) {
		Node<T>* temp = list.getHead();
		T data;
		for (int i = 1; i < list.getCount(); i++) {
			data = temp->getItem();
			if (data <= X) {
				list.DeleteNode(data);
				list.InsertBeg(data);
			}

		}
	}

	//[18] ShiftLargest
	void Shiftlargest() {
		Node<T>* temp1 = Head;
		Node<T>* temp2 = temp1->getNext();
		Node<T>* temp3;
		int counter = 1;
		while (counter - count < 1 && temp2 != NULL)
		{
			if (temp1->getItem() > temp2->getItem()) { //SWAP
				temp3 = temp1;
				temp1->setNext(temp2->getNext());
				temp2 = temp3;
				temp2->setNext(temp1);
			}
			else {
				temp1 = temp2;
				temp2 = temp2->getNext();
			}
			counter++;
		}
	}

	//[19] Make Dictionary
	void makeDictionary(LinkedList<diction> dictionList) {
		//Node<diction>* dictionHead = dictionList.getHead();
		Node<diction>* temp_pointer = dictionList.getHead();
		int counter;
		diction temp_diction;
		T item;
		Node<T>* temp = Head;
		for (int i = 1; i < count; i++) {
			item = temp->getItem();
			counter = this->CountOccurance(item);
			temp_diction = { item,counter };
			temp_pointer->setItem(temp_diction);
			temp_pointer->setNext(new Node<diction>*);
			temp_pointer = temp_pointer->getNext();
		}
	}

	//[20] Remove Duplicates
	void remove_duplicates() {
		Node<T>* temp1, temp2, temp3;
		temp1 = Head;
		temp2 = temp1;
		int f = 0;
		T item;
		for (i = 1; i <= count; i++) {
			for (int j = 1; j <= count; j++) {
				item = temp1->getItem();
				if (item == temp2->getNext()->getItem()) {
					temp2->setNext(temp2->getNext()->getNext()); //Delete the deuplicated Node
					f++;
				}
				temp2 = temp2->getNext();
			}
			count = count - f;
			temp1 = temp1->getNext();
		}
	}
};

#endif	
