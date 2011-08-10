#pragma once

#include "boost\function.hpp"
#include <queue>
#include <BWAPI.h>

struct BuildOrderElement
{
	typedef boost::function< void (BuildOrderElement* orderElement, BWAPI::Unit* builderProbe) > OnStartCallback;
	typedef boost::function< void (BWAPI::Unit* finishedBuilding, BWAPI::Unit* builderProbe) > OnDoneCallback;

	BuildOrderElement(BWAPI::UnitType type, OnStartCallback onStart, OnDoneCallback onDone, bool optional = false) : type(type), optional(optional), onStart(onStart), onDone(onDone) {}

	BWAPI::UnitType type;
	bool optional;
	OnDoneCallback onDone;
	OnStartCallback onStart;
};

class BuildOrder
{
public:
	BuildOrder();

	BWAPI::Unit* getLastBuilding(

private:
	std::queue<BuildOrderElement> buildQueue;
	std::list<BuildOrderElement> optionals;
};