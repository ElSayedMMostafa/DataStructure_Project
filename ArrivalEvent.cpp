#include "ArrivalEvent.h"

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType):Event(eTime, oID)
{
	OrdType = oType;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1
	Order MyOrder (OrderID,OrdType);
	switch (OrdType)
	{
	case TYPE_NRM: NormalOrders.InsertEnd(&MyOrder);
		break;
	case TYPE_VEG: VeganOrders.InsertEnd(&MyOrder);
		break;
	case TYPE_VIP: VIPOrders.InsertEnd(&MyOrder);
		break;
	default:
		break;
	}
}
