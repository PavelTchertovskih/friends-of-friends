#ifndef FRIENDS_OF_FRIENDS_H
#define FRIENDS_OF_FRIENDS_H
#include <list>
#include <map>
#include <string>
//#include <istream>
#include <ostream>
//using std::istream;
#include "my_time.h"
using std::ostream;
using std::list;
using std::map;
using std::string;
using std::pair;
class social_network
{
	struct Friends;
	struct News;
	map<string, pair<Friends, News>> users;
	//   user   his friends
	//дружба не симметрична, юзер подписан на новости своих друзей
	struct Friends
	{
		list<map<string, pair<Friends, News>>::iterator> friends_list;
	};
	struct News
	{
		map<iso_time, string, cmp_iso_time> user_news;
	};
	/*template<typename T> 
	static bool find_in_list(const list<T>&, const T&);*/
	static bool find_in_list(const list<map<string, pair<Friends, News>>::iterator>&, const map<string, pair<Friends, News>>::iterator&);
	static bool cmp_news(const pair<iso_time, string>&, const pair<iso_time, string>&);
	void dfs(map<string, int>& colors, const string& node) const;
public:
	void add_user(const string& user, const list<string>& friends);
	void print_friendships(ostream& os) const;
	void add_news(const iso_time& time, const string& user, const string& text);
	void print_news(ostream& os) const;
	void read_news(istream& is);
	void read_friends(istream& is);
	pair< list<pair<iso_time, string>>, list<pair<iso_time, string>> > get_feed(const string& user) const;
	int path_length(const string&, const string&) const;
};
ostream& operator<<(ostream& out, const list<pair<iso_time, string>>&);
#endif
