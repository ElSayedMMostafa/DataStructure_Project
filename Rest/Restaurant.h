#pragma once

#include "..\Defs.h"
#include "..\GUI\GUI.h"
#include"..\Generic_DS\Queue.h"
#include"..\Generic_DS\LinkedList.h"
#include"..\Events\Event.h"
#include"..\Events\ArrivalEvent.h"
#include"..\Events\CancellationEvent.h"
#include"..\Events\PromotionEvent.h"
#include"Cook.h"
#include"Order.h"
#include <iostream>
#include <fstream>
using namespace std;
// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	/////////////////////////////////////
	///===Added Members-Cooks===///
	Queue<Cook*> VIPCooks;  //A queue for each a type of AVAILABLE cooks.
	Queue<Cook*> NormalCooks;
	Queue<Cook*> VeganCooks;
	Queue<Cook*> B_cooks; // A queue of "in break" cooks;
	LinkedList<Cook*> Busy_Cooks;
	///===Added Members-orders===///
	LinkedList<Order*> waiting_orders;
	LinkedList<Order*> inwork_orders;
	LinkedList<Order*> done_orders;
	//LinkedList<ASSIGNED_ORDER> a_orders;
	//ASSIGNED_ORDER* a_orders [10]; //Replace 10 with the number of cooks.

	void Rest_Reader_Populator(string filename) ;

public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	
	void FillDrawingList();
	void addOrder(int ID, int arr, ORD_TYPE r_Type, int dishn, double totalmo);
	void CancelOrder(int ID);
	void Cooks_Orders_Assignment(int CurrentTimeStep);
	void Cooks_Populator(int* arr);
	void Arrival_Event_Populator(fstream& myfile);
	void Cancelation_Event_Populator(fstream& myfile);
	void Promotion_Event_Populator(fstream& myfile);
};
