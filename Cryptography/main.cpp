#include <string>
#include <iostream>
#include "math.h"
#include "crypto.h"


int main()
{
	


	auto bundle{ crypto::rsa_cipher("Encrypted Message") };

	auto ecnrypted{ std::get<0>(bundle) };
	std::cout << "Encrypted message: ";
	for (auto& e : ecnrypted)
		std::cout << e;

	std::cout << '\n';

	auto decrp_msg{ crypto::rsa_cipher(bundle) };
	std::cout << "Decrypted message: " << decrp_msg;

}
