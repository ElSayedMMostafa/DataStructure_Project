#pragma once
#include "LinkedList.h"
#include "Trible.h"

class Trible_LinkedList : public LinkedList<Trible> 
{
public:
	Trible_LinkedList() {
	}

	bool check_and_extract(int current,Trible tt) { //To use it to get out a trible if its finished.
		Node<Trible> *t = this->getHead();
		while (t != nullptr) {
			if (t->getItem() == current) // In Trible class, I made the operator overloading
				tt = t->getItem();
				// delete the node
			    DeleteFirst();
				return true;
		}
		return false;
	}
};
