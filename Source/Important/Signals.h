#pragma once

// Known issue with boost signals, generating a spurious warning so we suppress the warning
#pragma warning( push , 1 )
#pragma warning( disable : 4512 )

#include <boost/signal.hpp>

#pragma warning( pop )

#include <BWAPI.h>
#include <boost/bind.hpp>

//These emulate the callbacks by the BWAPI
//Use boost::bind to supply the correct function call
//returning true will remove the binding.  (NOT IMPLEMENTED YET)
namespace Signal
{

    //Register a start callback.
    //Only called once, so no need for return value
    boost::signal<void ()> &onStart(void);

    //Register an end callback.
    //Only called once, so no need for return value
    //1 = isWinner
    boost::signal<void (bool)> &onEnd();

    //Register a frame callback.
    boost::signal<void ()> &onFrame(void);

    //Register a sending_text callback.
    //1 = text
    boost::signal<void (std::string)> &onSendText(void);

    //Register a receiving_text callback.
    //1 = player
    //2 = text
    boost::signal<void (BWAPI::Player* player, std::string)> &onReceiveText(void);

    //Register a player_left callback.
    //1 = player
    boost::signal<void (BWAPI::Player* player)> &onPlayerLeft(void);

    //Register a nuke_detect callback.
    //1 = posistion
    boost::signal<void (BWAPI::Position target)> &onNukeDetect(void);

    //Register a unit discover callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onUnitDiscover(void);

    //Register a unit evade callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onUnitEvade(void);

    //Register a unit show callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onUnitShow(void);

    //Register a unit hide callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onUnitHide(void);

    //Register a friendly unit create callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onFriendlyUnitCreate(void);

    //Register an enemy unit create callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onEnemyUnitCreate(void);

    //Register a frienldy unit destroy callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onFriendlyUnitDestroy(void);

    //Register an enemy unit destroy callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onEnemyUnitDestroy(void);

    //Register a neutral unit destroy callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onNeutralUnitDestroy(void);

    //Register a unit morph callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onUnitMorph(void);

    //Register a unit renegade callback.
    //1 = unit
    boost::signal<void (BWAPI::Unit*)> &onUnitRenegade(void);

    //Register a on save game callback.
    //1 = gamename
    boost::signal<void (std::string)> &onSaveGame(void);

}

#define SIGNAL_ON_START(type) Signal::onStart().connect(boost::bind(& ## type ## ::onStart, this))
#define SIGNAL_OFF_START(type) Signal::onStart().disconnect(boost::bind(& ## type ## ::onStart, this))
#define SIGNAL_ON_FRAME(type) Signal::onFrame().connect(boost::bind(& ## type ## ::onFrame, this))
#define SIGNAL_OFF_FRAME(type) Signal::onFrame().disconnect(boost::bind(& ## type ## ::onFrame, this))
