#pragma once

#include "..\Defs.h"
#include "..\Generic_DS\Queue.h"
#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	 /// ==Added Members ==//
	int cons_orders; // Number of consecutive orders before taking a break;
	int break_duration; // The time the cook takes as a break;
	int taken_orders; // The number #orders the cook actually take t
	bool busy, in_break;
public:
	
	Cook();
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	//== Added Functions ==//
	Cook(int id, ORD_TYPE ty, int c_orders); //Non-default constructor
	bool isBusy(); //Returns true if busy working
	bool inBreak(); //Return true if the cook is in his break
	bool work();  //Make the cook busy and increases his taken_orders
	bool Check4Break(); //Check if the cook deserves a break or not.
	int getSpeed();
	void setSpeed(int sp);
	void populate(int* arr);
};