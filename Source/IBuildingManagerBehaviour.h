#pragma once
#include <BWAPI.h>
#include <boost\shared_ptr.hpp>

class IBuildingManagerBehaviour
{
public:

	virtual void postBuild(BWAPI::Unit *unit) = 0;
	virtual bool shouldBuild(BWAPI::UnitType *) {return true;}

};

typedef boost::shared_ptr<IBuildingManagerBehaviour> IBM_BehaviourPtr;

template<class T>
struct BM_BehaviourFactory {

	IBM_BehaviourPtr operator()(BWAPI::Unit *unit) {
		IBM_BehaviourPtr newPtr(static_cast<IBuildingManagerBehaviour *>(new T(unit)));
		return newPtr;
	}
};