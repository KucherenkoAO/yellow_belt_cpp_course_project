#pragma once

#include <iostream>

class Date
{
public:
    Date(int y, int m, int d);
    friend bool operator <  (const Date & d1, const Date & d2);
    friend bool operator <= (const Date & d1, const Date & d2);
    friend bool operator >  (const Date & d1, const Date & d2);
    friend bool operator >= (const Date & d1, const Date & d2);
    friend bool operator == (const Date & d1, const Date & d2);
    friend bool operator != (const Date & d1, const Date & d2);
    friend std::ostream & operator << (std::ostream & os, const Date & d);
private:
    int year, month, day;
};

Date ParseDate(std::istream & is);
