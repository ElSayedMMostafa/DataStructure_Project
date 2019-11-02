#include "CancelEvent.h"


CancelEvent::CancelEvent(int oID, ORD_TYPE oType) :Event(oID)
{
	OrdType = oType;
}

void CancelEvent::Execute(Restaurant* pRest)
{
	//This function should delete an order from  
	Order ord(OrderID, OrdType); //create an order that will be deleted
	if (OrdType == TYPE_NRM)
	{
		NormalOrders.DeleteNode(&ord.GetID);
	}
}
