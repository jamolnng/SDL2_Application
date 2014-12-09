#pragma once
#include <string>

using namespace std;

namespace crypt
{
	enum Method
	{
		AES,
		DEFAULT
	};
	enum Hash
	{
		SHA1,
		SHA224,
		SHA256,
		SHA384,
		SHA512,
		MD5,
		TIGER,
		WHIRLPOOL,
		RIPEMD128,
		RIPEMD160,
		RIPEMD256,
		RIPEMD320
	};
};

class Crypto
{
	public:
		Crypto(void);
		~Crypto(void);

		void setDefaultKey(string key);
		void setDefaultIV(string iv);
		void setDefaultPass(string pass);

		string encrypt(string value, crypt::Method method, string pass = "");
		string decrypt(string value, crypt::Method method, string pass = "");

		string hash(string value, crypt::Hash hash);

		string read(string fileName, crypt::Method method);
		void write(string fileName, string text, crypt::Method method);
		void write(string fileName, string text, crypt::Hash hash);

		unsigned int getKeyLength(void);
		unsigned int getIVLength(void);

	private:
		string key;
		string iv;
		string pass;
};