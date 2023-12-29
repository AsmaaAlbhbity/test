#ifndef ACTION_DELETE_H
#define ACTION_DELETE_H
#include <iostream>
#include "Actions/Action.h"
#pragma once

class ActionDelete : public Action
{
public:
	ActionDelete(ApplicationManager* pApp);

	
	virtual void Execute();
};
#endif

