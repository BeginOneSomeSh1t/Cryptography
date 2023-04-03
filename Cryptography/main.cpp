#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <map>
#include <algorithm>
//#include "math.h"
#include "binary.h"
#include "crypto.h"


int main()
{
	
	

	try
	{
		auto [pub_key, pri_key, phi_mod, cipher] {crypto::rsa_cipher("I'm encrypted")};
		std::cout << "Public key: " << pub_key << '\n';
		std::cout << "Private key: " << pri_key << '\n';
		std::cout << "PhiMod: " << phi_mod << '\n';
		std::cout << "Cipher: " << cipher << '\n';

	}
	catch (std::binary_exception ex)
	{
		std::cout << ex.what();
	}
	

	/*auto calc{ [](int b, int q, int r) {return b * q + r; } };

	try
	{
		std::modulus<int> mod;

		std::cout << mod(2732 * 1323, 8800);

	}
	catch (std::exception ex)
	{
		std::cout << ex.what();
	}*/
	
}

