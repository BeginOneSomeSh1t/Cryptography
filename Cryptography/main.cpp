#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <map>
#include <algorithm>
#include "math.h"
#include "binary.h"
#include "crypto.h"


int main()
{
	
	auto [public_key, private_key,n ,msg] {crypto::rsa_cipher("Hello World")};


	std::cout << "PubK: " << public_key << '\n'
		<< "PrivL: " << private_key << '\n'
		<< "Encrptd: " << msg << '\n';

	std::binary bin{ msg };
	std::size_t cipher_del{ bin };

	auto value{ std::fmod(std::pow(cipher_del, private_key), n) };

	std::binary to_str{ static_cast<size_t>(value)};

	std::cout << "Message: " << to_str.operator std::string();
	
}

