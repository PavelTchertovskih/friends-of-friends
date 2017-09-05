#include <sstream>
#include <iostream>
#include "friends_of_friends.h"
using std::stringstream;
void social_network::add_user(const string& user, const list<string>& friends)
{
	auto u_ret = users.insert(pair<string, pair<Friends, News>>(user, {}));
	for (auto& i: friends)
	{
		auto ret = users.insert(pair<string, pair<Friends, News>>(i, {}));
		u_ret.first->second.first.friends_list.push_back(ret.first);
	}
}
void social_network::print_friendships(ostream& os) const
{
	for (auto& i: users)
	{
		//os << i.first;
		//os << "(" << i.first << ")";
		os << i.first;
		for(auto& j: i.second.first.friends_list)
		{
			//os << " <" << j->first << ">";
			os << " " << j->first; 
		}
		os << std::endl;
	}
}
void social_network::add_news(const iso_time& time, const string& user, const string& text)
{
	auto u_ret = users.insert(pair<string, pair<Friends, News>>(user, {}));
	u_ret.first->second.second.user_news[time] = text;
}
void social_network::print_news(ostream& os) const
{
	for (auto& i: users)
	{
		for (auto& j: i.second.second.user_news)
		{
			os << j.first << " ";//time
			os << i.first << " ";//author
			os << j.second << std::endl;//message
		}
	}
}
void social_network::read_news(istream& is)
{
	if (is.eof()) return;
	while (is.good())
	{
		iso_time t;
		string user;
		string text;
		is >> t;
		is >> user;
		getline(is, text);
		if (is.good() || is.eof() && text != "" && text != "\n")
			add_news(t, user, text);
		else
			break;
	}
}
void social_network::read_friends(istream& is)
{
	while (is.good())
	{
		stringstream ss;
		string user;
		list<string> friends;
		string line;
		getline(is, line);
		ss << line;
		ss >> user;
		while(ss.good())
		{
			string tmp;
			ss >> tmp;
			friends.push_back(tmp);
		}
		if (!user.empty() && user != " ")
			add_user(user, friends);

	}
}
bool social_network::cmp_news(const pair<iso_time, string>& A, const pair<iso_time, string>& B)
{
	cmp_iso_time tmp;
	return tmp.operator()(A.first, B.first);
}
//template </*map<string, pair<social_network::Friends, social_network::News>>::iterator*/> 
//bool social_network::find_in_list(const list<map<string, pair<social_network::Friends, social_network::News>>::iterator>& l, const map<string, pair<social_network::Friends, social_network::News>>::iterator& e);
/*template <typename T>
bool social_network::find_in_list(const list<T>& l, const T& e)*/
bool social_network::find_in_list(const list<map<string, pair<Friends, News>>::iterator>& l, const map<string, pair<Friends, News>>::iterator& e)
{
	for (auto& i: l)
	{
		if (i == e) return true;
	}
	return false;
}
pair<list<pair<iso_time, string>>, list<pair<iso_time, string>>> 
social_network::get_feed(const string& user) const
{
	//std::cout << user << std::endl;
	map<string, pair<Friends, News>>::const_iterator tmp = users.find(user);
	pair<list<pair<iso_time, string>>, list<pair<iso_time, string>>> feed;
	if (tmp == users.end()) 
	{
		return feed;
		//return pair< list<pair<iso_time, string>>, list<pair<iso_time, string>> > ({}, {});
	}
	const Friends& friends = tmp->second.first;
	Friends friends_of_friends;
	for (const auto& i: friends.friends_list)
	{
		for (const auto& k: i->second.second.user_news)
		{
			feed.first.push_back(pair<iso_time, string>(k.first, " " + i->first + k.second));
		}
		for(const auto& j: i->second.first.friends_list)
		{
			if(!find_in_list(friends.friends_list, j) && 
				!find_in_list(friends_of_friends.friends_list, j)&& 
				tmp != j)
			{
				friends_of_friends.friends_list.push_back(j);
				for (const auto& k: j->second.second.user_news)
				{
					feed.second.push_back(pair<iso_time, string>(k.first, " " + j->first + k.second));
				}
			}

		}
	}
	feed.first.sort(cmp_news);
	feed.second.sort(cmp_news);
	/*for (const auto& i: friends.friends_list)
		std::cout << i->first << " ";
	std::cout << std::endl;
	for (const auto& i: friends_of_friends.friends_list)
		std::cout << i->first << " ";
	std::cout << std::endl;*/
	/*std::cout << feed.first << std::endl;
	std::cout << feed.second << std::endl;*/
	return feed;
}
ostream& operator<<(ostream& out, const list<pair<iso_time, string>>& l)
{
	for(auto& i: l)
	{
		out << i.first << i.second << std::endl;
	}
	return out;
}
void social_network::dfs(map<string, int>& colors, const string& node) const
{
	int& corrent = colors[node];
	auto srch = users.find(node);
	//for(const auto& i: users[node].first.friends_list)
	for (auto& i: srch->second.first.friends_list)
	{
		int& next = colors[i->first];
		if (next == -1 || next > corrent)
		{
			next = corrent + 1;
			dfs(colors, i->first);
		}
	}
}
int social_network::path_length(const string& to, const string& from) const 
{
	auto s1 = users.find(to);
	if (s1 == users.end()) return -1;
	auto s2 = users.find(from);
	if (s2 == users.end()) return -1;
	if (to == from) return 0;
	map<string, int> colors;
	for (auto& i: users)
	{
		colors[i.first] = -1;
	}
	colors[from] = 0;
	dfs(colors, from);
	return colors[to];
}
