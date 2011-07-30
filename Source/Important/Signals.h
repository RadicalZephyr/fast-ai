#pragma once

// Known issue with boost signals, generating a spurious warning so we suppress the warning
#pragma warning( push , 1 )
#pragma warning( disable : 4512 )

#include <boost/signal.hpp>

#pragma warning( pop )

#include "boost\bind.hpp"
#include "Important/Common.h"

//These emulate the callbacks by the BWAPI
//Use boost::bind to supply the correct function call
//returning true will remove the binding.
namespace Signal
{

	//Register a start callback.
	//Only called once, so no need for return value
	GLOBAL boost::signal<void ()> onStart;

	//Register an end callback.
	//Only called once, so no need for return value
	//1 = isWinner
	GLOBAL boost::signal<void (bool)> onEnd;

	//Register a frame callback.
	GLOBAL boost::signal<void ()> onFrame;

	//Register a sending_text callback.
	//1 = text
	GLOBAL boost::signal<void (std::string)> onSendText;

	//Register a receiving_text callback.
	//1 = player
	//2 = text
	GLOBAL boost::signal<void (BWAPI::Player* player, std::string)> onReceiveText;

	//Register a player_left callback.
	//1 = player
	GLOBAL boost::signal<void (BWAPI::Player* player)> onPlayerLeft;

	//Register a nuke_detect callback.
	//1 = posistion
	GLOBAL boost::signal<void (BWAPI::Position target)> onNukeDetect;

	//Register a unit discover callback.
	//1 = unit
	GLOBAL boost::signal<void (BWAPI::Unit*)> onUnitDiscover;

	//Register a unit evade callback.
	//1 = unit
	GLOBAL boost::signal<void (BWAPI::Unit*)> onUnitEvade;

	//Register a unit show callback.
	//1 = unit
	GLOBAL boost::signal<void (BWAPI::Unit*)> onUnitShow;

	//Register a unit hide callback.
	//1 = unit
	GLOBAL boost::signal<void (BWAPI::Unit*)> onUnitHide;

	//Register a friendly unit create callback.
	//1 = unit
	GLOBAL boost::signal<void (BWAPI::Unit*)> onFriendlyUnitCreate;

	//Register an enemy unit create callback.
	//1 = unit
	GLOBAL boost::signal<void (BWAPI::Unit*)> onEnemyUnitCreate;

	//Register a unit destroy callback.
	//1 = unit
	GLOBAL boost::signal<void (BWAPI::Unit*)> onUnitDestroy;

	//Register a unit morph callback.
	//1 = unit
	GLOBAL boost::signal<void (BWAPI::Unit*)> onUnitMorph;

	//Register a unit renegade callback.
	//1 = unit
	GLOBAL boost::signal<void (BWAPI::Unit*)> onUnitRenegade;

	//Register a on save game callback.
	//1 = gamename
	GLOBAL boost::signal<void (std::string)> onSaveGame;

}