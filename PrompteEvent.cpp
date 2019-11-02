#include "PrompteEvent.h"


PrompteEvent::PrompteEvent(int oID, ORD_TYPE oType) :Event(oID)
{
	OrdType = oType;
}

void PrompteEvent::Execute(Restaurant* pRest)
{
	//This function should delete an order from  
	Order ord(OrderID, OrdType); //create an order that will be deleted
	if (OrdType == TYPE_NRM)
	{
		if (NormalOrders.DeleteNode(&ord.GetID)) {
			VIPOrders.InsertEnd(&ord);
		}
	}
}
