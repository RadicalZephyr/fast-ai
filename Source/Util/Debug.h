#pragma once
#include <string>

class Debug
{
public:
    Debug(void);
    ~Debug(void);

    void doSendText(std::string text);
    void doFrame(void);

    virtual void printDebug(void) = 0;
    virtual bool isMyUnitSelected(void) = 0;

private:
    bool debug;
};
