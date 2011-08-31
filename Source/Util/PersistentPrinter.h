#pragma once

#include <string>
#include "Important/Signals.h"
#include <cstdio>
#include <stdarg.h>

class PersistentPrinter
{
public:
    PersistentPrinter(int x = 0, int y = 0) : m_printText(), m_x(x), m_y(y) {
   Signal::onFrame().connect(boost::bind(&PersistentPrinter::onFrame, this));
    }

    ~PersistentPrinter(void) {
   Signal::onFrame().disconnect(boost::bind(&PersistentPrinter::onFrame, this));
    }

    void onFrame(void) {
   BWAPI::Broodwar->drawTextScreen(m_x, m_y, "%s", m_printText);
    }

    void printf(const char *format, ...) {
   char buff[512];
   va_list ap;

        va_start(ap, format);
        vsnprintf_s(buff, 512, format, ap);
        va_end(ap);

        m_printText.assign(buff);
    }

private:
    std::string m_printText;
    int m_x;
    int m_y;
};
