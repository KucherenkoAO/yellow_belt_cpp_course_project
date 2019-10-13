#pragma once

#include "date.h"
#include "node.h"
#include "event_t.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using dateToEvents_vector = std::map<Date, std::vector<std::string>>;
using dateToEvents_set = std::map<Date, std::set<std::string>>;

class Database
{
public:
    Database() {}
    void Add(const Date & d, const std::string & event);
    void Print(std::ostream & os) const;

    template <typename F>
    int RemoveIf(F predicate) {
        int count = 0;
        for (auto it = events_v.begin(); it != events_v.end(); ) {
            auto &d = it->first;
            auto &vect_events = it->second;
            auto &set_events = events_s[d];

            auto it_end = std::stable_partition(vect_events.begin(), vect_events.end(),
                                     [&d, predicate](const std::string &event) {return !predicate(d, event);});
            count += vect_events.end() - it_end;
            for(auto i = it_end; i != vect_events.end(); i++)
                set_events.erase(*i);
            vect_events.erase(it_end, vect_events.end());

            if (vect_events.empty()){
                it = events_v.erase(it);
                events_s.erase(d);
            }
            else
                ++it;
        }
        return count;
    }

    template <typename F>
    std::vector<Event_t> FindIf(F predicate) const {
        std::vector<Event_t> rezult;
        for (const auto & [date, all_events] : events_v) {
            const auto &d = date;
            std::for_each(all_events.begin(), all_events.end(),
                          [&rezult, &d, predicate](const std::string &event)
            {
                if (predicate(d, event)) {
                    std::ostringstream os;
                    os << d << ' ' << event;

                    rezult.push_back({d, event});
                }
            });
        }
        return rezult;
    }
    Event_t Last(const Date & d) const;
private:
    dateToEvents_vector events_v;
    dateToEvents_set events_s;
};

void TestDatabaseAddAndPrint();
void TestDatabaseFindIf();
void TestDatabaseRemoveIf();
void TestDatabaseLast();
