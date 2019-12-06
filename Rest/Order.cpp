#include "Order.h"

Order::Order(int id,int arr , ORD_TYPE r_Type, int dishn, double totalmo)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	ArrTime = arr;
	type = r_Type;
	Dishes = dishn;
	totalMoney = totalmo;
	if (type != TYPE_VIP) {
		priority = 0;
	}
	else {
		priority = arr * 3 + (int)totalmo/dishn;
	}
	status = WAIT;
	waiting_time = 0;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetDishes(int d)
{
	Dishes = d>0?d:0;
}

int Order::GetDishes() const
{
	return Dishes;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

