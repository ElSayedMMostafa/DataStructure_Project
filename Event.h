#pragma once

#include "Defs.h"

class Restaurant;	//Forward declation

//The base class for all possible events in the system (abstract class)
class Event
{
protected:
	int EventTime;	//Timestep when this event takes place
	int OrderID;	//each event is related to certain order

	///==Added Member===///
	LinkedList<Order*> VIPOrders;
	LinkedList<Order*> VeganOrders;
	LinkedList<Order*> NormalOrders;

public:
	Event(int eTime, int ordID);
	int getEventTime();
	int getOrderID();
	virtual ~Event();


	virtual void Execute(Restaurant* pRest)=0;	////a pointer to "Restaurant" and events need it to execute

	//==Added Functions==//
	Event(int ordID); //Another Constructor

};
