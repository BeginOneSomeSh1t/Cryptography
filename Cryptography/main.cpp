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
	
	auto [public_key, private_key, msg] {crypto::rsa_cipher("hi")};

	std::cout << "PubK: " << public_key << '\n'
		<< "PrivL: " << private_key << '\n'
		<< "Encrptd: " << msg << '\n';

	
}

