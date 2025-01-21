#pragma once
#include <stack>
#include "State.h"

class StateStack
{
public:
	StateStack() = default;
	~StateStack() = default;

	State* GetTopState()
	{
		return myStack.top();
	}

	void PopState()
	{
		myStack.pop();
	}

	void PushState(State* aStatePointer)
	{
		myStack.push(aStatePointer);
	}

	const std::stack<State*> GetStack()
	{
		return myStack;
	}

	void SetPreviousState(State* aState)
	{
		myPreviousState = aState;
	}

	State* GetPreviousState() const
	{
		return myPreviousState;
	}

private:
	std::stack<State*> myStack;
	State* myPreviousState;
};


//fix all the images - pos, size etc
