#include "date.h"
#include <exception>
#include <iomanip>

Date::Date(int y, int m, int d)
    : year(y), month(m), day(d) {}

bool operator == (const Date & d1, const Date & d2)
{
    return d1.year == d2.year && d1.month == d2.month && d1.day == d2.day;
}

bool operator != (const Date & d1, const Date & d2)
{
    return !(d1 == d2);
}

bool operator < (const Date & d1, const Date & d2)
{
    if(d1.year != d2.year)
        return d1.year < d2.year;
    else if (d1.month != d2.month)
        return d1.month < d2.month;
    else
        return d1.day < d2.day;
}

bool operator <= (const Date & d1, const Date & d2)
{
    return !(d2 < d1);
}

bool operator > (const Date & d1, const Date & d2)
{
    return d2 < d1;
}

bool operator >= (const Date & d1, const Date & d2)
{
    return !(d1 < d2);
}



std::ostream & operator << (std::ostream & os,
                                   const Date & d)
{
    char last_fill = os.fill('0');
    os << std::setw(4) << d.year << '-' << std::setw(2) << d.month << '-' << std::setw(2) << d.day;
    os.fill(last_fill);
    return os;
}

Date ParseDate(std::istream & is)
{
    int y, m, d;
    char ch1, ch2;
    if (is >> y >> ch1 >> m >> ch2 >> d
        && ch1 == '-' && ch2 == '-')
        return {y, m, d};
    else
        throw std::invalid_argument("Bad date's format");
}
