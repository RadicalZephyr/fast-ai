#include "Cannonball.h"

#include "Important/Common.h"
#include "Util/Debug.h"
#include "Util/Functions.h"
#include "UnitTrainingManager\Behaviours/NexusBehaviour.h"
#include "UnitTrainingManager\Behaviours/DefaultBehaviour.h"
#include "Cheese/StrategyManager.h"
#include "UnitTrainingManager/Behaviours/GatewayBehaviour.h"

using namespace BWAPI;

void Cannonball::onStart()
{
  // Enable some cheat flags
  Broodwar->enableFlag(Flag::UserInput);
  setDebugSpeed(true);
  // Uncomment to enable complete map information
  //Broodwar->enableFlag(Flag::CompleteMapInformation);

  // Creation of the g_managerWatchMap.  Nexii get a specialized behaviour, all other buildings get the default (PRODUCE SOMETHING!!)
  g_managerWatchMap.insert(std::make_pair(BWAPI::UnitTypes::Protoss_Nexus,
    static_cast<UnitTrainingManager_BaseBehaviourFactory *>(new BM_BehaviourFactory<NexusBehaviour>)));
  // Gateways produce zealots, and then make a class to cause the zealots to wander the map
  g_managerWatchMap.insert(std::make_pair(BWAPI::UnitTypes::Protoss_Gateway,
    static_cast<UnitTrainingManager_BaseBehaviourFactory *>(new BM_BehaviourFactory<GatewayBehaviour>)));

  // Default behaviours
  g_managerWatchMap.insert(std::make_pair(BWAPI::UnitTypes::Protoss_Carrier,
    static_cast<UnitTrainingManager_BaseBehaviourFactory *>(new BM_BehaviourFactory<DefaultBehaviour>)));
  g_managerWatchMap.insert(std::make_pair(BWAPI::UnitTypes::Protoss_Reaver,
    static_cast<UnitTrainingManager_BaseBehaviourFactory *>(new BM_BehaviourFactory<DefaultBehaviour>)));
	//g_managerWatchMap.insert(std::make_pair(BWAPI::UnitTypes::Protoss_Stargate,
	//									  static_cast<UnitTrainingManager_BaseBehaviourFactory *>(new BM_BehaviourFactory<DefaultBehaviour>)));
	//g_managerWatchMap.insert(std::make_pair(BWAPI::UnitTypes::Protoss_Robotics_Facility,
	//									  static_cast<UnitTrainingManager_BaseBehaviourFactory *>(new BM_BehaviourFactory<DefaultBehaviour>)));

	// Register to check the watch map every time we create a unit
	Signal::onFriendlyUnitCreate().connect(boost::bind(&checkForBuildings, _1, g_managerWatchMap));

	Signal::onStart()();

  std::set<BWAPI::TilePosition> startLocs = Broodwar->getStartLocations();

  //char buff[2048];
  //int point = 0;
  //point += sprintf(buff, "Num locations: %d\n", startLocs.size());

  //for (std::set<BWAPI::TilePosition>::iterator itr = startLocs.begin();
  //      itr != startLocs.end(); ++itr) {
  //        point += sprintf(buff+point, "x: %d, y: %d\n", itr->x(), itr->y());

  //}
  //PersistentPrinter *printer = new PersistentPrinter;

  //printer->printf("%s", buff);
}

void Cannonball::onSendText(std::string text)
{
    // This is the place to capture user input to do stuff with
	//Broodwar->printf("onSendText called: '%s'", text.c_str());

	if (UnitTypes::getUnitType(text) != UnitTypes::None) {
		UnitTypeSet const buildSet = buildsWhat(UnitTypes::getUnitType(text));
		//Broodwar->printf("%s can build:\n", UnitTypes::getUnitType(text).getName().c_str());
		for (UnitTypeSet::const_iterator itr = buildSet.begin(); itr != buildSet.end(); itr++) {
			Broodwar->printf("%s", itr->getName().c_str());
		}
	}
	Signal::onSendText()(text);
}

// The actually import callbacks to our AI
void Cannonball::onFrame()
{
	/* Global Update TODO: Move somewhere more general */
	g_frame = Broodwar->getFrameCount();

    if (Broodwar->isReplay())
        return;

	//if(probes->inLocation()) {
	//	Broodwar->printf("Happened");
	//	probes->nextLocation();
	//}
	Signal::onFrame()();
}

