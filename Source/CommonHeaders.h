#pragma once

#include <BWAPI.h>
#include <list>
#include <vector>
#include <set>

#include <boost/shared_ptr.hpp>

typedef std::set<BWAPI::Unit*> UnitSet;
typedef std::list<BWAPI::Unit*> UnitList;
typedef std::vector<BWAPI::Unit*> UnitVector;

class NexusManager;

typedef boost::shared_ptr<NexusManager> NexusManagerPtr;
typedef std::set<NexusManagerPtr> NexusManagerSet;