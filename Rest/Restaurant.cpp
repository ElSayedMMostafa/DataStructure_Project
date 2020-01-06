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
	PROG_MODE mode = pGUI->getProgramMode(); //The first Screen that let me choose the mode. This allow the user to choose the 
											// Resturant mode

	this->Rest_Reader_Populator("test_case4.txt"); // Loading Input File

	switch (mode) // switching for the modes 
	{
	case MODE_INTR:
		pGUI->initSimMode(); // Starting the GUI 

		for (int i = 0; i < 70; i++) {

			pGUI->waitForClick(); // Waiting for a click to start the next time click
			cout << "=========================" << endl;
			cout << "Time Now = " << i << endl;
			this->ExecuteEvents(i); // excutiong all the events in that time step
			while (GetCookOut(i));                         //To get out the cooks from the break
			waiting_orders.reorder_Orders(auto_promotion); // checking for auto-promoted Normal orders
			Queue<Trible*> *Assignedd = new Queue<Trible*>; // To Keep track of the last timesstep Assignment
			while (this->Cooks_Orders_Assignment(i, Assignedd)); // Assigning the cooks to the order as much as possible
			FinishOrder(i); // Checking 
			waiting_orders.increase_waiting_time(); //Increase the waiting time for all the orders in the waiting order list
			this->FillDrawingList(i, Assignedd);
			delete Assignedd;
			pGUI->updateInterface();
			pGUI->handleSimGUIEvents();
			in_operation.print_triple();	//For testing
			waiting_orders.printlist();		// For testing 
			if (!VIPCooks.isEmpty()) cout << "VIP Cook & ";
			if (!NormalCooks.isEmpty()) cout << "Normal Cook & ";
			if (!VeganCooks.isEmpty()) cout << "Vegan Cook & ";
			if (!B_cooks.isEmpty()) cout << "Break Cook & ";
			cout << endl;
		}
		OutFile();
		break;
	case MODE_STEP:
		pGUI->initSimMode(); // Starting the GUI 

		for (int i = 1; i < 40; i++) {

			pGUI->sleep(100);
			cout << "=========================" << endl;
			cout << "Time Now = " << i << endl;
			this->ExecuteEvents(i); // excutiong all the events in that time step
			while (GetCookOut(i));                         //To get out the cooks from the break
			waiting_orders.reorder_Orders(auto_promotion); // checking for auto-promoted Normal orders
			Queue<Trible*> *Assignedd = new Queue<Trible*>; // To Keep track of the last timesstep Assignment
			while (this->Cooks_Orders_Assignment(i, Assignedd)); // Assigning the cooks to the order as much as possible
			FinishOrder(i); // Checking 
			waiting_orders.increase_waiting_time(); //Increase the waiting time for all the orders in the waiting order list
			this->FillDrawingList(i, Assignedd);
			delete Assignedd;
			pGUI->updateInterface();
			pGUI->handleSimGUIEvents();
			in_operation.print_triple();	//For testing
			waiting_orders.printlist();		// For testing 
			if (!VIPCooks.isEmpty()) cout << "VIP Cook & ";
			if (!NormalCooks.isEmpty()) cout << "Normal Cook & ";
			if (!VeganCooks.isEmpty()) cout << "Vegan Cook & ";
			if (!B_cooks.isEmpty()) cout << "Break Cook & ";
			cout << endl;
		}
		OutFile();
		break;
	case MODE_SLNT:
		for (int i = 1; i < 500; i++) {

			cout << "=========================" << endl;
			cout << "Time Now = " << i << endl;
			this->ExecuteEvents(i); // excutiong all the events in that time step
			while (GetCookOut(i));                         //To get out the cooks from the break
			waiting_orders.reorder_Orders(auto_promotion); // checking for auto-promoted Normal orders
			Queue<Trible*> *Assignedd = new Queue<Trible*>; // To Keep track of the last timesstep Assignment
			while (this->Cooks_Orders_Assignment(i, Assignedd)); // Assigning the cooks to the order as much as possible
			FinishOrder(i); // Checking 
			waiting_orders.increase_waiting_time(); //Increase the waiting time for all the orders in the waiting order list

			delete Assignedd;
			in_operation.print_triple();	//For testing
			waiting_orders.printlist();		// For testing 
			if (!VIPCooks.isEmpty()) cout << "VIP Cook & ";
			if (!NormalCooks.isEmpty()) cout << "Normal Cook & ";
			if (!VeganCooks.isEmpty()) cout << "Vegan Cook & ";
			if (!B_cooks.isEmpty()) cout << "Break Cook & ";
			cout << endl;
		}
		OutFile();
		break;
	}
}



//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		//cout <<"\n this is the event time  : "<< pE->getEventTime();
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current time
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


void Restaurant::FillDrawingList(int step, Queue<Trible*>*Assigned){
	pGUI->FillDrawings(step, Assigned, VIPCooks, NormalCooks, VeganCooks, B_cooks, waiting_orders, in_operation, done_orders);

}

/// ====Cooks & Orders Assignment ===///
bool Restaurant::Cooks_Orders_Assignment(int CurrentTimeStep, Queue<Trible*>* Assigned) {
	return waiting_orders.Cooks_Orders_Assignment(in_operation, VIPCooks, NormalCooks, VeganCooks, CurrentTimeStep, Assigned);
}


void Restaurant::addOrder(Order* d) {
	waiting_orders.insert_priority_Sorted(d);
}

