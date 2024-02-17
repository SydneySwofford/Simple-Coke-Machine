#include "InputHandler.hpp"
#include <iostream>
using namespace std;

InputHandler::InputHandler(CokeMachine& cokeMachine) :
	_cokeMachine(cokeMachine)
{};

InputHandler::~InputHandler()
{};

void InputHandler::executeInput()
{
	//logic to interact with a user
	int userInput;
	cout<<"Please Enter a Coin by Writing in its Value:" << endl;
	cout << "(Ex. 1,5,10,25)" << endl;
	cin >> userInput;

	//checks if coin is a valid US coin, (because we have error logic for 1 and 25 built into the state machine)
	if (userInput == 1 || userInput == 5 || userInput == 10 || userInput == 25)
	{
		_cokeMachine.stateMachineTask(userInput);
	}
	else
	{
		cout << "You have not entered a valid coin type, please try again" << endl;
	}

}