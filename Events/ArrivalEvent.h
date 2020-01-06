#pragma once

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDishes;	//order number of dishes
	ORD_TYPE OrdType;		//order type: Normal, Vegan, VIP	                
	double OrdMoney;	//Total order money
public:
	ArrivalEvent(ORD_TYPE oType, int eTime, int oID, int size, double money);
	//Add more constructors if needed
	
	virtual void Execute(Restaurant *pRest);	//override execute function
	//void Arrival_Event_Populator(fstream& myfile, Queue<Event*>&EventsQueue);
};