// Best place to do stuff with our units because going to be 
// called more for our units than the enemies
void Cannonball::onUnitCreate(BWAPI::Unit* unit)
{
    // The unit belongs to us
    if (unit->getPlayer() == Broodwar->self()) {
        //Broodwar->printf("Created a %s", unit->getType().getName().c_str());
		Signal::onFriendlyUnitCreate()(unit);
    } else {
		Signal::onEnemyUnitCreate()(unit);
	}
}

// Probably mostly for responding to enemy units
void Cannonball::onUnitDiscover(BWAPI::Unit* unit)
{
    //if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
    //    Broodwar->sendText("A %s [%x] has been discovered at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());

	Signal::onUnitDiscover()(unit);
}

void Cannonball::onUnitShow(BWAPI::Unit* unit)
{
    //if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
    //    Broodwar->sendText("A %s [%x] has been spotted at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());

	Signal::onUnitShow()(unit);
}



/// Relatively unused callbacks

void Cannonball::onEnd(bool isWinner)
{
	Signal::onEnd()(isWinner);
}

void Cannonball::onReceiveText(BWAPI::Player* player, std::string text)
{
    //Broodwar->printf("%s said '%s'", player->getName().c_str(), text.c_str());

	Signal::onReceiveText()(player, text);
}

void Cannonball::onPlayerLeft(BWAPI::Player* player)
{
    //Broodwar->sendText("%s left the game.",player->getName().c_str());

	Signal::onPlayerLeft()(player);
}

void Cannonball::onNukeDetect(BWAPI::Position target)
{
    //if (target!=Positions::Unknown)
    //    Broodwar->printf("Nuclear Launch Detected at (%d,%d)",target.x(),target.y());
    //else
    //    Broodwar->printf("Nuclear Launch Detected");

	Signal::onNukeDetect()(target);
}

void Cannonball::onUnitEvade(BWAPI::Unit* unit)
{
    //if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
    //    Broodwar->sendText("A %s [%x] was last accessible at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());

	Signal::onUnitEvade()(unit);
}

void Cannonball::onUnitHide(BWAPI::Unit* unit)
{
    //if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
    //    Broodwar->sendText("A %s [%x] was last seen at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());

	Signal::onUnitHide()(unit);
}

void Cannonball::onUnitDestroy(BWAPI::Unit* unit)
{
    //if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
    //    Broodwar->sendText("A %s [%x] has been destroyed at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());

    if (unit->getPlayer() == Broodwar->self()) {
		Signal::onFriendlyUnitDestroy()(unit);
	} else if (unit->getPlayer()->getType() == PlayerTypes::Neutral) {
		Signal::onNeutralUnitDestroy()(unit);
	} else {
		Signal::onEnemyUnitDestroy()(unit);
	}
}

void Cannonball::onUnitMorph(BWAPI::Unit* unit)
{
    if (!Broodwar->isReplay())
        Broodwar->sendText("A %s [%x] has been morphed at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
    else
    {
        /*if we are in a replay, then we will print out the build order
        (just of the buildings, not the units).*/
        if (unit->getType().isBuilding() && unit->getPlayer()->isNeutral()==false)
        {
            int seconds=Broodwar->getFrameCount()/24;
            int minutes=seconds/60;
            seconds%=60;
            Broodwar->sendText("%.2d:%.2d: %s morphs a %s",minutes,seconds,unit->getPlayer()->getName().c_str(),unit->getType().getName().c_str());
        }
    }

	Signal::onUnitMorph()(unit);
}

void Cannonball::onUnitRenegade(BWAPI::Unit* unit)
{
    //if (!Broodwar->isReplay())
    //    Broodwar->sendText("A %s [%x] is now owned by %s",unit->getType().getName().c_str(),unit,unit->getPlayer()->getName().c_str());

	Signal::onUnitRenegade()(unit);
}

void Cannonball::onSaveGame(std::string gameName)
{
    //Broodwar->printf("The game was saved to \"%s\".", gameName.c_str());

	Signal::onSaveGame()(gameName);
}
