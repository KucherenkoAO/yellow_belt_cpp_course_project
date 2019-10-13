#include "database.h"
#include <exception>

using namespace std;

void Database::Add(const Date & d, const std::string & event) {
    auto &vect_events = events_v[d];
    auto &set_events = events_s[d];
    if (set_events.find(event) == set_events.end()){
        vect_events.push_back(event);
        set_events.insert(event);
    }
}

void Database::Print(std::ostream & os) const {
    for (const auto & [date, all_events] : events_v) {
        for (const auto & event : all_events){
            os << date << ' ' << event << endl;
        }
    }
}

Event_t Database::Last(const Date & d) const {
    auto it = events_v.upper_bound(d);
    if (it == events_v.begin())
        throw std::invalid_argument("");
    --it;
    auto date = it->first;
    auto event = *((it)->second.rbegin());
    return {date, event};
}
