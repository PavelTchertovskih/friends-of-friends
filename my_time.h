#ifndef MY_TIME_H
#define MY_TIME_H
#include <istream>
#include <ostream>
using std::istream;
using std::ostream;
typedef unsigned char uchar;
typedef unsigned int uint;
struct iso_time
{
	uint year;
	uchar month;
	uchar day;
	uchar hour;
	uchar min;
	uchar sec;
	static const uint epoch = 1970;
};
ostream& operator<<(ostream&, const iso_time&);
istream& operator>>(istream&, iso_time&);
struct cmp_iso_time
{
	bool operator()(const iso_time&, const iso_time&) const;
};
#endif
