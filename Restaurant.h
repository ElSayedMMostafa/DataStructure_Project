#pragma once

#include "Defs.h"
#include "GUI.h"
#include "Queue.h"
#include "Event.h"
#include "Cook.h"


// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	 ///===Added Members===///
	Queue<Cook*> VIPCooks;  //A queue for each a type of AVAILABLE cooks.
	Queue<Cook*> NormalCooks;
	Queue<Cook*> VeganCooks;
	
	Queue<Cook*> B_cooks; // A queue for BUSY or in-Break Cooks.
	

public:
	
	Restaurant();
	~Restaurant();
	
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void FillDrawingList();

	//==Added Functions==//
	void InsertCook(Cook* c);

};
