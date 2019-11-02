#include "Cook.h"


Cook::Cook()
{
}
 
Cook::Cook(int id, ORD_TYPE ty, int c_orders=4) {
	ID = id;
	type = ty;
	switch (ty)  // The speed  and break duration aer constants for each type of cooks.
	{
	case TYPE_NRM: speed = 2; break_duration = 5;
		break;
	case TYPE_VEG: speed = 3; break_duration = 3;
		break;
	case TYPE_VIP: speed = 4; break_duration = 2;
		break;
	case TYPE_CNT: speed = 6; break_duration = 5;
		break;
	}
	cons_orders = c_orders; // Default value is 4 unless the user defined another value.
	taken_orders = 0;
}
bool Cook::isBusy() {
	return busy;
}
bool Cook::inBreak() {
	return in_break;
}
bool Cook::work() {  // Makes the cook start working unless he/she is in break
	if (!Check4Break()) {
		busy = true;
		taken_orders++;
		return true;
	}
	return false;
} 

Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = id;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
	switch (t)  // The speed is constant for each type of cooks.
	{
	case TYPE_NRM: speed = 2;
		break;
	case TYPE_VEG: speed = 3;
		break;
	case TYPE_VIP: speed = 4;
		break;
	case TYPE_CNT: speed = 6;
		break;
	}
}

bool Cook::Check4Break() {
	if (taken_orders == cons_orders) { in_break = true; busy = false; return true; }
	return false;
}


