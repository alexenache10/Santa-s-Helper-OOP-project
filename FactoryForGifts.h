#pragma once

#include "Car.h"
#include "Scooter.h"
#include "Bike.h"
#include "Laptop.h"
#include "PC.h"

namespace FactoryGifts {
	enum class Types{Car, Scooter, Bike, Laptop, PC};
	static Gift* getGift(Types type, std::string giftType)
	{
		switch (type)
		{
		case Types::Bike:
			return new Bike(giftType);
		case Types::Car:
			return new Car(giftType);
		case Types::Laptop:
			return new Laptop(giftType);
		case Types::PC:
			return new PC(giftType);
		case Types::Scooter:
			return new Scooter(giftType);
		}
	}
}