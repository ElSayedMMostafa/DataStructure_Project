#pragma once
#include "Event.h"

class PromotionEvent : public Event
{
	double ExMony;
public:

	PromotionEvent(int eTime, int oID,double ExMony);
	virtual void Execute(Restaurant *pRest);

};

