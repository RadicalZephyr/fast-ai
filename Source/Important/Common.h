#pragma once

#include <BWAPI.h>
#include <list>
#include <vector>
#include <set>

#include <boost/shared_ptr.hpp>

// Global Macro
#ifndef COMPILE_GLOBAL
  #define GLOBAL extern
#else
  #define GLOBAL
#endif

class Debug;

typedef std::set<Debug*> DebugSet;

#include "Signals.h"

typedef std::set<BWAPI::Unit*> UnitSet;
typedef std::list<BWAPI::Unit*> UnitList;
typedef std::vector<BWAPI::Unit*> UnitVector;

class NexusManager;

typedef boost::shared_ptr<NexusManager> NexusManagerPtr;
typedef std::set<NexusManagerPtr> NexusManagerSet;

class BuildingManager;

typedef boost::shared_ptr<BuildingManager> BuildingManagerPtr;
typedef std::set<BuildingManagerPtr> BuildingManagerSet;

/* globals */
GLOBAL int g_frame;
GLOBAL DebugSet debuggers;
GLOBAL BuildingManagerSet managers;