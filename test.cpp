#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include "friends_of_friends.h"
using namespace std;
/*TEST(fof_test, test_00)
{
	social_network sn;
	sn.add_user("B{abc}", list<string>{"a", "b", "c"});
	sn.add_user("C{bde}", list<string>{"b", "d", "e"});
	sn.add_user("D{abcdefg}", list<string>{"a", "b", "c", "d" , "e", "f", "g"});
	sn.add_user("a{123}", list<string>{"1", "2", "3"});
	sn.add_news({2000-iso_time::epoch, 1, 1, 1, 1, 1}, "user1", "hello");
	sn.add_news({2000-iso_time::epoch, 2, 1, 1, 1, 1}, "user2", "hello");
	sn.add_news({2000-iso_time::epoch, 1, 4, 1, 1, 1}, "user3", "hello");
	sn.add_news({2000-iso_time::epoch, 1, 4, 6, 1, 1}, "user4", "hello");
	sn.add_news({2000-iso_time::epoch, 1, 1, 1, 8, 2}, "user5", "hello");
	sn.add_news({2000-iso_time::epoch, 1, 1, 1, 8, 1}, "user6", "hello");
	sn.add_news({2000-iso_time::epoch, 1, 1, 1, 1, 1}, "user7", "hello");
	sn.add_news({2000-iso_time::epoch, 1, 1, 1, 1, 2}, "user8", "hello");
	sn.print_friendships(cout);
	sn.print_news(cout);
	stringstream fs, ns;
	fs << "vasya kolya petya sasha" << endl;
	fs << "sasha vasya cool123 petya" << endl;
	fs << "cool123 kolya" << endl;
	fs << "kolya cool123" << endl;
	ns << "2014-10-20T08:00:00 vasya Блин, сегодня опять понедельник :(" << endl;
	ns << "2014-10-20T08:05:00 cool123 Ура, понедельник!!!" << endl;
	ns << "2014-10-20T08:51:00 kolya Какой сегодня день?" << endl;
	ns << "2014-10-20T08:39:00 bolotnik 1" << endl;
	ns << "2014-10-20T08:39:00 bolotnik 2" << endl;
	ns << "2014-10-20T08:39:00 bolotnik 3" << endl;
	ns << "2014-10-20T08:39:00 bolotnik 4" << endl;
	ns << "2014-10-20T08:39:00 bolotnik 5" << endl;
	ns << "2014-10-20T08:39:00 bolotnik 6" << endl;
	ns << "2014-10-20T08:39:00 bolotnik 7" << endl;
	ns << "2014-10-20T08:39:00 bolotnik 8";
	sn.read_news(ns);
	sn.read_friends(fs);
	sn.print_friendships(cout);
	sn.print_news(cout);
	cout << endl;
	auto feed = sn.get_feed("vasya");
	cout << feed.first << endl;
	cout << feed.second << endl;
}*/
TEST(friends_of_friends_test, test_01)//testing add_user and path_length
{
	social_network sn;
	sn.add_user("1", list<string>{"3", "5", "7", "9"});
	sn.add_user("2", list<string>{"4", "6", "8", "10"});
	sn.add_user("3", list<string>{"1", "5", "7", "9"});
	sn.add_user("4", list<string>{"2", "6", "8", "10"});
	sn.add_user("5", list<string>{"1", "3", "7", "9"});
	sn.add_user("6", list<string>{"2", "4", "8", "10"});
	sn.add_user("7", list<string>{"1", "3", "5", "9"});
	sn.add_user("8", list<string>{"2", "4", "6", "10"});
	sn.add_user("9", list<string>{"1", "3", "5", "7"});
	sn.add_user("10", list<string>{"2", "4", "6", "8"});
	stringstream ss1, ss2;
	sn.print_friendships(ss1);
	ss2 << "1 3 5 7 9" << endl;
	ss2 << "10 2 4 6 8" << endl;
	ss2 << "2 4 6 8 10" << endl;
	ss2 << "3 1 5 7 9" << endl;
	ss2 << "4 2 6 8 10" << endl;
	ss2 << "5 1 3 7 9" << endl;
	ss2 << "6 2 4 8 10" << endl;
	ss2 << "7 1 3 5 9" << endl;
	ss2 << "8 2 4 6 10" << endl;
	ss2 << "9 1 3 5 7" << endl;
	string s1, s2;
	while (ss1.good() && ss2.good())
	{
		getline(ss1, s1);
		getline(ss2, s2);
		//cout << s1 << endl;
		//cout << s2 << endl;
		EXPECT_TRUE(s1 == s2);
	}
	for (int i = 1; i <= 10; i++)
	{
		for (int j = 1; j <= 10; j++)
		{
			int rez = sn.path_length(to_string(i), to_string(j));
			if (i == j)
				EXPECT_TRUE(rez == 0);
			else if (i % 2 == j % 2)
				EXPECT_TRUE(rez == 1);
			else 
				EXPECT_TRUE(rez == -1);
		}
	}
	EXPECT_TRUE(sn.path_length("-1", "1") == -1);
	EXPECT_TRUE(sn.path_length("-1", "-1") == -1);
	EXPECT_TRUE(sn.path_length("3", "11") == -1);
	EXPECT_TRUE(sn.path_length("667", "1") == -1);
}
TEST(friends_of_friends_test, test_02)//testing add_news
{
	social_network sn;
	sn.add_news({2002-iso_time::epoch, 2, 1, 1, 1, 1}, "user", "0");
	sn.add_news({2002-iso_time::epoch, 1, 2, 1, 1, 1}, "user", "1");
	sn.add_news({2001-iso_time::epoch, 2, 2, 1, 1, 1}, "user", "2");
	sn.add_news({2001-iso_time::epoch, 2, 1, 2, 1, 1}, "user", "3");
	sn.add_news({2001-iso_time::epoch, 1, 2, 2, 1, 1}, "user", "4");
	sn.add_news({2001-iso_time::epoch, 1, 2, 1, 2, 1}, "user", "5");
	sn.add_news({2001-iso_time::epoch, 1, 1, 2, 2, 1}, "user", "6");
	sn.add_news({2001-iso_time::epoch, 1, 1, 2, 1, 2}, "user", "7");
	sn.add_news({2001-iso_time::epoch, 1, 1, 1, 2, 2}, "user", "8");
	sn.add_news({2001-iso_time::epoch, 1, 1, 1, 2, 1}, "user", "9");
	sn.add_news({2001-iso_time::epoch, 1, 1, 1, 1, 2}, "user", "10");
	sn.add_news({2001-iso_time::epoch, 1, 1, 1, 1, 1}, "user", "11");
	stringstream ss1, ss2;
	ss1 << "2002-02-01T01:01:01 user 0" << endl;
	ss1 << "2002-01-02T01:01:01 user 1" << endl;
	ss1 << "2001-02-02T01:01:01 user 2" << endl;
	ss1 << "2001-02-01T02:01:01 user 3" << endl;
	ss1 << "2001-01-02T02:01:01 user 4" << endl;
	ss1 << "2001-01-02T01:02:01 user 5" << endl;
	ss1 << "2001-01-01T02:02:01 user 6" << endl;
	ss1 << "2001-01-01T02:01:02 user 7" << endl;
	ss1 << "2001-01-01T01:02:02 user 8" << endl;
	ss1 << "2001-01-01T01:02:01 user 9" << endl;
	ss1 << "2001-01-01T01:01:02 user 10" << endl;
	ss1 << "2001-01-01T01:01:01 user 11" << endl;
	sn.print_news(ss2);
	string s1, s2;
	while(ss1.good() && ss2.good())
	{
		getline(ss1, s1);
		getline(ss2, s2);
		EXPECT_TRUE(s1 == s2);
		//cout << s1 << endl;
		//cout << s2 << endl;
	}
}
TEST(friends_of_friends_test, test_03)//testing read_friends
{
	social_network sn;
	stringstream ss1, ss2;
	ss1 << "1 3 5 7 9" << endl;
	ss1 << "10 2 4 6 8" << endl;
	ss1 << "2 4 6 8 10" << endl;
	ss1 << "3 1 5 7 9" << endl;
	ss1 << "4 2 6 8 10" << endl;
	ss1 << "5 1 3 7 9" << endl;
	ss1 << "6 2 4 8 10" << endl;
	ss1 << "7 1 3 5 9" << endl;
	ss1 << "8 2 4 6 10" << endl;
	ss1 << "9 1 3 5 7" << endl;
	ss2 << "1 3 5 7 9" << endl;
	ss2 << "10 2 4 6 8" << endl;
	ss2 << "2 4 6 8 10" << endl;
	ss2 << "3 1 5 7 9" << endl;
	ss2 << "4 2 6 8 10" << endl;
	ss2 << "5 1 3 7 9" << endl;
	ss2 << "6 2 4 8 10" << endl;
	ss2 << "7 1 3 5 9" << endl;
	ss2 << "8 2 4 6 10" << endl;
	ss2 << "9 1 3 5 7" << endl;
	sn.read_friends(ss1);
	ss1 << "1 3 5 7 9" << endl;
	ss1 << "10 2 4 6 8" << endl;
	ss1 << "2 4 6 8 10" << endl;
	ss1 << "3 1 5 7 9" << endl;
	ss1 << "4 2 6 8 10" << endl;
	ss1 << "5 1 3 7 9" << endl;
	ss1 << "6 2 4 8 10" << endl;
	ss1 << "7 1 3 5 9" << endl;
	ss1 << "8 2 4 6 10" << endl;
	ss1 << "9 1 3 5 7" << endl;
	string s1, s2;
	while(ss1.good() && ss2.good())
	{
		getline(ss1, s1);
		getline(ss2, s2);
		EXPECT_TRUE(s1 == s2);
		//cout << s1 << endl;
		//cout << s2 << endl;
	}
}
TEST(friends_of_friends_test, test_04)//testing read_news
{
	social_network sn;
	stringstream ss1, ss2;
	ss1 << "2002-02-01T01:01:01 user 0" << endl;
	ss1 << "2002-01-02T01:01:01 user 1" << endl;
	ss1 << "2001-02-02T01:01:01 user 2" << endl;
	ss1 << "2001-02-01T02:01:01 user 3" << endl;
	ss1 << "2001-01-02T02:01:01 user 4" << endl;
	ss1 << "2001-01-02T01:02:01 user 5" << endl;
	ss1 << "2001-01-01T02:02:01 user 6" << endl;
	ss1 << "2001-01-01T02:01:02 user 7" << endl;
	ss1 << "2001-01-01T01:02:02 user 8" << endl;
	ss1 << "2001-01-01T01:02:01 user 9" << endl;
	ss1 << "2001-01-01T01:01:02 user 10" << endl;
	ss1 << "2001-01-01T01:01:01 user 11" << endl;
	ss2 << "2002-02-01T01:01:01 user 0" << endl;
	ss2 << "2002-01-02T01:01:01 user 1" << endl;
	ss2 << "2001-02-02T01:01:01 user 2" << endl;
	ss2 << "2001-02-01T02:01:01 user 3" << endl;
	ss2 << "2001-01-02T02:01:01 user 4" << endl;
	ss2 << "2001-01-02T01:02:01 user 5" << endl;
	ss2 << "2001-01-01T02:02:01 user 6" << endl;
	ss2 << "2001-01-01T02:01:02 user 7" << endl;
	ss2 << "2001-01-01T01:02:02 user 8" << endl;
	ss2 << "2001-01-01T01:02:01 user 9" << endl;
	ss2 << "2001-01-01T01:01:02 user 10" << endl;
	ss2 << "2001-01-01T01:01:01 user 11" << endl;
	sn.read_news(ss1);
	ss1 << "2002-02-01T01:01:01 user 0" << endl;
	ss1 << "2002-01-02T01:01:01 user 1" << endl;
	ss1 << "2001-02-02T01:01:01 user 2" << endl;
	ss1 << "2001-02-01T02:01:01 user 3" << endl;
	ss1 << "2001-01-02T02:01:01 user 4" << endl;
	ss1 << "2001-01-02T01:02:01 user 5" << endl;
	ss1 << "2001-01-01T02:02:01 user 6" << endl;
	ss1 << "2001-01-01T02:01:02 user 7" << endl;
	ss1 << "2001-01-01T01:02:02 user 8" << endl;
	ss1 << "2001-01-01T01:02:01 user 9" << endl;
	ss1 << "2001-01-01T01:01:02 user 10" << endl;
	ss1 << "2001-01-01T01:01:01 user 11" << endl;
	string s1, s2;
	while(ss1.good() && ss2.good())
	{
		getline(ss1, s1);
		getline(ss2, s2);
		EXPECT_TRUE(s1 == s2);
		//cout << s1 << endl;
		//cout << s2 << endl;
	}
}
TEST(friends_of_friends_test, test_05)//testing get_fee and path_length
{
	stringstream friendships;
	friendships << "1 2 3" << endl;
	friendships << "2 4 5" << endl;
	friendships << "3 6 7" << endl;
	friendships << "4 8 9" << endl;
	friendships << "5 10 11" << endl;
	friendships << "6 12 13" << endl;
	friendships << "7 14 15" << endl;
	stringstream news;
	news << "2001-01-01T01:01:01 1 1" << endl;
	news << "2001-01-01T02:01:01 2 2" << endl;
	news << "2001-01-01T03:01:01 3 3" << endl;
	news << "2001-01-01T04:01:01 4 4" << endl;
	news << "2001-01-01T05:01:01 5 5" << endl;
	news << "2001-01-01T06:01:01 6 6" << endl;
	news << "2001-01-01T07:01:01 7 7" << endl;
	news << "2001-01-01T08:01:01 8 8" << endl;
	news << "2001-01-01T09:01:01 9 9" << endl;
	news << "2001-01-01T10:01:01 10 10" << endl;
	news << "2001-01-01T11:01:01 11 11" << endl;
	news << "2001-01-01T12:01:01 12 12" << endl;
	news << "2001-01-01T13:01:01 13 13" << endl;
	news << "2001-01-01T14:01:01 14 14" << endl;
	news << "2001-01-01T15:01:01 15 15" << endl;
	social_network sn;
	sn.read_news(news);
	sn.read_friends(friendships);
	//sn.print_friendships(cout);
	//sn.print_news(cout);
	auto feed = sn.get_feed("1");
	//cout << feed.first;
	//cout << feed.second;
	stringstream f, fof;
	f << feed.first;
	fof << feed.second;
	stringstream fe, fofe;
	fe << "2001-01-01T03:01:01 3 3" << endl;
	fe << "2001-01-01T02:01:01 2 2" << endl;
	fofe << "2001-01-01T07:01:01 7 7" << endl;
	fofe << "2001-01-01T06:01:01 6 6" << endl;
	fofe << "2001-01-01T05:01:01 5 5" << endl;
	fofe << "2001-01-01T04:01:01 4 4" << endl;
	string s1, s2;
	while (fe.good() && f.good())
	{
		getline(f, s1);
		getline(fe, s2);
		//cout << s1 << endl;
		//cout << s2 << endl;
		EXPECT_TRUE(s1 == s2);
	}
	while (fofe.good() && fof.good())
	{
		getline(fof, s1);
		getline(fofe, s2);
		//cout << s1 << endl;
		//cout << s2 << endl;
		EXPECT_TRUE(s1 == s2);
	}
	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= 15; j++)
		{
			//cout << sn.path_length(to_string(i), to_string(j)) << " " << i << " " << j << endl;
			if (i == j)
				EXPECT_TRUE(sn.path_length(to_string(j), to_string(i)) == 0);
			else if (i*2 == j || i*2+1 == j)
				EXPECT_TRUE(sn.path_length(to_string(j), to_string(i)) == 1);
			else if (j >= i*4 && j <= (i*2+1)*2+1)
				EXPECT_TRUE(sn.path_length(to_string(j), to_string(i)) == 2);
			else if (i == 1 && j >= 8 && j <= 15)
				EXPECT_TRUE(sn.path_length(to_string(j), to_string(i)) == 3);
			else EXPECT_TRUE(sn.path_length(to_string(j), to_string(i)) == -1);
		}
}
int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
