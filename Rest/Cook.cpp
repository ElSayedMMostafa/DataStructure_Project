#include "Cook.h"


Cook::Cook()
{
		taken_orders = 0;
}

Cook::Cook(int id, ORD_TYPE ty, int c_orders = 4) {
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
Cook::Cook(int id, ORD_TYPE ty, int sp, int c_orders = 4, int br_duration = 3) {
	ID = id;
	type = ty;
	speed = sp;
	break_duration = br_duration;
	cons_orders = c_orders; // Default value is 4 unless the user defined another value.
	taken_orders = 0;
}
bool Cook::isBusy() {
	return busy;
}
bool Cook::inBreak() {
	return in_break;
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

bool Cook::Check4Break(int time) {
	if (taken_orders == cons_orders) { in_break = true; busy = false; time_moment = time + break_duration; return true; }
	return false;
}
void Cook::goBreak_Injuried(int time) {
	in_break = true; busy = false; time_moment = time + break_duration;
}
bool Cook::OutFromBreak(int time) {
	if (time == time_moment) return true;
	return false;
}

int Cook::getSpeed() {
	return speed;
}
void Cook::setSpeed(int sp) {
	speed = sp;
}

