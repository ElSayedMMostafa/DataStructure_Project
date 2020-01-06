#include "ArrivalEvent.h"
#include"..\Rest\Restaurant.h"

ArrivalEvent::ArrivalEvent(ORD_TYPE oType, int eTime, int oID, int size, double money) :Event(eTime, oID) {
	OrdType = oType;
	OrdMoney = money;
	OrdDishes = size;
}


void ArrivalEvent::Execute(Restaurant* pRest)
{
	Order* o = new Order(OrderID, EventTime, OrdType, OrdDishes, OrdMoney);
	pRest->addOrder(o);
}


//void ArrivalEvent::Arrival_Event_Populator(fstream& myfile, Queue<Event*>&EventsQueue) {
//	char ortype;  // type of the order if the event is arrival 
//	ORD_TYPE order_type;
//	int data_arrival[4];
//
//	myfile >> ortype;
//	for (int j = 0; j < 4; j++) {
//		myfile >> data_arrival[j];
//	}
//	if (ortype == 'N') {
//		order_type = TYPE_NRM;
//	}
//	else if (ortype == 'G') {
//		order_type = TYPE_VEG;	//vegan
//	}
//	else if (ortype == 'V') {
//		order_type = TYPE_VIP;
//	}
//	Event * ev = new ArrivalEvent(order_type, data_arrival[0], data_arrival[1], data_arrival[2], data_arrival[3]);
//	EventsQueue.enqueue(ev);
//
//	ev = nullptr;
//	delete[] ev;
//}
