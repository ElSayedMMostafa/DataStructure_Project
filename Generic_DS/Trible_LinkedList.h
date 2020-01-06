#pragma once
#include "LinkedList.h"
#include "Trible.h"
#include <cstdlib>
class Trible_LinkedList : public LinkedList<Trible> 
{
public:
	Trible_LinkedList() {
	}

	bool check_and_extract(int current, Trible& tt) { //To use it to get out a trible if its finished.
		if (this->isEmpty()) return false;
		
			if (Head->getItem() == current) {// In Trible class, I made the operator overloading
				tt = Head->getItem();
				// delete the node
				Head = Head->getNext();
				count--;
				return true;
			}
		
		return false;
	}

	// insertion of (order* - cook* -time)Trible based of the time in ascending order 
	bool insert_time_Sorted( Trible& value) {
		// Empty list case //
		if (Head == nullptr) {
			InsertBeg(value);
			return true;
		}
		// Insert beginning case //
		if (Head->getItem() > value) {
			InsertBeg(value);
			return true;
		}
		if (Head->getItem() == value) {
			InsertBeg(value);
			return true;
		}
		// Single node case //
		if (Head->getNext() == nullptr) {
			if (Head->getItem() < value) {
				InsertEnd(value);
				return true;
			}
			
		}
		// General case //
		Node<Trible>* p = Head;
		Node<Trible>* q = p->getNext();
		while (q->getItem() < value) {
			if (q->getNext() == nullptr) {
				InsertEnd(value);
				return true;
			}
			p = q;
			q = q->getNext();

		}
	
		Node<Trible>* newNode = new Node<Trible>;
		newNode->setItem(value);
		newNode->setNext(q);
		p->setNext(newNode);
		count++;
		return true;

	}

	void print_triple() {
		Node<Trible>* p = Head;
		int n = 0;
		while (p) {
			cout << "[ t =" << p->getItem().getTime() << ", C=" << p->getItem().getCook()->GetID() << ", O=" << p->getItem().getOrder()->GetID() << " ] &";
			p = p->getNext();
			n++;
			if (n % 3) {
				cout << "\n";
			}
		}
		cout << "\n";
	}



	void FinishOrder(int& N_Done_Orders,Queue<Order*>& done_orders, Cooks_LinkedList &VIPCooks ,Cooks_LinkedList& NormalCooks,Cooks_LinkedList& VeganCooks,Queue<Cook*>& B_cooks ,int& time)
	{Trible t; Cook* finished_Co; Order* finished_Or;
		while (this->check_and_extract(time, t)) {
			finished_Co = t.getCook();
			// Propability to get injuried
			int val = rand() % 7;
			if (val == 5) {
				cout << "\n The cook whose ID is: " << finished_Co->GetID() << " is injuried" << endl;
				cout << "Press 1 to give him rest otherwise continue with less speed: ";
				cin >> val;
				if (val == 1) {
					finished_Co->getInjuried(true,time);
					B_cooks.enqueue(finished_Co);
				}
				else  finished_Co->getInjuried(false);
			}
			finished_Or = t.getOrder();
			finished_Or->set_FT(time);
			done_orders.enqueue(finished_Or);
			N_Done_Orders++;
			if (finished_Co->Check4Break(time)) B_cooks.enqueue(finished_Co);
			else
			{
				if (finished_Co->GetType() == TYPE_NRM) {
					NormalCooks.enqueue(finished_Co);
				}
				else if (finished_Co->GetType() == TYPE_VIP) {
					VIPCooks.enqueue(finished_Co);
				}
				else {
					VeganCooks.enqueue(finished_Co);
				}

			}
		}
	}
};
