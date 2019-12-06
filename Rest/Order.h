#pragma once

#include "..\Defs.h"

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
	Order(int ID,int arr, ORD_TYPE r_Type,int dishn,double totalmo);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;

	void SetDishes(int d);
	int GetDishes() const;
	int GetPriority() const { return priority; }

	void setStatus(ORD_STATUS s);
	ORD_STATUS getStatus() const;
	
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
	
};
