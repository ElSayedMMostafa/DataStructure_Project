#pragma once

#include "..\Defs.h"
#include "..\GUI\GUI.h"
#include"..\Generic_DS\Queue.h"
#include"..\Generic_DS\LinkedList.h"
#include"..\Generic_DS\Waiting_Orders_LinkedList.h"
#include"..\Generic_DS\Cooks_LinkedList.h"
#include"..\Events\Event.h"
#include"..\Events\ArrivalEvent.h"
#include"..\Events\CancellationEvent.h"
#include"..\Events\PromotionEvent.h"
#include"Cook.h"
#include"Order.h"
#include "..\Generic_DS\Trible_LinkedList.h"
#include <iostream>
#include <fstream>
using namespace std;
// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

								///===Added Members-Cooks===///
	Cooks_LinkedList VIPCooks;  //A queue for each a type of AVAILABLE cooks.
	Cooks_LinkedList NormalCooks;
	Cooks_LinkedList VeganCooks;
	Queue<Cook*> B_cooks; // A queue of "in break" cooks;
	Queue<Cook*> Inj_cooks; // A queue of "injuried" cooks;
	int Total_VIP_Cook=0; int Total_Vegan_Cook = 0; int Total_NRM_Cook = 0;
	///===Added Members-orders===///
	Waiting_Orders_LinkedList waiting_orders;
	Trible_LinkedList in_operation;
	Queue<Order*> done_orders;
	int N_Done_Orders=0;
	//LinkedList<ASSIGNED_ORDER> a_orders;
	//ASSIGNED_ORDER* a_orders [10]; //Replace 10 with the number of cooks.

	void Rest_Reader_Populator(string filename) ;
	int auto_promotion;

public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	

	void FillDrawingList(int TimeStep, Queue<Trible*>* Assigned);


	void addOrder(Order* d);
	void CancelOrder(int ID);
	void promoteOrder(int ID, int Extra);


	bool Cooks_Orders_Assignment(int CurrentTimeStep, Queue<Trible*>* Assigned);
	void FinishOrder(int time);
	bool GetCookOut(int time);



	void Cooks_Populator(int* arr);
	void Arrival_Event_Populator(fstream& myfile);
	void Cancelation_Event_Populator(fstream& myfile);
	void Promotion_Event_Populator(fstream& myfile);
	int get_auto_pro() { return auto_promotion; };
	
	void OutFile();
};
