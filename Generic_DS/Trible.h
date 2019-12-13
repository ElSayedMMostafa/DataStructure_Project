#pragma once
#include "../Rest/Cook.h"
#include "../Rest/Order.h"

class Trible
{
public:
	

	Trible(); //Default constructor
	Trible(Order* ord, Cook* co, int t){
		order = ord; 
		cook = co;
		time = t;
	}
	int getTime() {
		return time;
	}
	bool operator ==(int t) {
		if (this->time == t) return true;
		return false;
	}
private:
		Order* order;
		Cook* cook;
		int time;

		

};

