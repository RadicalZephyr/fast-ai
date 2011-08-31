#pragma once

#include <BWAPI.h>


#include "BaseManager/BaseManager.h"
#include "Cheese/Strategies.h"
#include "Cheese/StrategyManager.h"

class Cannonball : public BWAPI::AIModule {
public:
    Cannonball(void) : m_strategyMan(new CheeseStrategies::CannonAwesome()) {
    };

    virtual void onStart();
    virtual void onEnd(bool isWinner);
    virtual void onFrame();
    virtual void onSendText(std::string text);
    virtual void onReceiveText(BWAPI::Player* player, std::string text);
    virtual void onPlayerLeft(BWAPI::Player* player);
    virtual void onNukeDetect(BWAPI::Position target);
    virtual void onUnitDiscover(BWAPI::Unit* unit);
    virtual void onUnitEvade(BWAPI::Unit* unit);
    virtual void onUnitShow(BWAPI::Unit* unit);
    virtual void onUnitHide(BWAPI::Unit* unit);
    virtual void onUnitCreate(BWAPI::Unit* unit);
    virtual void onUnitDestroy(BWAPI::Unit* unit);
    virtual void onUnitMorph(BWAPI::Unit* unit);
    virtual void onUnitRenegade(BWAPI::Unit* unit);
    virtual void onSaveGame(std::string gameName);

private:
    CheeseStrategyManager m_strategyMan;
};
