#include "CokeMachine.hpp"
#include <iostream>
using namespace std;

int runningSum = 0;//global running sum to monitor the amount of money input from the user

//statemachine starts in idel state, with no event, and uninitialized upon object creation, with no coin value
CokeMachine::CokeMachine() :
	_state(CokeMachine::State::IDLE),
	_event(CokeMachine::Event::NO_EVENT),
	_systemInitialized(false),
	_coinValue(0)
{
	initialize();
};

CokeMachine::~CokeMachine()
{};

void CokeMachine::initialize() //initialize function to ensure object has been properly created 
{
	_systemInitialized = true;
}

void CokeMachine::stateMachineTask(int coinValue)
{
	if (!_systemInitialized) {
		return;
	}

	//code will decipher the input from the person, then switch on the event, and monitor its current state, while calling back the task to run the next event based on its state/event
	if (coinValue == 1 || coinValue == 25) 
	{
		_state = CokeMachine::State::ERROR;
		_event = CokeMachine::Event::ERROR;
	}

	else if (coinValue == 5 || coinValue == 10) 
	{
		_state = CokeMachine::State::WAITING_FOR_PURCHASE_PRICE;
		_event = CokeMachine::Event::PROPER_COIN_INSERTED;
	}
	_coinValue = coinValue;

	//TRACKING/DEBUG COMMENT cout << "I am in " << _state << "state " << endl << endl;
	switch (_event)
	{
	case CokeMachine::Event::PROPER_COIN_INSERTED:
		checkCoinValue();
		break;
	case CokeMachine::Event::DISPENSING_COMPLETE:
		executeIdle();
		break;
	case CokeMachine::Event::ERROR:
		executeErrorReturnCoins(_coinValue);
		break;
	case CokeMachine::Event::NO_EVENT:
		executeIdle();
		break;

	}
}

void CokeMachine::stateMachineTask(CokeMachine::Event::Enum newEvent)
{
	_event = newEvent;
	//overload of the statMachineTask to allow callbacks to happen to the task after events have already occured 
	//TRACKING/DEBUG COMMENT cout << "I am in " << _state << "state " << endl << endl;
	switch (_event)
	{
	case CokeMachine::Event::PROPER_COIN_INSERTED:
		checkCoinValue();
		break;
	case CokeMachine::Event::DISPENSING_COMPLETE:
		executeIdle();
		break;
	case CokeMachine::Event::ERROR:
		executeErrorReturnCoins(_coinValue);
		break;
	case CokeMachine::Event::NO_EVENT:
		executeCheckState();
		break;
	case CokeMachine::Event::SUFFICIENT_FUNDS_ACHIEVED:
		executeDispensing();
		break;

	}
}

void CokeMachine::checkCoinValue()
{
	//helper function to determine how much money a user has input 
	if (_coinValue == 10)
	{
		runningSum += 10;
	}
	if (_coinValue == 5)
	{
		runningSum += 5;
	}
	if (runningSum >= 15) {
		//once the price 15c has been reached, we change states and initialize a new event
		_state = CokeMachine::State::DISPENSING;
		stateMachineTask(CokeMachine::Event::SUFFICIENT_FUNDS_ACHIEVED);
	}
	//initialize no event
	stateMachineTask(CokeMachine::Event::NO_EVENT);
}

void CokeMachine::executeDispensing()
{
	//signals dispensing of the coke
	cout << "Dispensing Your Coke" << endl; 
	if (runningSum > 15)
	{
		//checks if there should be any change, such that a user input 2 dimes
		dispenseChange(runningSum - 15);
	}
	cout << "Thank you, come Again" << endl << endl;
	//calls back another task with dispensing complete 
	stateMachineTask(CokeMachine::Event::DISPENSING_COMPLETE);
}

void CokeMachine::executeIdle()
{
	//signifys the idle state of waiting for another customer
	_state = CokeMachine::State::IDLE;
	cout << "Waiting for the next customer" << endl; 
	runningSum = 0;
}

void CokeMachine::executeErrorReturnCoins(int coinValue)
{
	//how to recover from error state
	cout << "This is not a valid coin, please try again" << endl;
	dispenseChange(coinValue);
	stateMachineTask(CokeMachine::Event::NO_EVENT);
}

void CokeMachine::dispenseChange(int changeRemainder)
{
	//signifying the change being dispensed, used in multiple places as a helper function
	cout << "Here is your change: " << changeRemainder << " cents " << endl;
	
}

void CokeMachine::executeCheckState()
{
	if(runningSum>0)
	{
		_state = CokeMachine::State::WAITING_FOR_PURCHASE_PRICE;
	}
	//differentiates whether the state is idle or waiting for more money when it cant determine off input 
	if (_state == CokeMachine::State::IDLE)
	{
		executeIdle();
	}
	else if (_state == CokeMachine::State::WAITING_FOR_PURCHASE_PRICE)
	{
		executeWaiting();
	}
}

void CokeMachine::executeWaiting()
{
	cout << "Waiting for More Money" << endl;
}