#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancellationEvent.h"
#include "..\Events\PromotionEvent.h"
#include"..\GUI\GUIDrawables\NormalGUIElement.h"
#include"..\GUI\GUIDrawables\VeganGUIElement.h"
#include"..\GUI\GUIDrawables\VIPGUIElement.h"


Restaurant::Restaurant()
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE mode = pGUI->getProgramMode(); //The first Screen that let me choose the mode.

	this->Rest_Reader_Populator("trail.txt");
	// If you want to use the simulation GUI you must call initSimMode() same as the demo mode
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		pGUI->initSimMode();

		for (int i = 0; i < 30; i++) {

			this->ExecuteEvents(i);
			this->FillDrawingList();
			pGUI->updateInterface();
			pGUI->handleSimGUIEvents();
			// For Interactive mode
			pGUI->waitForClick();
			// For step-by-step mode
			//pGUI->sleep(300);
			

		}
		
		break;
	}

}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		cout <<"\n this is the event time  : "<< pE->getEventTime();
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		delete pGUI;
}


void Restaurant::FillDrawingList()
{

//	pGUI->addGUIDrawable()

	for (int i = 0; i < waiting_orders.getCount(); i++)
	{
		if (waiting_orders.Getkth(i)->GetType() == ORD_TYPE::TYPE_VEG) {
			pGUI->addGUIDrawable(new VeganGUIElement(waiting_orders.Getkth(i)->GetID(), GUI_REGION::DONE_REG));
		}
		else if (waiting_orders.Getkth(i)->GetType() == ORD_TYPE::TYPE_VIP) {
			pGUI->addGUIDrawable(new VIPGUIElement(waiting_orders.Getkth(i)->GetID(), GUI_REGION::SRV_REG));
		}
		else if (waiting_orders.Getkth(i)->GetType() == ORD_TYPE::TYPE_NRM) {
			pGUI->addGUIDrawable(new NormalGUIElement(waiting_orders.Getkth(i)->GetID(), GUI_REGION::ORD_REG));
		}
	}/*
	int h;
	Cook **C = NormalCooks.toArray(h);

	for (int i = 0; i < h; i++)
	{
			pGUI->addGUIDrawable(new VeganGUIElement(C[i]->GetID(), GUI_REGION::COOK_REG));	
	}*/


	
	//pGUI->addGUIDrawable(new VeganGUIElement(waiting_orders, GUI_REGION::ORD_REG));

	//This function should be implemented in phase1
	//It should add ALL orders and cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for cooks)

}

/// ====Cooks & Orders Assignment ===///
void Restaurant::Cooks_Orders_Assignment(int CurrentTimeStep) {
	ORD_TYPE type;
	Cook* mycook;
	Order* myorder;
	//ASSIGNED_ORDER Aorder;
	while (!(NormalCooks.isEmpty() && VeganCooks.isEmpty() && VIPCooks.isEmpty())) {
		type = waiting_orders.getHead()->getItem()->GetType();
		if (type == TYPE_VIP) {
			myorder = waiting_orders.getHead()->getItem();
			if (!VIPCooks.isEmpty()) VIPCooks.dequeue(mycook);
			else if (!NormalCooks.isEmpty()) NormalCooks.dequeue(mycook);
			else VeganCooks.dequeue(mycook); //This is to be deleted (But I wrote it for compliation only)
			//B_cooks.enqueue(mycook);
			//inwork_orders.InsertEnd(myorder);
			//Aorder.cook = mycook;
			//Aorder.order = myorder;
					   //==== Using the same LinkedList Implementation, I used the priority as the time to finish the ORDER--> Arrange with time; ======//
			//a_orders.insertpri(Aorder, CurrentTimeStep + mycook->getSpeed()*myorder->GetDishes()); // TO BE EDITED
			inwork_orders.insertpri(myorder, CurrentTimeStep + mycook->getSpeed()*myorder->GetDishes());
			Busy_Cooks.insertpri(mycook, CurrentTimeStep + mycook->getSpeed()*myorder->GetDishes());
		}
	}
}
 //Add Order function --> Called at ArrivalEvent
