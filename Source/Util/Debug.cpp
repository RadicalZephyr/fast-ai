#include "Debug.h"

void Debug::doFrame(void) {
    if (debug) {
        printDebug();
    }
}

void Debug::doSendText(std::string text) {
    if (isMyUnitSelected() && text.compare("/debug")) {
        debug = !debug;
    }
}