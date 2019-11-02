#pragma once

#include "Defs.h"

#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	int speed;		//dishes it can prepare in one clock tick (in one timestep)
	 /// ==Added Members ==//
	int cons_orders; // Number of consecutive orders before taking a break;
	int break_duration; // The time the cook takes as a break;
	bool busy, in_break;
public:
	Cook();
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE) ;
		//== Added Functions ==//
	Cook(int id, ORD_TYPE ty, int c_orders); //Non-default constructor
	bool isBusy();
	bool inBreak();
	void work();
};
