#include "Crypto.h"
#include <exception>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <modes.h>
#include <aes.h>
#include <filters.h>
#include <sha.h>
#include <hex.h>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <md5.h>
#include <osrng.h>
#include <tiger.h>
#include <whrlpool.h>
#include <ripemd.h>
#include <default.h>

using namespace crypt;

Crypto::Crypto(void)
{
}

Crypto::~Crypto(void)
{
}

void Crypto::setDefaultKey(string key)
{
	this->key = key;
}

void Crypto::setDefaultIV(string iv)
{
	this->iv = iv;
}

void Crypto::setDefaultPass(string pass)
{
	this->pass = pass;
}

string Crypto::encrypt(string plaintext, crypt::Method method, string pass)
{
	string ciphertext;
	switch (method)
	{
		case crypt::AES:
			{
				CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption e;
				e.SetKeyWithIV((byte*)key.c_str(), key.length(), (byte*)iv.c_str());

				// CFB mode must not use padding. Specifying
				//  a scheme will result in an exception
				CryptoPP::StringSource(plaintext, true, new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(ciphertext)));
			}
			break;
		case crypt::DEFAULT:
			{
				CryptoPP::StringSource ss1(plaintext, true, new CryptoPP::DefaultEncryptorWithMAC((byte*)pass.data(), pass.size(), new CryptoPP::HexEncoder(new CryptoPP::StringSink(ciphertext))));
			}
			break;
		default:
			break;
	}
	return ciphertext;
}

string Crypto::decrypt(string result_string, crypt::Method method, string pass)
{
	string decryptedtext;
	switch (method)
	{
		case crypt::AES:
			{
				CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption d;
				d.SetKeyWithIV((byte*)key.c_str(), key.length(), (byte*)iv.c_str());

				// The StreamTransformationFilter removes
				//  padding as required.
				CryptoPP::StringSource s(result_string, true, new CryptoPP::StreamTransformationFilter(d, new CryptoPP::StringSink(decryptedtext)));
			}
			break;
		case crypt::DEFAULT:
			{
				CryptoPP::StringSource ss2(result_string, true, new CryptoPP::HexDecoder(new CryptoPP::DefaultDecryptorWithMAC((byte*)pass.data(), pass.size(), new CryptoPP::StringSink(decryptedtext))));
			}
			break;
		default:
			break;
	}
	return decryptedtext;
}

string Crypto::hash(string value, crypt::Hash hash)
{
	string r = "";
	switch (hash)
	{
		case crypt::SHA1:
			{
				CryptoPP::SHA1 s1;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(s1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::TIGER:
			{
				CryptoPP::Tiger ti;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(ti, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::WHIRLPOOL:
			{
				CryptoPP::Whirlpool wp;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(wp, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::SHA224:
			{
				CryptoPP::SHA224 s2;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(s2, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::SHA384:
			{
				CryptoPP::SHA384 s3;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(s3, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::SHA512:
			{
				CryptoPP::SHA512 s5;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(s5, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::SHA256:
			{
				CryptoPP::SHA256 s2;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(s2, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::MD5:
			{
				CryptoPP::Weak::MD5 m5;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(m5, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::RIPEMD128:
			{
				CryptoPP::RIPEMD128 r1;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(r1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::RIPEMD160:
			{
				CryptoPP::RIPEMD160 r1;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(r1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::RIPEMD256:
			{
				CryptoPP::RIPEMD256 r1;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(r1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		case crypt::RIPEMD320:
			{
				CryptoPP::RIPEMD320 r1;
				CryptoPP::StringSource(value, true, new CryptoPP::HashFilter(r1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(r))));
			}
			break;
		default:
			break;
	}
	return r;
}

string Crypto::read(string value, crypt::Method method)
{
	ifstream t(value);
	string str((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
	str = decrypt(str, method, pass);
	return str;
}

void Crypto::write(string file, string text, crypt::Method method)
{
	text = encrypt(text, method, pass);
	ofstream myfile;
	myfile.open(file);
	myfile << text;
	myfile.close();
}

void Crypto::write(string file, string text, crypt::Hash hash)
{
	text = Crypto::hash(text, hash);
	ofstream myfile;
	myfile.open(file);
	myfile << text;
	myfile.close();
}

unsigned int Crypto::getKeyLength(void)
{
	return key.length();
}

unsigned int Crypto::getIVLength(void)
{
	return iv.length();
}