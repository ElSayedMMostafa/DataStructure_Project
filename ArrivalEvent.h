#pragma once

#include "Event.h"
#include "LinkedList.h"
#include "Order.h"

//class for the arrival event
class ArrivalEvent : public Event
{
	//info about the order ralted to arrival event
	int OrdDishes;	//order number of dishes
	ORD_TYPE OrdType;		//order type: Normal, Vegan, VIP	                
	double OrdMoney;	//Total order money

	///==Added Member===///
	LinkedList<Order*> VIPOrders;
	LinkedList<Order*> VeganOrders;
	LinkedList<Order*> NormalOrders;


public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);
	//Add more constructors if needed

	virtual void Execute(Restaurant *pRest);	//override execute function

};

