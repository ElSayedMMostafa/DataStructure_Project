#include "GUI.h"

GUI::GUI() {
	for (int i = 0; i < MAX_DRAWABLES_COUNT; i++){
		drawablesList[i] = NULL;
	}

	calibre = new sf::Font;
	if (!calibre->loadFromFile(FONT_FILE_PATH)) {
		std::cerr << "The font wasn't loaded\n";
		exit(1);
	}
}

GUI::~GUI() {
	delete calibre;
	delete simWindow;
	delete drawingScreen;
	delete statusBar;
}

PROG_MODE GUI::getProgramMode() {

	sf::RenderWindow window(sf::VideoMode((int)STARTING_WINDOW_SIZE_X, (int)STARTING_WINDOW_SIZE_Y), "Resturant, Starting Window");
	StartingScreen screen(STARTING_WINDOW_SIZE_X, STARTING_WINDOW_SIZE_Y, LOGO_FILE_PATH, calibre);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			std::string userInput = "";

			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode < 128) {
					userInput += static_cast<char>(event.text.unicode);
					if (userInput[0] == '\r') {
						PROG_MODE mode = screen.getMode();
						if (mode != PROG_MODE::MODE_CNT) {
							window.close();
							return mode;
						}
					} else {
						screen.showModeChoice(userInput);
					}
				}
				break;
			default:
				break;
			}
		}

		window.clear(sf::Color::Yellow);
		window.draw(screen);
		window.display();
	}
	// If something went wrong
	exit(1);
}

void GUI::initSimMode(){
	simWindow = new sf::RenderWindow(sf::VideoMode((int)DRAWING_WINDOW_SIZE_X, (int) (DRAWING_WINDOW_SIZE_Y + STATUS_BAR_SIZE_Y)), "Resturant, Simulation Window");
	
	drawingScreen = new MainScreen(DRAWING_WINDOW_SIZE_X, DRAWING_WINDOW_SIZE_Y, calibre);
	statusBar = new TextArea(STATUS_BAR_SIZE_X, STATUS_BAR_SIZE_Y, calibre);
	statusBar->setPosition(0.0f, DRAWING_WINDOW_SIZE_Y);
}

void GUI::updateInterface(){
	drawingScreen->drawUserGUIElements(drawablesList, drawablesListSize);

	simWindow->clear(this->MAIN_WINDOW_BACKGROUND_COLOR);
	simWindow->draw(*drawingScreen);
	simWindow->draw(*statusBar);
	simWindow->display();

	drawingScreen->clearUserElements();

	// Cleaning up the current Drawables
	for (int i = 0; i < drawablesListSize; i++)	{
		delete drawablesList[i];
		drawablesList[i] = NULL;
	}
	drawablesListSize = 0;
}

void GUI::sleep(int milliseconds) {
	sf::sleep(sf::milliseconds(milliseconds));
}

void GUI::addGUIDrawable(GUIDrawable* drawable){
	if(drawablesListSize + 1 < MAX_DRAWABLES_COUNT) {
		drawablesList[drawablesListSize++] = drawable;
	} else {
		std::cerr << "Too Many drawables on the screen\n";
	}
}
void GUI::deleteGUIDrawable(int ID, GUI_REGION r ) {
	int position =-1;
	for (int i = 0; i < drawablesListSize; i++)
	{
		
		if ( (drawablesList[i]->getID() == ID) && (drawablesList[i]->getCurrentRegion() == r)) position = i;
	}
	if (position != -1) {
		for (int i = position; i < MAX_DRAWABLES_COUNT; i++)
		{
			drawablesList[i] = drawablesList[i + 1];
		}
		drawablesListSize--;
	}
	
}
void GUI::deleteGUIDrawable() {
	drawablesListSize = 0;

}

void GUI::printStringInStatusBar(std::string text) {
	statusBar->printString(text);
}

void GUI::handleSimGUIEvents() {
	sf::Event event;
	while(simWindow->pollEvent(event)) {
		switch(event.type) {
		case sf::Event::Closed:
			simWindow->close();
			break;
		default:
			break;
		}
	}
}

