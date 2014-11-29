#pragma once

#include <map>
#include <string>
#include "Crypto.h"

using namespace std;

class Properties
{
	public:
		Properties(void);
		Properties(string fileName);
		Properties(string fileName, string key, string iv, crypt::Method method);
		Properties(string fileName, string pass, crypt::Method method);
		~Properties(void);

		void load(string fileName);
		void load(string fileName, string key, string iv, crypt::Method method);
		void load(string fileName, string pass, crypt::Method method);
		string gets(string propertyName);
		int geti(string propertyName);
		bool getb(string propertyName);

		std::map<string, string> get(void);

	private:
		std::map<string, string> props;
};