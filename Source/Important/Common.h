#pragma once

#include <BWAPI.h>
#include "windows.h"

#include <list>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include "Important/Signals.h"
#include "Util/RelativePosition.h"
#include "Util/ResourceManager.h"

// Global Macro
#ifndef COMPILE_GLOBAL
  #define GLOBAL extern
#else
  #define GLOBAL
#endif

// Typedefs for standard containers for BWAPI Unit's
//   Note that BWAPI Unit's are ALWAYS pointers (don't make new ones!)
typedef std::set<BWAPI::Unit*> UnitSet;
typedef std::list<BWAPI::Unit*> UnitList;
typedef std::vector<BWAPI::Unit*> UnitVector;

typedef std::set<BWAPI::UnitType> UnitTypeSet;
typedef std::list<BWAPI::UnitType> UnitTypeList;

// Prototype for function that allows you to find what unit types a unit builds
// Usage: buildsWhat(UnitType)
namespace BWAPI {

    UnitTypeSet const &buildsWhat(UnitType unitType);
}

class UnitTrainingManager;

typedef boost::shared_ptr<UnitTrainingManager> UnitTrainingManagerPtr;
typedef std::set<UnitTrainingManagerPtr> UnitTrainingManagerSet;

class IUnitManagerBehaviour;

typedef boost::shared_ptr<IUnitManagerBehaviour> IUnitManager_BehaviourPtr;

class IUnitTrainingManagerBehaviour;

typedef boost::shared_ptr<IUnitTrainingManagerBehaviour> IUnitTrainingManager_BehaviourPtr;

struct UnitTrainingManager_BaseBehaviourFactory;

typedef std::map<BWAPI::UnitType, UnitTrainingManager_BaseBehaviourFactory*> UnitTrainingManager_factoryMap;

class BaseManager;

typedef boost::shared_ptr<BaseManager> BaseManagerPtr;
typedef std::set<BaseManagerPtr> BaseManagerSet;

class GatewayBehaviour;
class RoboticsBehaviour;

typedef boost::shared_ptr<GatewayBehaviour> GatewayBehaviourPtr;
typedef std::set<GatewayBehaviourPtr> GatewayBehaviourSet;

typedef boost::shared_ptr<RoboticsBehaviour> RoboticsBehaviourPtr;
typedef std::set<RoboticsBehaviourPtr> RoboticsBehaviourSet;

class ResourceManager;

/* globals */
GLOBAL int g_frame;
GLOBAL UnitTrainingManagerSet g_managers;
GLOBAL UnitTrainingManager_factoryMap g_managerWatchMap;
GLOBAL BaseManagerSet g_baseManagers;
GLOBAL RelativePosition g_position;
GLOBAL GatewayBehaviourSet g_gateways;
GLOBAL RoboticsBehaviourSet g_robotics;
GLOBAL ResourceManager g_resourceManager;

#define DEBUG(x) ::MessageBoxA(0, x, "Debugging", 0)
