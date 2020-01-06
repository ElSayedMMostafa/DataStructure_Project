#pragma once
#include "LinkedList.h"
#include"..\Rest\Order.h"
#include"..\Rest\Cook.h"
#include"..\Generic_DS\Cooks_LinkedList.h"
#include"..\Generic_DS\Trible_LinkedList.h"


class Waiting_Orders_LinkedList : public LinkedList<Order*> {
	 
	int NumberOfAutoPromoted;
	

public :
	bool  reorder_Orders(int autoPro) {  //Sayed's Version
		//increase_waiting_time(); //Increase the waiting time for all the orders in the waiting order list
		int flag = 0;
		if (Head == nullptr) {
			return false;
		}

		if (Head->getItem()->reprioritize_Order(autoPro)) flag = 1;

		Node<Order*> *p = Head;
		Node<Order*> *q = p->getNext();
		while (q) {
			if (q->getItem()->reprioritize_Order(autoPro)) {
				p->setNext(q->getNext());
				count--;
				insert_priority_Sorted(q->getItem());
				flag = 1;
				NumberOfAutoPromoted++;
			}
			p = q;
			q = p->getNext();
		}

		if (flag == 0)	return false;
		return true;
	}

	Waiting_Orders_LinkedList() { NumberOfAutoPromoted = 0; 
	}
	void increase_waiting_time() {
		Node<Order*>* p = Head;
		while (p) {
			p->getItem()->increment_waiting_time();
			p = p->getNext();
		}
	}
	ORD_TYPE Frist_Order_Type() {
		return Head->getItem()->GetType();
	}

	// Insert Orders with respect to its priority 
	bool insert_priority_Sorted ( Order* const &value) {
		// Empty list case //
		

		if (Head == nullptr) {
			InsertBeg(value);
			
			return true;
		}

		if (value->GetPriority() == 0) {
			InsertEnd(value);
			
			return true;
		}
		// Insert beginning case //
		if (Head->getItem()->GetPriority() < value->GetPriority()) {
			InsertBeg(value);
			
			return true;
		}
		if (Head->getItem()->GetPriority() == value->GetPriority()) {
			InsertBeg(value);
			
			return true;
		}
		// Single node case //
		if (Head->getNext() == nullptr) {
			if (Head->getItem()->GetPriority() > value->GetPriority()) {
				InsertEnd(value);
				
				return true;
			}

		}
		// General case //
		Node<Order*>* p = Head;
		Node<Order*>* q = p->getNext();
		while (q->getItem()->GetPriority() > value->GetPriority()) {
			if (q->getNext() == nullptr) {
				InsertEnd(value);
				
				return true;
			}
			p = q;
			q = q->getNext();

		}
		
		Node<Order*>* newNode = new Node<Order*>;
		newNode->setItem(value);
		newNode->setNext(q);
		p->setNext(newNode);
		
		count++;
		return true;

	}


	bool Swap_frist_Normal() {
		Node<Order*> *p = Head;
		Node<Order*> *q = p->getNext();
		while (q) {
			if ((q->getItem()->GetType() == TYPE_NRM)|| (q->getItem()->GetType() == TYPE_VIP)) {
				 p->setNext(q->getNext());
				count--;
				InsertBeg(q->getItem());
				return true;
			}
		//	p = q;
		//	q = p->getNext();	//These 2 lines make errors
			p = q;		//Sayed's version
			if (p) q = p->getNext();
			else break;
		}
		return false;
	}
	bool Swap_frist_Vegan() {
		Node<Order*> *p = Head;
		Node<Order*> *q = p->getNext();
		while (q) {
			if ((q->getItem()->GetType() == TYPE_VEG)) {
				p->setNext(q->getNext());
				count--;
				InsertBeg(q->getItem());
				return true;
			}
		//	p = q;
		//	q = p->getNext(); //These 2 lines make errors

			p = q;		//Sayed's version
			if (p) q = p->getNext();
			else break;
		}
		return false;
	}
	bool  Extract_First(Order* &d) {
		
		if (Head) {
			Node<Order*> *p = Head->getNext();
			d = Head->getItem();
			Head = p;
			count--;
			return true;
		}
		return false ;
	}


