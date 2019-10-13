#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "test_runner.h"

#include <sstream>
using namespace std;

void TestDatabaseAddAndPrint()
{
    {
        Database db;
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), "", "Simple print");
    }
    {
        Database db;
        db.Add({1,1,1}, "event1");
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), "0001-01-01 event1\n", "Single add");
    }
    {
        Database db;
        db.Add({1,1,1}, "event1");
        db.Add({1,1,1}, "event1");
        db.Add({1,1,1}, "event1");
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), "0001-01-01 event1\n", "Dubble add");
    }
    {
        Database db;
        db.Add({3,1,1}, "event3");
        db.Add({1,1,1}, "event1");
        db.Add({2,1,1}, "event2");
        db.Add({1,1,1}, "event1");
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), "0001-01-01 event1\n" "0002-01-01 event2\n" "0003-01-01 event3\n", "Multi add");
    }
}


void TestDatabaseFindIf()
{
    Database db;
    db.Add({2057,8,8}, "event1");
    db.Add({2017,7,8}, "event1");
    db.Add({2011,1,1}, "event2");

    {
        istringstream is("");
        auto condition = ParseCondition(is);
        auto predicate = [&condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        vector<Event_t> rez {{{2011,1,1}, "event2"}, {{2017,7,8}, "event1"}, {{2057,8,8}, "event1"}};
        AssertEqual(db.FindIf(predicate), rez, "Find empty condition");
    }
    {
        istringstream is("date == 2017-07-08");
        auto condition = ParseCondition(is);
        auto predicate = [&condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        vector<Event_t> rez {{{2017,7,8}, "event1"}};
        AssertEqual(db.FindIf(predicate), rez, "Find single date");
    }
    {
        istringstream is("event == \"event1\"");
        auto condition = ParseCondition(is);
        auto predicate = [&condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        vector<Event_t> rez {{{2017,7,8}, "event1"}, {{2057,8,8}, "event1"}};
        AssertEqual(db.FindIf(predicate), rez, "Find single event");
    }
    {
        istringstream is("date <= 2017-07-08 AND event == \"event1\"");
        auto condition = ParseCondition(is);
        auto predicate = [&condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        vector<Event_t> rez {{{2017,7,8}, "event1"}};
        AssertEqual(db.FindIf(predicate), rez, "Find date and event");
    }
    {
        istringstream is("event == \"event3\"");
        auto condition = ParseCondition(is);
        auto predicate = [&condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        vector<Event_t> rez;
        AssertEqual(db.FindIf(predicate), rez, "Not found");
    }

}


void TestDatabaseRemoveIf()
{
    {
        Database db;
        db.Add({2057,8,8}, "event1");
        db.Add({2017,7,8}, "event1");
        db.Add({2011,1,1}, "event2");
        istringstream is("date == 2017-07-08");
        auto condition = ParseCondition(is);
        auto predicate = [&condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        AssertEqual(db.RemoveIf(predicate), 1, "Delete date");
    }
    {
        Database db;
        db.Add({2057,8,8}, "event1");
        db.Add({2017,7,8}, "event1");
        db.Add({2011,1,1}, "event2");
        istringstream is("event == \"event1\"");
        auto condition = ParseCondition(is);
        auto predicate = [&condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        AssertEqual(db.RemoveIf(predicate), 2, "Delete event");
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), "2011-01-01 event2\n", "Delete event");
    }
    {
        Database db;
        db.Add({2057,8,8}, "event1");
        db.Add({2017,7,8}, "event1");
        db.Add({2011,1,1}, "event2");
        istringstream is("date <= 2017-08-08 AND event == \"event1\"");
        auto condition = ParseCondition(is);
        auto predicate = [&condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        AssertEqual(db.RemoveIf(predicate), 1, "Delete date and event");
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), "2011-01-01 event2\n" "2057-08-08 event1\n", "Delete date and event");
    }
    {
        Database db;
        db.Add({2057,8,8}, "event1");
        db.Add({2011,1,1}, "event2");
        istringstream is("event == \"event1\" OR event == \"event2\"");
        auto condition = ParseCondition(is);
        auto predicate = [&condition](const Date& date, const string& event) {
          return condition->Evaluate(date, event);
        };
        AssertEqual(db.RemoveIf(predicate), 2, "Delete all");
        ostringstream os;
        db.Print(os);
        AssertEqual(os.str(), "", "Delete all");
    }
}


void TestDatabaseLast()
{
    Database db;
    db.Add({2057,8,8}, "event1");
    db.Add({2017,7,8}, "event2");
    db.Add({2011,1,1}, "event3");
    db.Add({2063,2,3}, "event4");
    db.Add({2011,1,1}, "event5");
    db.Add({2011,1,1}, "event6");
    db.Add({2017,7,8}, "event7");

    AssertEqual(db.Last({2011,1,1}), Event_t({2011,1,1}, "event6"), "Last with one event in date");
    AssertEqual(db.Last({2011,1,2}), Event_t({2011,1,1}, "event6"), "");

    bool was_exception = false;
    try {
        db.Last({2010,1,2});
    } catch (invalid_argument&) {
        was_exception = true;
    }
    AssertEqual(was_exception, true, "Exception");
}






