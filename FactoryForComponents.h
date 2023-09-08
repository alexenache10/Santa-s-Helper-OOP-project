#pragma once


#include "bikeframe.h"
#include "Case.h"
#include "Door.h"
#include "Engine.h"
#include "Motherboard.h"
#include "Wheel.h"
#include "Processor.h"
#include "Videocard.h"

namespace FactoryComponents
{
	enum class Types { bikeframe, Case, Door, Engine, Motherboard, Wheel, Processor, Videocard};
	static IComponent* getType(Types type)
	{
		switch (type)
		{
		case Types::bikeframe:
			return new bikeframe;
		case Types::Case:
			return new Case;
		case Types::Door:
			return new Door;
		case Types::Engine:
			return new Engine;
		case Types::Motherboard:
			return new Motherboard;
		case Types::Wheel:
			return new Wheel;
		case Types::Processor:
			return new Processor;
		case Types::Videocard:
			return new Videocard;
		
		}
	}
}