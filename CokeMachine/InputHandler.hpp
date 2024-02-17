#pragma once
#include "CokeMachine.hpp"

class InputHandler {
public:
	//used to allow cokemachine to have single responsibility, and seperate user input out
	InputHandler(CokeMachine& cokeMachine);
	~InputHandler();

	void executeInput();

private:
	//holder for the referenced coke object
	CokeMachine _cokeMachine;
};