void Restaurant::addOrder(int ID, int arr, ORD_TYPE r_Type, int dishn, double totalmo) {
	Order* ord = new Order(ID, arr, r_Type, dishn, totalmo);
	if (ord->GetPriority() != 0) {
		waiting_orders.insertpri(ord, ord->GetPriority());
		delete[] ord;
	}
	else {
		waiting_orders.InsertEnd(ord);
	}
};
/// Cancel Order Function --> Called at CancelEvent
void Restaurant::CancelOrder(int ID) {
	Order* order;
	Node<Order*>* ord =new Node<Order*>;
	// I need Operator Overloading to have no errors in FIND Function ///
	waiting_orders.Find(ID, ord);
	order = ord->getItem();
	waiting_orders.DeleteNode(order);
}

////====READING THE FILE and Populating ===////
void Restaurant::Rest_Reader_Populator(string filename) {
	fstream myfile(filename, std::ios_base::in);
	int a;
	int general_data[12]; //In this array, I will save all the General Data from the input file	
	int i = 0;
	while (true)
	{
		myfile >> skipws >> a;
		general_data[i] = a;
		if (i == 11) break;
		i++;
	}
	Cooks_Populator(general_data);
	// 2- Population of events
	char event_type; // type of the event
	// P.S:: general_data[11] is the number of events from the file //
	for (int k = 0; k < general_data[11]; k++)
	{
		myfile >> event_type;
		switch (event_type)
		{
		case 'R': Arrival_Event_Populator(myfile);
			break;
		case 'X': Cancelation_Event_Populator(myfile);
			break;
		case 'P': Promotion_Event_Populator(myfile);
			break;
		}
	}
}
void Restaurant::Cooks_Populator(int* arr) {
	// Population of Cooks is Here 
	Cook* cook;
	for (int i = 0; i < arr[3]; i++) //Populate Normal Cooks
	{
		cook = new Cook(100 * (i + 1), TYPE_NRM, arr[6]);
		cook->setSpeed(arr[0]);
		NormalCooks.enqueue(cook);
	}
	for (int i = 0; i < arr[4]; i++) //Populate Vegan Cooks
	{
		cook = new Cook(200 * (i + 1), TYPE_VEG, arr[6]);
		cook->setSpeed(arr[1]);
		VeganCooks.enqueue(cook);
	}
	for (int i = 0; i < arr[5]; i++) //Populate VIP Cooks
	{
		cook = new Cook(300 * (i + 1), TYPE_VIP, arr[6]);
		cook->setSpeed(arr[2]);
		VIPCooks.enqueue(cook);
	}
}
void Restaurant::Arrival_Event_Populator(fstream& myfile) {
	char ortype; // type of the order if the event is arrival 
	ORD_TYPE order_type;
	int data_arrival[4];

	myfile >> ortype;
	for (int j = 0; j < 4; j++) {
		myfile >> data_arrival[j];
	}
	if (ortype == 'N') {
		order_type = TYPE_NRM;
	}
	else if (ortype == 'G') {
		order_type = TYPE_VEG;	//vegan
	}
	else if (ortype == 'V') {
		order_type = TYPE_VIP;
	}
	Event * ev = new ArrivalEvent(order_type, data_arrival[0], data_arrival[1], data_arrival[2], data_arrival[3]);
	EventsQueue.enqueue(ev);

	ev = nullptr;
	delete[] ev;
}
void Restaurant::Cancelation_Event_Populator(fstream& myfile) {
	int data_cancelation[2];
	for (int j = 0; j < 2; j++) {
		myfile >> data_cancelation[j];
	}
	Event ** ev = new Event*[1];
	ev[0] = new CancellationEvent(data_cancelation[0], data_cancelation[1]);
	EventsQueue.enqueue(ev[0]);
	delete[] ev;
}
void Restaurant::Promotion_Event_Populator(fstream& myfile) {
	int data_promotion[3];
	for (int j = 0; j < 3; j++) {
		myfile >> data_promotion[j];
	}
	Event * ev = new PromotionEvent(data_promotion[0], data_promotion[1], data_promotion[3]);
	EventsQueue.enqueue(ev);
	ev = nullptr;
	delete[] ev;

}