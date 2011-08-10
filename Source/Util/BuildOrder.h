#pragma once

#include "Important\Common.h"
#include "boost\function.hpp"
#include <queue>
#include <BWAPI.h>

class BuildOrder;
struct BuildOrderElement;

typedef boost::function< void (BuildOrderElement* orderElement, BWAPI::Unit* builderProbe) > BuildOrderElementOnStartCallback;
typedef boost::function< void (BWAPI::Unit* finishedBuilding) > BuildOrderElementOnDoneCallback;

void BuildOrderElementOnStartVoid(BuildOrderElement* orderElement, BWAPI::Unit* builderProbe);
void BuildOrderElementOnDoneVoid(BWAPI::Unit* finishedBuilding);

struct BuildOrderElement
{
	friend class BuildOrder;

	BuildOrderElement(BWAPI::UnitType const& type, BWAPI::TilePosition const& position, bool optional = false, BuildOrderElementOnStartCallback onStart = &BuildOrderElementOnStartVoid, BuildOrderElementOnDoneCallback onDone = &BuildOrderElementOnDoneVoid) : type(type), position(position), optional(optional), onStart(onStart), onDone(onDone) {}

	BWAPI::TilePosition position;
	BWAPI::UnitType type;
	bool optional;

protected:
	// onDone not currently called.
	BuildOrderElementOnDoneCallback onDone;

	// onStart will be called after the order to build. This is good for queuing.
	BuildOrderElementOnStartCallback onStart;
};

class BuildOrder
{
public:
	typedef boost::function< void (BWAPI::Unit* builderProbe) > OnEndCallback;

	BuildOrder(OnEndCallback onEnd) : m_onEnd(onEnd) {}

	// This will add the element to the stack.
	// Optional elements will be poped off the stack as they appear.
	// The top non optional element is used first
	void addOrderElement(BuildOrderElement const& newOrder);
	void addOptionalElement(BuildOrderElement const& newOrder);

	void start(BWAPI::Unit* probe);
	BWAPI::Unit* stop();

private:
	void onFrame();

	BuildOrderElement* m_currentBuildOrder;

	BWAPI::Unit* m_probe;

	std::queue<BuildOrderElement> m_buildQueue;
	std::list<BuildOrderElement> m_optionals;

	OnEndCallback m_onEnd;

	void clearOptionals(void);
};