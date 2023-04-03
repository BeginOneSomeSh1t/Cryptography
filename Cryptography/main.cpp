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
	
	/*auto [public_key, private_key,n ,msg] {crypto::rsa_cipher("Hello World")};


	std::cout << "PubK: " << public_key << '\n'
		<< "PrivL: " << private_key << '\n'
		<< "Encrptd: " << msg << '\n';*/

	
	size_t big_del{ 128u };
	std::binary<8> bin{ big_del };
	std::string bin_str{ bin.to_string(decltype(bin)::_String) };

	std::binary<8> bin_dec{ bin_str };
	std::cout << bin_dec.to_ullong();
	
	
	
	
	
	
}

