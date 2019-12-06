#include "ArrivalEvent.h"
#include"..\Rest\Restaurant.h"

ArrivalEvent::ArrivalEvent(ORD_TYPE oType, int eTime, int oID, int size, double money) :Event(eTime, oID) {
	OrdType = oType;
	OrdMoney = money;
	OrdDishes = size;
}


void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	pRest->addOrder(this->OrderID, this->EventTime, this->OrdType, this->OrdDishes, this->OrdMoney);
}