void GUI::waitForClick() {
	sf::Event event;
	while(true) {
		while(simWindow->pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed:
				simWindow->close();
				break;
			case sf::Event::MouseButtonPressed:
				if(event.mouseButton.button == sf::Mouse::Left) { 
					return;
				}
				break;
			default:
				break;
			}
		}
	}
}
void GUI::FillDrawings(int &step, Queue<Trible*>*&Assigned, Cooks_LinkedList &VIPCooks, Cooks_LinkedList& NormalCooks, Cooks_LinkedList& VeganCooks, Queue<Cook*>& B_cooks, Waiting_Orders_LinkedList &waiting_orders, Trible_LinkedList &in_operation, Queue<Order*> &done_orders)
{
	ORD_TYPE order_type;
	int Id;
	int N_N = 0;
	int N_VIP = 0;
	int N_Vegan = 0;

	this->deleteGUIDrawable();
	for (int i = 0; i < waiting_orders.getCount(); i++)
	{
		order_type = waiting_orders.Getkth(i)->GetType();
		Id = waiting_orders.Getkth(i)->GetID();
		if (order_type == ORD_TYPE::TYPE_VEG) {
			this->addGUIDrawable(new VeganGUIElement(Id, GUI_REGION::ORD_REG));
			N_Vegan++;
		}
		else if (order_type == ORD_TYPE::TYPE_VIP) {
			this->addGUIDrawable(new VIPGUIElement(Id, GUI_REGION::ORD_REG));
			N_VIP++;
		}
		else if (order_type == ORD_TYPE::TYPE_NRM) {
			this->addGUIDrawable(new NormalGUIElement(Id, GUI_REGION::ORD_REG));
			N_N++;
		}
	}

	for (int i = 0; i < in_operation.getCount(); i++)
	{
		order_type = in_operation.Getkth(i).getOrder()->GetType();
		Id = in_operation.Getkth(i).getOrder()->GetID();
		if (order_type == ORD_TYPE::TYPE_VEG) {
			this->addGUIDrawable(new VeganGUIElement(Id, GUI_REGION::SRV_REG));
		}
		else if (order_type == ORD_TYPE::TYPE_VIP) {
			this->addGUIDrawable(new VIPGUIElement(Id, GUI_REGION::SRV_REG));
		}
		else if (order_type == ORD_TYPE::TYPE_NRM) {
			this->addGUIDrawable(new NormalGUIElement(Id, GUI_REGION::SRV_REG));
		}
	}
	int done_order_count;
	Order** done_orders_array = done_orders.toArray(done_order_count);
	for (int i = 0; i < done_order_count; i++)
	{
		order_type = done_orders_array[i]->GetType();
		Id = done_orders_array[i]->GetID();
		if (order_type == ORD_TYPE::TYPE_VEG) {
			this->addGUIDrawable(new VeganGUIElement(Id, GUI_REGION::DONE_REG));
		}
		else if (order_type == ORD_TYPE::TYPE_VIP) {
			this->addGUIDrawable(new VIPGUIElement(Id, GUI_REGION::DONE_REG));
		}
		else if (order_type == ORD_TYPE::TYPE_NRM) {
			this->addGUIDrawable(new NormalGUIElement(Id, GUI_REGION::DONE_REG));
		}
	}
	delete[] done_orders_array;
	std::string status;

	int normalcooks;
	Cook** Normal_array = NormalCooks.toArray(normalcooks);
	int VIPcooks;
	Cook** VIP_array = VIPCooks.toArray(VIPcooks);
	int Vegancooks;
	Cook** Vegan_array = VeganCooks.toArray(Vegancooks);
	for (int i = 0; i < normalcooks; i++)
	{
		this->addGUIDrawable(new NormalGUIElement(Normal_array[i]->GetID(), GUI_REGION::COOK_REG));
	}
	for (int i = 0; i < VIPcooks; i++)
	{
		this->addGUIDrawable(new VIPGUIElement(VIP_array[i]->GetID(), GUI_REGION::COOK_REG));
	}
	for (int i = 0; i < Vegancooks; i++)
	{
		this->addGUIDrawable(new VeganGUIElement(Vegan_array[i]->GetID(), GUI_REGION::COOK_REG));
	}
	delete[] Normal_array;
	delete[] VIP_array;
	delete[] Vegan_array;
	status = "";
	status = "Timestep = " + std::to_string(step)
		+ "\n Number of waiting orders      Normal = " + std::to_string(N_N)
		+ "              VIP = " + std::to_string(N_VIP)
		+ "              Vegan = " + std::to_string(N_Vegan)
		+ "\n Number of available cooks     Normal = " + std::to_string(NormalCooks.getCount())
		+ "              VIP = " + std::to_string(VIPCooks.getCount())
		+ "              Vegan = " + std::to_string(VeganCooks.getCount());
	Trible* t;
	if (Assigned->isEmpty())
	{
		status += "\nNo Orders assigned last Timestep ";
	}
	else {
		std::string cooktype;
		std::string ordertype;
		status += "\nThe number of orders Assigned last Timestep is " + std::to_string(Assigned->get_count()) + "\n";
		while (Assigned->dequeue(t)) {
			if (t->getCook()->GetType() == TYPE_NRM) {
				cooktype = "Normal";
			}
			else if (t->getCook()->GetType() == TYPE_VIP) {
				cooktype = "VIP";
			}
			else cooktype = "Vagen";
			if (t->getOrder()->GetType() == TYPE_NRM) {
				ordertype = "Normal";
			}
			else if (t->getOrder()->GetType() == TYPE_VIP) {
				ordertype = "VIP";
			}
			else ordertype = "Vagen";
			status += cooktype + " cook#" + std::to_string(t->getCook()->GetID()) + " assigned " + ordertype + " order#" + std::to_string(t->getOrder()->GetID()) + "\n";
			//status += "Cook ID = " + std::to_string(t->getCook()->GetID()) +"     Cook Type = " + cooktype +"     Order ID = " + std::to_string(t->getOrder()->GetID()) +"     Order Type = " + ordertype +"\n";
		}
	}
	cout << status;
	this->printStringInStatusBar(status);
}
