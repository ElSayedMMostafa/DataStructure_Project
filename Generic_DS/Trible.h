#pragma once
#include "../Rest/Cook.h"
#include "../Rest/Order.h"

class Trible
{
public:
	Trible() {
		order = nullptr;
		cook = nullptr;
		time = 0;
	}
	Trible(Order* ord, Cook* co, int t){
		order = ord; 
		cook = co;
		time = t;
	}
	int getTime() {
		return time;
	}
	Order* getOrder() {
		return order;
	}
	Cook* getCook() {
		return cook;
	}
	bool operator ==(int t) {
		if (this->time == t) return true;
		return false;
	}

	bool operator >(Trible& y) {
		if (this->time > y.getTime()) return true;
		return false;
	}
	bool operator <(Trible& y) {
		if (this->time < y.getTime()) return true;
		return false;
	}

	bool operator ==(Trible& y) {
		if (this->time == y.getTime()) return true;
		return false;
	}
private:
		Order* order;
		Cook* cook;
		int time;

		

};

