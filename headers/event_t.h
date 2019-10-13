#pragma once

#include "date.h"
#include <string>
#include <iostream>

struct Event_t {
    const Date date;
    const std::string event;
    Event_t(const Date & d, const std::string & ev);
};

std::ostream & operator << (std::ostream & os, const Event_t & e);
bool operator == (const Event_t & e1, const Event_t & e2);
bool operator != (const Event_t & e1, const Event_t & e2);
