#pragma once

#include "..\Defs.h"
#include "..\Generic_DS\Queue.h"
#pragma once
class Cook
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding type (VIP, Normal, Vegan)
	double speed;		//dishes it can prepare in one clock tick (in one timestep)
	 /// ==Added Members ==//
	int cons_orders; // Number of consecutive orders before taking a break; (constant)
	int break_duration; // The time the cook takes as a break; (constant)
	int time_moment; // The instant at which, the cook finished his break;
	int taken_orders; // The number #orders the cook actually take t
	bool busy, in_break, injured;
public:
	
	Cook();
	virtual ~Cook();
	int GetID() const;
	ORD_TYPE GetType() const;
	void setID(int);
	void setType(ORD_TYPE);
	//== Added Functions ==//
	Cook(int id, ORD_TYPE ty, int c_orders); //Non-default constructor
	Cook(int id, ORD_TYPE ty,int sp, int c_orders, int br_duration);
	bool isBusy(); //Returns true if busy working
	bool inBreak(); //Return true if the cook is in his break
	// Vital Functions
	bool Check4Break(int time); //Check if the cook deserves a break or not.
	bool OutFromBreak(int time);
	void go_work() { busy = true; taken_orders++; }
	int getSpeed();
	void setSpeed(int sp);
	void goBreak_Injuried(int time);
//	void populate(int* arr);
	void getInjuried(bool rest=true,int time=0) {
		injured = true;
		if (!rest) {
			speed = speed/2;
			if (speed < 1) speed = 1; //Minimum
		}
		else goBreak_Injuried(time);
		
	}
};