	bool DeleteOrder(int & ID   ) {
		if (Head == nullptr) {
			return false;
		}

		if (Head->getItem()->GetID() == ID) {
		
			DeleteFirst();
			return true;
		}
		Node<Order*> *p = Head;
		Node<Order*> *q = p->getNext();

		while (q) {
			if (q->getItem()->GetID() == ID) {
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

	bool PromoteOrder(int & ID,int extra) {
		if (Head == nullptr) {
			return false;
		}

		if (Head->getItem()->GetID() == ID) {

			Head->getItem()->Promote_To_Vip(extra);
			return true;
		}
		Node<Order*> *p = Head;
		Node<Order*> *q = p->getNext();
		Order* ord ;
		while (q) {
			if (q->getItem()->GetID() == ID) {
				p->setNext(q->getNext());
				count--;
				q->getItem()->Promote_To_Vip(extra);
				q->setNext(nullptr);
				ord = q->getItem();
				this->insert_priority_Sorted(ord);

				return true;
			}
			p = q;
			q = p->getNext();
		}
		cout << " promotion not  done";
		return false;
	}

	void printlist() {
		if (Head == nullptr) {
			cout << "No waiting Orders" << endl;
			return;
		}
		Node<Order*>* p = Head;
		while (p) {
			cout << p->getItem()->GetID() << "&" << p->getItem()->GetPriority() << " / ";
			p = p->getNext();
		}
	}

	int 	get_NumberOfAutoPromoted() { return NumberOfAutoPromoted; }
	

	bool Cooks_Orders_Assignment(Trible_LinkedList& in_operation,Cooks_LinkedList& VIPCooks, Cooks_LinkedList& NormalCooks,Cooks_LinkedList& VeganCooks ,int &CurrentTimeStep, Queue<Trible*>*& Assigned) {


		if (this->isEmpty()) return false;

		if (VIPCooks.isEmpty() && NormalCooks.isEmpty() && VeganCooks.isEmpty()) return false;

		ORD_TYPE type = this->Frist_Order_Type();
		Cook* mycook = new Cook;
		Order* myorder = new Order;
		int flag = 0;
		int t; // Unit time for finishing the order
		//ASSIGNED_ORDER Aorder;
		if (type == TYPE_VIP) {
			if (!VIPCooks.isEmpty()) {
				VIPCooks.dequeue(mycook);
			}
			else if (!NormalCooks.isEmpty()) {
				NormalCooks.dequeue(mycook);

			}
			else {
				VeganCooks.dequeue(mycook);

			}
			this->Extract_First(myorder);
			mycook->go_work();
			t = (int)(myorder->GetDishes() / mycook->getSpeed()) + CurrentTimeStep;
			Trible *trible = new Trible(myorder, mycook, t);
			in_operation.insert_time_Sorted(*trible);
			Assigned->enqueue(trible);
			return true;
		}
		if (type == TYPE_VEG) {
			if (VeganCooks.isEmpty()) {
				return this->Swap_frist_Normal();

			}
			else
			{
				this->Extract_First(myorder);
				VeganCooks.dequeue(mycook);
				mycook->go_work();
				t = myorder->GetDishes() / mycook->getSpeed() + CurrentTimeStep;
				Trible *trible = new Trible(myorder, mycook, t);
				in_operation.insert_time_Sorted(*trible);
				Assigned->enqueue(trible);
				return true;
			}
		}
		if (type == TYPE_NRM) {
			if (VIPCooks.isEmpty() && NormalCooks.isEmpty()) return this->Swap_frist_Vegan();

			if (!NormalCooks.isEmpty())
			{
				NormalCooks.dequeue(mycook);
			}
			else
			{
				VIPCooks.dequeue(mycook);
			}
			this->Extract_First(myorder);
			mycook->go_work();
			t = myorder->GetDishes() / mycook->getSpeed() + CurrentTimeStep;
			Trible *trible = new Trible(myorder, mycook, t);
			in_operation.insert_time_Sorted(*trible);
			Assigned->enqueue(trible);
			return true;
		}
		return false;

	}
private:


};