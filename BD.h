#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include "Child.h"
#include "User.h"
#include "Logger.h"
#include <conio.h>
#include <sstream>
#include "FactoryForComponents.h"
#include "FactoryForGifts.h"

#include "Builder.h"

class BD
{
private:
	static BD* instance;
	//static int numchildren;
	BD() {}
	BD(const BD& obj) {}

	list<Child> childList;
	
	list<Gift*> giftStock;
	list<IComponent*> componentStock;

public:
	void startApplication();
	static BD* getInstance();
};

