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

/* globals */
GLOBAL int g_frame;

typedef std::set<BWAPI::Unit*> UnitSet;
typedef std::list<BWAPI::Unit*> UnitList;
typedef std::vector<BWAPI::Unit*> UnitVector;

class NexusManager;

typedef boost::shared_ptr<NexusManager> NexusManagerPtr;
typedef std::set<NexusManagerPtr> NexusManagerSet;