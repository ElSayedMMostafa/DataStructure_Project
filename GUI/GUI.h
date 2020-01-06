#pragma once
#include <SFML\Graphics.hpp>

#include "GUIWindows\StartingScreen.h"
#include "GUIWindows\MainScreen.h"
#include "GUIWindows\TextArea.h"
#include "GUIDrawables\VIPGUIElement.h"
#include "GUIDrawables\NormalGUIElement.h"
#include "GUIDrawables\VeganGUIElement.h"
#include "..\Defs.h"
#include"..\Generic_DS\Queue.h"
#include"..\Generic_DS\LinkedList.h"
#include"..\Generic_DS\Waiting_Orders_LinkedList.h"
#include"..\Generic_DS\Cooks_LinkedList.h"

#include "..\Defs.h"
#include"..\Generic_DS\Queue.h"
#include"..\Generic_DS\LinkedList.h"
#include"..\Generic_DS\Waiting_Orders_LinkedList.h"
#include"..\Generic_DS\Cooks_LinkedList.h"
#include"..\Events\Event.h"
#include"..\Events\ArrivalEvent.h"
#include"..\Events\CancellationEvent.h"
#include"..\Events\PromotionEvent.h"
#include"..\Rest\Cook.h"
#include"..\Rest\Order.h"
#include "..\Generic_DS\Trible_LinkedList.h"

class GUI{

private:
	// GUI const parameters
#ifdef __unix__ 
	const std::string FONT_FILE_PATH = "Resources/CalibreBoldItalic.otf";
	const std::string LOGO_FILE_PATH = "Resources/logo1.png";
#elif _WIN32   
	const std::string FONT_FILE_PATH = "Resources\\CalibreBoldItalic.otf";
	const std::string LOGO_FILE_PATH = "Resources\\logo1.png";	
#endif

	sf::Font* calibre;

	const float STARTING_WINDOW_SIZE_X = 800, STARTING_WINDOW_SIZE_Y = 400;
	const float DRAWING_WINDOW_SIZE_X = 800, DRAWING_WINDOW_SIZE_Y = 400;
	const float STATUS_BAR_SIZE_X = 800, STATUS_BAR_SIZE_Y = 150;
	
	const sf::Color MAIN_WINDOW_BACKGROUND_COLOR = sf::Color(240, 231, 140);
	const sf::Color STARTING_WINDOW_BACKGROUND_COLOR = sf::Color(240, 231, 140);

	// GUI members
	sf::RenderWindow* simWindow = NULL;
	MainScreen* drawingScreen = NULL;
	TextArea* statusBar = NULL;

	// LOGIC members
	static const int MAX_DRAWABLES_COUNT = 200;
	GUIDrawable* drawablesList[MAX_DRAWABLES_COUNT];
	int drawablesListSize = 0;

public:

	GUI();
	~GUI();

	PROG_MODE getProgramMode();
	void initSimMode();

	void addGUIDrawable(GUIDrawable* drawable);
	void deleteGUIDrawable(int ID, GUI_REGION r);
	void deleteGUIDrawable();

	void printStringInStatusBar(std::string text);
	void handleSimGUIEvents();
	void waitForClick();
	void updateInterface();

	static void sleep(int milliseconds);



	void FillDrawings(int &step, Queue<Trible*>*&Assigned, Cooks_LinkedList &VIPCooks, Cooks_LinkedList& NormalCooks, Cooks_LinkedList& VeganCooks, Queue<Cook*>& B_cooks, Waiting_Orders_LinkedList &waiting_orders, Trible_LinkedList &in_operation, Queue<Order*> &done_orders);
	
};

