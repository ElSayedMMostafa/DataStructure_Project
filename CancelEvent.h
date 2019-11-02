#pragma once
#include "Event.h"
#include "LinkedList.h"
#include "Order.h"

//class for the cancel event
class CancelEvent : public Event
{
	//info about the order ralted to cancel event
	ORD_TYPE OrdType;		//order type: Normal, Vegan, VIP	                

	///==Added Member===///
	LinkedList<Order*> VIPOrders;
	LinkedList<Order*> VeganOrders;
	LinkedList<Order*> NormalOrders;


public:
	CancelEvent(int oID, ORD_TYPE oType);
	//Add more constructors if needed

	virtual void Execute(Restaurant *pRest);	//override execute function

};