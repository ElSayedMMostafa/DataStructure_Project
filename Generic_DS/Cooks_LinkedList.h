#pragma once
#include"LinkedList.h"
#include"..\Rest\Cook.h"

#/*include "LinkedList.h"
#include"..\Rest\Cook.h"*/


class Cooks_LinkedList : public LinkedList<Cook*>
{
public:
	Cooks_LinkedList() {};
	~Cooks_LinkedList() {};
	bool  dequeue(Cook* &d) {

			if (Head) {
				Node<Cook*> *p = Head->getNext();
				d = Head->getItem();
				Head = p;
				count--;
				return true;
			}
			return false;
		}

	bool enqueue(Cook*  &value) {
		
			// Empty list case //


			if (Head == nullptr) {
				InsertBeg(value);
				
				return true;
			}

			if (value->getSpeed() == 0) {
				InsertEnd(value);
				
				return true;
			}
			// Insert beginning case //
			if (Head->getItem()->getSpeed() < value->getSpeed()) {
				InsertBeg(value);
				return true;
			}
			if (Head->getItem()->getSpeed() == value->getSpeed()) {
				InsertBeg(value);
			
				return true;
			}
			// Single node case //
			if (Head->getNext() == nullptr) {
				if (Head->getItem()->getSpeed() > value->getSpeed()) {
					InsertEnd(value);
					
					return true;
				}

			}
			// General case //
			Node<Cook*>* p = Head;
			Node<Cook*>* q = p->getNext();
			while (q->getItem()->getSpeed() > value->getSpeed()) {
				if (q->getNext() == nullptr) {
					InsertEnd(value);
				
					return true;
				}
				p = q;
				q = q->getNext();

			}

			Node<Cook*>* newNode = new Node<Cook*>;
			newNode->setItem(value);
			newNode->setNext(q);
			p->setNext(newNode);
			count++;
			return true;

		}

};


