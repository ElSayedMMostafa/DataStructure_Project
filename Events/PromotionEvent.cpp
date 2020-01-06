#include "PromotionEvent.h"
#include"..\Rest\Restaurant.h"



PromotionEvent::PromotionEvent(int eTime, int oID, double Extramony) :Event(eTime, oID)
{
	ExMony = Extramony;

}
void PromotionEvent::Execute(Restaurant *pRest) {

	pRest->promoteOrder(OrderID, ExMony);
	cout << " The extra " << ExMony << endl;
}