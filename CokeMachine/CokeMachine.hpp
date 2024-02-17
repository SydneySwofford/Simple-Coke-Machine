#pragma once
class CokeMachine
{
public:
	struct State//creating class enum to define the states
	{
		enum Enum
		{
			IDLE=0,
			DISPENSING=1,
			ERROR=2,
			WAITING_FOR_PURCHASE_PRICE=3
		};
	};

	struct Event//creating class enum to define the events
	{
		enum Enum
		{
			PROPER_COIN_INSERTED = 0,
			DISPENSING_COMPLETE = 1,
			ERROR = 2,
			NO_EVENT = 3,
			SUFFICIENT_FUNDS_ACHIEVED =4
		};
	};

	//constructor, destructor
	CokeMachine();
	~CokeMachine();

	//initialize function allows seperation between running and instantiation of the object. 
	void initialize();
	//this is the task callback, a simulation of a thread, a task that would be running, with two overloaded functions
	void stateMachineTask( int coinValue);
	void stateMachineTask(CokeMachine::Event::Enum newEvent);
	//what to do when the staemachine is idle 
	void executeIdle();
	//helper function to check the state when states cannot be differentiated by events by the input 
	void executeCheckState();
	//what to do when the statemachine is dispensing
	void executeDispensing();
	//what to do when the statemachine is in an error
	void executeErrorReturnCoins(int coinValue);
	//helper function to check the user coin input
	void checkCoinValue();
	//what to do when the statemachine is waiting
	void executeWaiting();
	//helper function to give change if there is any 
	void dispenseChange(int changeRemainder);

	//private values I deemed important for the statemachine to have knowledge of throughout its instance
private:
	CokeMachine::State::Enum _state;
	CokeMachine::Event::Enum _event;
	bool _systemInitialized;
	int _coinValue;
};





