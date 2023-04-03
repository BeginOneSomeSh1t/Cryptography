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

	try
	{
		std::binary<64> bin{ "100000u" };
		std::string bin_str{ bin.to_string(decltype(bin)::_String) };

		std::binary<64> bin_dec{ bin_str };

		std::cout << "String as ullong: " << bin_dec.to_ullong() << '\n';
		std::cout << "String as string: " << bin_dec.to_string(decltype(bin_dec)::_String) << '\n';
	}
	catch (std::binary_exception ex)
	{
		std::cout << ex.what();
	}
	

	
	
	
	
	
	
}

