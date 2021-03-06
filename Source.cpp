#include "Rest\Restaurant.h"

#include "GUI\GUIDrawables\NormalGUIElement.h"
#include "GUI\GUIDrawables\VeganGUIElement.h"
#include "GUI\GUIDrawables\VIPGUIElement.h"
#include "GUI\GUI.h"
#include <iostream>
#include <fstream>

using namespace std;
/* int GUIDemo()
{
	GUI gui;
	gui.initSimMode();

	int steps = 1;

	//while (true) {
		//if (steps % 5 == 0) {
			//gui.printStringInStatusBar("Current Time: " + std::to_string(steps));
	//	}
		int i = 5;

	//	for (int i = 0; i < steps; i++) {
		//	gui.addGUIDrawable(new VIPGUIElement(i+2, GUI_REGION::ORD_REG));
		//	gui.addGUIDrawable(new NormalGUIElement(i, GUI_REGION::COOK_REG));
		//	gui.addGUIDrawable(new VeganGUIElement(i, GUI_REGION::SRV_REG));
	//		gui.addGUIDrawable(new VIPGUIElement(i, GUI_REGION::DONE_REG));
		} //
		gui.addGUIDrawable(new VIPGUIElement(i + 2, GUI_REGION::ORD_REG));
		gui.addGUIDrawable(new NormalGUIElement(i, GUI_REGION::COOK_REG));
		gui.addGUIDrawable(new VeganGUIElement(i, GUI_REGION::SRV_REG));
		gui.addGUIDrawable(new VIPGUIElement(i, GUI_REGION::DONE_REG));
		gui.addGUIDrawable(new VIPGUIElement(i + 2+1, GUI_REGION::ORD_REG));
		gui.addGUIDrawable(new NormalGUIElement(i+1, GUI_REGION::COOK_REG));
		gui.addGUIDrawable(new VeganGUIElement(i+1, GUI_REGION::SRV_REG));
		gui.addGUIDrawable(new VIPGUIElement(i+1, GUI_REGION::DONE_REG));
		gui.deleteGUIDrawable(i + 3, GUI_REGION::ORD_REG);
		gui.updateInterface();
		gui.handleSimGUIEvents();
		// For Interactive mode
		//gui.waitForClick();
		// For step-by-step mode
		gui.sleep(300);
		steps++;
	//}
	
	return 0;
} */

int GUIDemo()
{
	GUI gui;
	gui.initSimMode();

	int steps = 1;

	while (true) {
		if (steps % 5 == 0) {
			gui.printStringInStatusBar("Current Time: " + std::to_string(steps));
		}

		for (int i = 0; i < steps; i++) {
			gui.addGUIDrawable(new VIPGUIElement(i, GUI_REGION::ORD_REG));
			gui.addGUIDrawable(new NormalGUIElement(i, GUI_REGION::COOK_REG));
			gui.addGUIDrawable(new VeganGUIElement(i, GUI_REGION::SRV_REG));
			gui.addGUIDrawable(new VIPGUIElement(i, GUI_REGION::DONE_REG));
		}

		gui.updateInterface();
		gui.handleSimGUIEvents();
		// For Interactive mode
		gui.waitForClick();
		// For step-by-step mode
		gui.sleep(300);
		steps++;
	}

	return 0;
}

int main() {

	/*Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();

	delete pRest;*/

	GUIDemo();
	// Reader

};


