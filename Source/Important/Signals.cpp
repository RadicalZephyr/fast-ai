#include "Signals.h"

namespace Signal
{

	//Register a start callback.
	//Only called once, so no need for return value
	boost::signal<void ()> &onStart(void) {
		static boost::signal<void ()> onStart;
		return onStart;
	}

	//Register an end callback.
	//Only called once, so no need for return value
	//1 = isWinner
	boost::signal<void (bool)> &onEnd() {
		static boost::signal<void (bool)> onEnd;
		return onEnd;
	}

	//Register a frame callback.
	boost::signal<void ()> &onFrame(void) {
		static boost::signal<void ()> onFrame;
		return onFrame;
	}

	//Register a sending_text callback.
	//1 = text
	boost::signal<void (std::string)> &onSendText(void) {
		static boost::signal<void (std::string)> onSendText;
		return onSendText;
	}

	//Register a receiving_text callback.
	//1 = player
	//2 = text
	boost::signal<void (BWAPI::Player* player, std::string)> &onReceiveText(void) {
		static boost::signal<void (BWAPI::Player* player, std::string)> onReceiveText;
		return onReceiveText;
	}

	//Register a player_left callback.
	//1 = player
	boost::signal<void (BWAPI::Player* player)> &onPlayerLeft(void) {
		static boost::signal<void (BWAPI::Player* player)> onPlayerLeft;
		return onPlayerLeft;
	}

	//Register a nuke_detect callback.
	//1 = posistion
	boost::signal<void (BWAPI::Position target)> &onNukeDetect(void) {
		static boost::signal<void (BWAPI::Position target)> onNukeDetect;
		return onNukeDetect;
	}

	//Register a unit discover callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onUnitDiscover(void) {
		static boost::signal<void (BWAPI::Unit*)> onUnitDiscover;
		return onUnitDiscover;
	}

	//Register a unit evade callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onUnitEvade(void) {
		static boost::signal<void (BWAPI::Unit*)> onUnitEvade;
		return onUnitEvade;
	}

	//Register a unit show callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onUnitShow(void) {
		static boost::signal<void (BWAPI::Unit*)> onUnitShow;
		return onUnitShow;
	}

	//Register a unit hide callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onUnitHide(void) {
		static boost::signal<void (BWAPI::Unit*)> onUnitHide;
		return onUnitHide;
	}

	//Register a friendly unit create callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onFriendlyUnitCreate(void) {
		static boost::signal<void (BWAPI::Unit*)> onFriendlyUnitCreate;
		return onFriendlyUnitCreate;
	}

	//Register an enemy unit create callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onEnemyUnitCreate(void) {
		static boost::signal<void (BWAPI::Unit*)> onEnemyUnitCreate;
		return onEnemyUnitCreate;
	}

	//Register a frienldy unit destroy callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onFriendlyUnitDestroy(void) {
		static boost::signal<void (BWAPI::Unit*)> onFriendlyUnitDestroy;
		return onFriendlyUnitDestroy;
	}

	//Register an enemy unit destroy callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onEnemyUnitDestroy(void) {
		static boost::signal<void (BWAPI::Unit*)> onEnemyUnitDestroy;
		return onEnemyUnitDestroy;
	}

	//Register a neutral unit destroy callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onNeutralUnitDestroy(void) {
		static boost::signal<void (BWAPI::Unit*)> onNeutralUnitDestroy;
		return onNeutralUnitDestroy;
	}

	//Register a unit morph callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onUnitMorph(void) {
		static boost::signal<void (BWAPI::Unit*)> onUnitMorph;
		return onUnitMorph;
	}

	//Register a unit renegade callback.
	//1 = unit
	boost::signal<void (BWAPI::Unit*)> &onUnitRenegade(void) {
		static boost::signal<void (BWAPI::Unit*)> onUnitRenegade;
		return onUnitRenegade;
	}

	//Register a on save game callback.
	//1 = gamename
	boost::signal<void (std::string)> &onSaveGame(void) {
		static boost::signal<void (std::string)> onSaveGame;
		return onSaveGame;
	}

}
