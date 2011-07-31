#include "Important/Common.h"
#include "Debug.h"

Debug::Debug(void) : debug(false) {
	// Register with the global debug manager
	debuggers.insert(this);
	Signal::onFrame().connect(boost::bind(&Debug::doFrame, this));
	Signal::onSendText().connect(boost::bind(&Debug::doSendText, this, _1));
}

Debug::~Debug(void) {
	debuggers.erase(this);
}

void Debug::doFrame(void) {
    if (debug) {
        printDebug();
    }
}

void Debug::doSendText(std::string text) {
    if (isMyUnitSelected() && !(text.compare("/debug"))) {
        debug = !debug;
    }
}

// Default implementations of the virtual functions debug defines so we don't get mysterious crashes
// or link errors.  Instead we get a mysterious spam message when we turn debug mode on!!
void Debug::printDebug(void) {
	BWAPI::Broodwar->printf("UNIMPLEMENTED printDebug method");
}

bool Debug::isMyUnitSelected(void) {
	BWAPI::Broodwar->printf("DBG isMyUnitSelected");
	return true;
}