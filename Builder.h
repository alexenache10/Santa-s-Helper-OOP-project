#pragma once
#include "IComponent.h"
#include <vector>

#include "Laptop.h"
#include "Car.h"
#include "PC.h"
#include "Bike.h"
#include "Scooter.h"
#include <iostream>
using namespace std;


template<typename T>
class Builder
{
private:
	vector<IComponent*> componentarray;

public:
	Builder(){}
	void addComponent(IComponent* component) {
		componentarray.push_back(component);
	}
	T* build()
	{
		T* object = new T;
		for (auto& it : componentarray)
		{
			object->getComponentInstance().push_back(it);
		}
		return object;
	}
};


