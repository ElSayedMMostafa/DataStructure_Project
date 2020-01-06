#pragma once

#include "..\Defs.h"
#include<iostream>
#include "..\Generic_DS\Queue.h"
using namespace std;
class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Vegan, VIP
	ORD_STATUS status;	//waiting, in-service, done
	int Dishes;	//The number of dishes in that order 
	int priority;
	double totalMoney;	//Total order money
	int waiting_time;	// order waiting time 
	int ArrTime, ServTime, FinishTime;	//arrival, service start, and finish times

	
	

public:
	Order() {}
	Order(int ID,int arr, ORD_TYPE r_Type,int dishn,double totalmo);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	void SetDishes(int d);

	void Promote_To_Vip(int extra) {
		type = TYPE_VIP;
		cout << " The extra is " << extra;
		totalMoney = extra + totalMoney;
		priority = (int)3 / (ArrTime + 1) + (int)totalMoney / Dishes;
	}
	void increment_waiting_time() { waiting_time++; }
	int GetDishes() const;
	int GetPriority() const { return priority; }

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;

	bool reprioritize_Order(int p ) {
		if (!type) return false;
		if (waiting_time > p) {
			type = ORD_TYPE::TYPE_VIP;
			priority = (int)3 / (1+ArrTime) + (int)totalMoney / Dishes;
			return true;
		}
		return false;
	}
	//
	// TODO: Add More Member Functions As Needed
	//
	// Operator Overloading.
	bool operator==(const int & d) {

		if (this->GetID() == d) {
			return true;
		}
		return false;
	}

	static void GetNumberEachOrder(int* arr, Queue<Order*> DONE_ORDERS_QUEUE);
	int get_FT() {
		return FinishTime;
	}
	void set_FT(int t) {
		FinishTime = t;
	}
	int get_WT() {
		return waiting_time;
	}
	int get_AT() {
		return ArrTime;
	}
};
