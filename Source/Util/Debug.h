#pragma once
#include <string>

class Debug
{
public:
    Debug(void);

private:
    void doSendText(std::string text);
    void doFrame(void);

    virtual void printDebug(void) = 0;
    virtual bool isMyUnitSelected(void) = 0;

    bool debug;
};


void setDebugSpeed(bool goDebugSuperFastCatCatCat);