#pragma once

#include <BWAPI.h>
#include <list>
#include <vector>
#include <set>

#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/function.hpp>

// Global Macro
#ifndef COMPILE_GLOBAL
  #define GLOBAL extern
#else
  #define GLOBAL
#endif

class Debug;

typedef std::set<Debug*> DebugSet;

typedef std::set<BWAPI::Unit*> UnitSet;
typedef std::list<BWAPI::Unit*> UnitList;
typedef std::vector<BWAPI::Unit*> UnitVector;

class NexusManager;

typedef boost::shared_ptr<NexusManager> NexusManagerPtr;
typedef std::set<NexusManagerPtr> NexusManagerSet;

class BuildingManager;

typedef boost::shared_ptr<BuildingManager> BuildingManagerPtr;
typedef std::set<BuildingManagerPtr> BuildingManagerSet;

typedef boost::function<bool (BWAPI::UnitType)> BM_shouldBuildFunc;
typedef boost::function<void (BWAPI::Unit *)> BM_postBuildFunc;

struct managerWatchTriple {
	BWAPI::UnitType    watchUnit;
	BM_shouldBuildFunc shouldBuildCallback;
	BM_postBuildFunc   postBuildCallback;
};
typedef boost::tuple<BWAPI::UnitType, BM_shouldBuildFunc, BM_postBuildFunc> ;
typedef std::vector<managerWatchTriple> managerWatchVector;

/* globals */
GLOBAL int g_frame;
GLOBAL DebugSet debuggers;
GLOBAL BuildingManagerSet managers;