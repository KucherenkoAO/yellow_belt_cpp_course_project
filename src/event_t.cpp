#include "event_t.h"

Event_t::Event_t(const Date & d, const std::string & ev)
    : date(d), event(ev) {}

std::ostream & operator << (std::ostream & os, const Event_t & e)
{
    os << e.date << ' ' << e.event;
    return os;
}

bool operator == (const Event_t & e1, const Event_t & e2)
{
    return e1.date == e2.date && e1.event == e2.event;
}

bool operator != (const Event_t & e1, const Event_t & e2)
{
    return !(e1 == e2);
}
