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

typedef boost::function<bool (BWAPI::UnitType)> boolUnitTypeFunc;
typedef boost::function<void (BWAPI::Unit *)> voidUnitFunc;

typedef boost::tuple<BWAPI::UnitType, boolUnitTypeFunc, voidUnitFunc> managerWatchTriple;
typedef std::vector<managerWatchTriple> managerWatchVector;

/* globals */
GLOBAL int g_frame;
GLOBAL DebugSet debuggers;
GLOBAL BuildingManagerSet managers;