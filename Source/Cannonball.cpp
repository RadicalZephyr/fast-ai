#include "Cannonball.h"
#include "Important/Common.h"

using namespace BWAPI;

void Cannonball::onStart()
{
    // Enable some cheat flags
    Broodwar->enableFlag(Flag::UserInput);
    // Uncomment to enable complete map information
    //Broodwar->enableFlag(Flag::CompleteMapInformation);

    std::set<Unit*>& startLocSet = Broodwar->getUnitsInRadius(BWAPI::Position(Broodwar->self()->getStartLocation()), 100);
    
	bool first = true;
    for (std::set<Unit*>::const_iterator i = startLocSet.begin(); i != startLocSet.end(); i++) {
        if ((*i)->getType().isResourceDepot()) {
            NexusManagerPtr manager(new NexusManager(*(*i)));
            managers.insert(manager);
        }
    }

    (*(managers.begin()))->findMinerals();

    for(std::set<Unit*>::const_iterator i=Broodwar->self()->getUnits().begin();i!=Broodwar->self()->getUnits().end();i++)
    {
        if ((*i)->getType().isWorker())
        {
			if(first == true)
			{
				probes = new ProbeControl(*i);
				probes->addProbe();
				first = false;
			}
			else
			{
				(*(managers.begin()))->addMiner(*i);
			}
		}
    }
}

void Cannonball::onEnd(bool isWinner)
{
    if (isWinner)
    {
        //log win to file
    }
}

void Cannonball::onSendText(std::string text)
{
    // This is the place to capture user input to do stuff with
}

void Cannonball::onReceiveText(BWAPI::Player* player, std::string text)
{
    Broodwar->printf("%s said '%s'", player->getName().c_str(), text.c_str());
}

void Cannonball::onPlayerLeft(BWAPI::Player* player)
{
    Broodwar->sendText("%s left the game.",player->getName().c_str());
}

void Cannonball::onNukeDetect(BWAPI::Position target)
{
    if (target!=Positions::Unknown)
        Broodwar->printf("Nuclear Launch Detected at (%d,%d)",target.x(),target.y());
    else
        Broodwar->printf("Nuclear Launch Detected");
}

void Cannonball::onUnitEvade(BWAPI::Unit* unit)
{
    if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
        Broodwar->sendText("A %s [%x] was last accessible at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}

void Cannonball::onUnitShow(BWAPI::Unit* unit)
{
    if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
        Broodwar->sendText("A %s [%x] has been spotted at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}

void Cannonball::onUnitHide(BWAPI::Unit* unit)
{
    if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
        Broodwar->sendText("A %s [%x] was last seen at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}

void Cannonball::onUnitDestroy(BWAPI::Unit* unit)
{
    if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
        Broodwar->sendText("A %s [%x] has been destroyed at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
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
}

void Cannonball::onUnitRenegade(BWAPI::Unit* unit)
{
    if (!Broodwar->isReplay())
        Broodwar->sendText("A %s [%x] is now owned by %s",unit->getType().getName().c_str(),unit,unit->getPlayer()->getName().c_str());
}

void Cannonball::onSaveGame(std::string gameName)
{
    Broodwar->printf("The game was saved to \"%s\".", gameName.c_str());
}

// The actually import callbacks to our AI
void Cannonball::onFrame()
{
	/* Global Update TODO: Move somewhere more general */
	g_frame = Broodwar->getFrameCount();

    if (Broodwar->isReplay())
        return;

	if(probes->inLocation()){
		Broodwar->printf("Happened");
		probes->nextLocation();
	}

    for (NexusManagerSet::const_iterator manager = managers.begin();
        manager != managers.end(); manager++) {
        (*manager)->onFrame();
    }

}

// Best place to do stuff with our units because going to be 
// called more for our units than the enemies
void Cannonball::onUnitCreate(BWAPI::Unit* unit)
{
    // The unit belongs to us
    if (unit->getPlayer() == Broodwar->self()) {
        //Broodwar->printf("Created a %s", unit->getType().getName().c_str());
		for (NexusManagerSet::const_iterator manager = managers.begin();
			manager != managers.end(); manager++) {
			(*manager)->onUnitCreate(unit);
		}
    }
}

// Probably mostly for responding to enemy units
void Cannonball::onUnitDiscover(BWAPI::Unit* unit)
{
    if (!Broodwar->isReplay() && Broodwar->getFrameCount()>1)
        Broodwar->sendText("A %s [%x] has been discovered at (%d,%d)",unit->getType().getName().c_str(),unit,unit->getPosition().x(),unit->getPosition().y());
}
