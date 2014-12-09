#include "Properties.h"
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> Split(const string& s, const string& delim, const bool keep_empty = true)
{
	vector<string> result;
	if (delim.empty())
	{
		result.push_back(s);
		return result;
	}
	string::const_iterator substart = s.begin(), subend;
	while (true)
	{
		subend = search(substart, s.end(), delim.begin(), delim.end());
		string temp(substart, subend);
		if (keep_empty || !temp.empty())
		{
			result.push_back(temp);
		}
		if (subend == s.end())
		{
			break;
		}
		substart = subend + delim.size();
	}
	return result;
}

Properties::Properties(void)
{
}

Properties::Properties(string fileName)
{
	load(fileName);
}

Properties::Properties(string fileName, string key, string iv, crypt::Method method)
{
	load(fileName, key, iv, method);
}

Properties::Properties(string fileName, string pass, crypt::Method method)
{
	load(fileName, pass, method);
}

Properties::~Properties(void)
{
}

void Properties::load(string fileName)
{
	std::ifstream fs(fileName);
	if (fs.is_open())
	{
		string line = "";
		while (fs.good())
		{
			getline(fs, line);
			if (line.at(0) != '#')
			{
				vector<string> prop = Split(line, ":");
				props.insert(pair<string, string>(prop[0], line.substr(prop[0].length() + 1)));
			}
		}
		fs.close();
	}
}

void Properties::load(string fileName, string key, string iv, crypt::Method method)
{
	Crypto c;
	c.setDefaultIV(iv);
	c.setDefaultKey(key);
	string f = c.read(fileName, method);
	vector<string> s = Split(f, "\|");
	for (string str : s)
	{
		vector<string> prop = Split(str, ":");
		props.insert(pair<string, string>(prop[0], str.substr(prop[0].length() + 1)));
	}
}

void Properties::load(string fileName, string pass, crypt::Method method)
{
	Crypto c;
	c.setDefaultPass(pass);
	string f = c.read(fileName, method);
	vector<string> s = Split(f, "\|");
	for (string str : s)
	{
		vector<string> prop = Split(str, ":");
		props.insert(pair<string, string>(prop[0], str.substr(prop[0].length() + 1)));
	}
}

string Properties::gets(string name)
{
	if (props.find(name) == props.end())
	{
		return "";
	}
	else
	{
		return props.find(name)->second;
	}
}

int Properties::geti(string name)
{
	if (props.find(name) == props.end())
	{
		return 0;
	}
	else
	{
		return stoi(props.find(name)->second);
	}
}

bool Properties::getb(string name)
{
	if (props.find(name) == props.end())
	{
		return 0;
	}
	else
	{
		string v = props.find(name)->second;
		if (v == "1" || v == "true" || v == "TRUE" || v == "True")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

std::map<string, string> Properties::get(void)
{
	return props;
}