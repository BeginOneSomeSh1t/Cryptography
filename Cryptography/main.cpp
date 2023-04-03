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
	
	

	/*try
	{
		auto [pub_key, pri_key, phi_mod, cipher] {crypto::rsa_cipher("Small")};
		std::cout << "Public key: " << pub_key << '\n';
		std::cout << "Private key: " << pri_key << '\n';
		std::cout << "PhiMod: " << phi_mod << '\n';
		std::cout << "Cipher: " << cipher << '\n';

	}
	catch (std::binary_exception ex)
	{
		std::cout << ex.what();
	}*/
	

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

	/*std::string str{ "I'm encrypted" };

	std::string out;

	for (auto it{ std::begin(str) }; it != std::end(str); ++it)
	{
		auto octane{ std::bitset<8>{static_cast<size_t>(*it)}.to_string()};
		out += octane;
	}

	std::cout << "binary out: " << out << '\n';

	std::string decoded;

	
	for (auto it{ std::begin(out) }; it != std::end(out); it+=8)
	{
		char dcd_ch{ static_cast<char>(std::bitset<8>{std::string{it, it + 8}}.to_ullong())};
		decoded += dcd_ch;
	}

	std::cout << "decoded string: " << decoded << '\n';*/


	/*std::binary<8> bin_str{ "I'm encrypted" };

	std::cout << "Binary: " << bin_str._Bin_Str << '\n';
	std::cout << "String: " << bin_str.to_string() << '\n';
	std::cout << "Ullong: " << bin_str.to_ullong() << '\n';

	std::cout << std::bitset<8>{bin_str.to_ullong()}.to_string();*/
	

	/*size_t cipher{ 2673 };

	std::cout << "Cipher is " << cipher << '\n';

	std::binary<8> bin_ciph{ cipher };

	std::cout << "Binary of cipher is: " << bin_ciph._Bin_Str << '\n';
	std::cout << "String representation is: " << bin_ciph.to_string() << '\n';

	std::binary<8> bin_cipher_from_str{ bin_ciph.to_string() };

	std::cout << "Binary cipher from string: " << bin_cipher_from_str._Bin_Str << '\n';
	std::cout << "String representation is: " << bin_cipher_from_str.to_string() << '\n';
	std::cout << "Ullong representation is: " << bin_cipher_from_str.to_ullong() << '\n';*/
	

	/*std::string bin{ "01110001" };

	size_t counted{ 0u };

	for (auto it{ std::begin(bin) }; it != std::end(bin); ++it)
	{
		counted = (counted * 2) + static_cast<size_t>(*it - '0');
	}

	std::cout << "Composed number from binary: " << counted << '\n';

	std::string decomposed_bin;

	while (counted >= 1)
	{
		decomposed_bin += std::to_string(counted % 2);
		counted /= 2;
	}

	

	std::string res;
	std::copy(std::rbegin(decomposed_bin), std::rend(decomposed_bin), std::back_inserter(res));

	std::cout << "Decomposed number from binary: " << res;*/

	std::binary bin_hi{ "hi" };
	size_t del{ bin_hi.to_ullong() };
	std::binary bin_del{ del };
	std::string str_hi{ bin_del.to_string() };

}

