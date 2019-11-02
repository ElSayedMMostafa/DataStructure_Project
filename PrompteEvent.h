#pragma once
#include "Event.h"
#include "LinkedList.h"
#include "Order.h"

//class for the Prompte event
class PrompteEvent : public Event
{
	//info about the order ralted to Prompte event
	ORD_TYPE OrdType;		//order type: Normal, Vegan, VIP	
	int Added_Money;	//The additionalMoney to make the normal -> VIP ( Not used till NOW ya 4abab :'D )

public:
	PrompteEvent(int oID, ORD_TYPE oType);
	//Add more constructors if needed

	virtual void Execute(Restaurant *pRest);	//override execute function

};