/// Cancel Order Function --> Called at CancelEvent
void Restaurant::CancelOrder(int ID) {
	waiting_orders.DeleteOrder(ID);
}
// Called when we check if an order is done and then operate on the cook and the finished order as shown.
void Restaurant::FinishOrder(int time) { 
	in_operation.FinishOrder(N_Done_Orders, done_orders, VIPCooks, NormalCooks, VeganCooks, B_cooks, time);
}

// Called to finish the break duration of some cooks
 // Repeat it in while loop when execution
bool Restaurant::GetCookOut(int time) {
	Cook* Co;
	if (B_cooks.peekFront(Co)) {
		if (Co->OutFromBreak(time)) {
			B_cooks.dequeue(Co);
			switch (Co->GetType())
			{
			case TYPE_VIP: VIPCooks.enqueue(Co);
				break;
			case TYPE_NRM: NormalCooks.enqueue(Co);
				break;
			case TYPE_VEG: VeganCooks.enqueue(Co);
				break;
			}
			return true;
		}
	}
	return false;
}

void Restaurant::promoteOrder(int ID, int Extra) { waiting_orders.PromoteOrder(ID, Extra); }

////====READING THE FILE and Populating ===////
void Restaurant::Rest_Reader_Populator(string filename) {
	fstream myfile(filename, std::ios_base::in);
	int a;
	int general_data[100]; //In this array, I will save all the General Data from the input file	
	int i = 0;
	while (true)
	{
		myfile >> skipws >> a;
		if (a == 11111) break;
		general_data[i] = a;
		i++;
	}
	Cooks_Populator(general_data);
	// 2- Population of events
	char event_type; // type of the event
	
	myfile >> skipws >> auto_promotion; //The auto-promotion limit
	myfile >> skipws >> a;				// The number of events
	for (int k = 0; k < a; k++)
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
    // arr[0] is the number of Normal Cooks
	// arr[1] is the number of VIP Cooks
	// arr[2] is the number of Vegan Cooks
	for (int i = 0; i < arr[0]; i++) //Populate Normal Cooks
	{
		cook = new Cook(100 * (i + 1), TYPE_NRM, arr[3+i], arr[3 + arr[0]+arr[1]+arr[2]], arr[6 + arr[0] + arr[1] + arr[2]]);
		NormalCooks.enqueue(cook);
		Total_NRM_Cook++;
	}
	for (int i = 0; i < arr[1]; i++) //Populate VIP Cooks
	{
		cook = new Cook(200 * (i + 1), TYPE_VIP, arr[3 + i + arr[0]], arr[4 + arr[0] + arr[1] + arr[2]], arr[6 + arr[0] + arr[1] + arr[2]]);
		VIPCooks.enqueue(cook);
		Total_VIP_Cook++;
	}
	for (int i = 0; i < arr[2]; i++) //Populate Vegan Cooks
	{
		cook = new Cook(300 * (i + 1), TYPE_VEG, arr[3 + i + arr[0] + arr[1]], arr[5 + arr[0] + arr[1] + arr[2]], arr[6 + arr[0] + arr[1] + arr[2]]);
		VeganCooks.enqueue(cook);
		Total_Vegan_Cook++;
	}
	auto_promotion = arr[3 + arr[0] + arr[1] + arr[2]];
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

//ArrivalEvent::Arrival_Event_Populator(myfile,EventsQueue);
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
	Event * ev = new PromotionEvent(data_promotion[0], data_promotion[1], data_promotion[2]);
	EventsQueue.enqueue(ev);
	ev = nullptr;
	delete[] ev;

}
void Restaurant::OutFile() {
	ofstream filey("OutputFile4.txt");
	Order* ord;
	Queue<Order*> done_orders_2;
	int waiting_times_sum = 0; int waiting_times_counter = 0;
	int serving_times_sum = 0; int serving_times_counter = 0;
	// 1 -Number of Orders (Total)
	filey << "The number of Served orders = " << N_Done_Orders << endl;
	// 2- Orders LIST
	filey << "FT" << '\t' << "ID" << '\t' << "AT" << '\t' << "WT" << '\t' << "ST" << endl;
	while (!done_orders.isEmpty()) //Ascending Order will be created automatically due to the usage of QUEUE.
	{
		done_orders.dequeue(ord);
		filey << ord->get_FT() << '\t' << ord->GetID() << '\t' << ord->get_AT() << '\t' << ord->get_WT() << '\t' << ord->get_FT() - ord->get_AT() - ord->get_WT() << endl;
		waiting_times_sum += ord->get_WT(); waiting_times_counter++;
		serving_times_sum += ord->get_FT() - ord->get_AT() - ord->get_WT(); serving_times_counter++;
		done_orders_2.enqueue(ord);
	}
	// 2- Number of Each Order Type
	int arr_done_orders[3];
	Order::GetNumberEachOrder(arr_done_orders, done_orders_2);
	filey << "# VIP Orders =    " << arr_done_orders[0] << endl;
	filey << "# Vegan Orders =  " << arr_done_orders[1] << endl;
	filey << "# Normal Orders = " << arr_done_orders[2] << endl;
	// 3- Number of Cooks;
	filey << "Number of Cooks = " << Total_NRM_Cook + Total_Vegan_Cook + Total_VIP_Cook << endl;
	filey << "# VIP Cooks =    " << Total_VIP_Cook << endl;
	filey << "# Vegan Cooks =  " << Total_Vegan_Cook << endl;
	filey << "# Normal Cooks = " << Total_NRM_Cook << endl;

	// 4- Statistics:
	filey << "Avg Wait= " << (float)waiting_times_sum / waiting_times_counter << endl;
	filey << "Avg Serv= " << (float)serving_times_sum / serving_times_counter << endl;
	filey << "Auto-Promoted= " << waiting_orders.get_NumberOfAutoPromoted() << endl;
}