#include <iostream>
#include <iomanip>
#include "my_time.h"
ostream& operator<<(ostream& os, const iso_time& t)
{	// format is 2014-10-20T08:00:00
	os << int(t.year + iso_time::epoch) << '-';
	os << std::setfill ('0') << std::setw (2);
	os << int(t.month) << '-';
	os << std::setfill ('0') << std::setw (2);
	os << int(t.day) << 'T';
	os << std::setfill ('0') << std::setw (2);
	os << int(t.hour) << ':';
	os << std::setfill ('0') << std::setw (2);
	os << int(t.min) << ':';
	os << std::setfill ('0') << std::setw (2);
	os << int(t.sec);
	return os;
}
istream& operator>>(istream& is, iso_time& t)
{
	char c;
	int tmp;
	is >> t.year;
	t.year -= iso_time::epoch;
	is >> c;//'-'
	is >> tmp; t.month = tmp;
	//is >> t.month;
	is >> c;//'_'
	is >> tmp; t.day = tmp;
	//is >> t.day;
	is >> c;//'T'
	is >> tmp; t.hour = tmp;
	//is >> t.hour;
	is >> c;//':'
	is >> tmp; t.min = tmp;
	//is >> t.min;
	is >> c;//':'
	is >> tmp; t.sec = tmp;
	//is >> t.sec;
	//not checking values
	if(is.good() || is.eof())
		return is;
	t = {0};
	return is;
}
bool cmp_iso_time::operator()(const iso_time& a, const iso_time& b) const
{
	// a >= b
	if (a.year > b.year) return true;
	if (a.year < b.year) return false;
	if (a.month > b.month) return true;
	if (a.month < b.month) return false;
	if (a.day > b.day) return true;
	if (a.day < b.day) return false;
	if (a.hour < b.hour) return false;
	if (a.hour > b.hour) return true;
	if (a.min < b.min) return false;
	if (a.min > b.min) return true;
	if (a.sec < b.sec) return false;
	if (a.sec > b.sec) return true;
	return false;
}
