#include <string>
#include <iostream>
#include "math.h"
#include "crypto.h"
#include <fstream>


std::string prompt(const std::string& _Display)
{
	std::cout << _Display;
	std::string out{ std::istream_iterator<char>{std::cin}, {} };
	//std::cin.clear();
	return out;
}
void programm_hang()
{
	std::cout << "Please, press enter to continue";
	getchar();
}

void rsa_implementation()
{
	std::cin.unsetf(std::ios::skipws);
	auto get_char{ [] { auto ch{getchar()}; /*reset*/ getchar(); return ch; } };
	while (true)
	{
		std::cout << "Choose action (E - encrypt, D - Decrypt) : ";



		switch (char c{ static_cast<char>(get_char()) }; static_cast<char>(toupper(c)))
		{
		case 'E':
		{
			std::cin.clear();
			std::string user_msg{prompt("Enter a message to encrypt, then press enter and then Ctrl + Z and enter again: ")};
			auto [codded, public_key, private_key, n] { crypto::rsa_cipher(user_msg) };
			std::cout << "Your encrypted message to use is: ";
			std::copy(std::begin(codded), std::end(codded), std::ostream_iterator<std::size_t>{std::cout, " "});
			std::cout << '\n';
			std::ofstream fout{ "Layout.txt" };
			if (!fout.is_open())
			{
				std::cout << "File error, press enter to continue";
				get_char();
				return;
			}

			helpers::do_n{ codded.size(), [&](auto i)
				{
					fout << codded[i] << ' ';
					if (i == codded.size() - 1)
							fout << 0;
				} };
			fout << ' ';
			fout << public_key << ' '
				<< private_key << ' ' << n;

			std::cout << "Pass your friend the encrypted file. Bye!";
			std::cout << "\nPress enter to continue...";
			get_char();
			fout.close();
			return;

		}
		break;
		case 'D':
		{
			std::cin.clear();
			std::cout << "Point a path to a file: ";
			std::string input{ std::istream_iterator<char>{std::cin}, {} };

			// delete unneccessary symbols
			const char symbols[]{ "\t\n\x1a" };
			const size_t first(input.find_first_not_of(symbols));
			if (std::string::npos == first)
				return;
			const size_t last(input.find_last_not_of(symbols));
			const std::string path{ input.substr(first, (last - first + 1)) };

			// open file
			std::ifstream fin{ path.c_str() };
			if (!fin.is_open())
			{
				std::cout << "File error. Press enter to continue";
				get_char();
				return;
			}

			std::vector<int> encoded;

			int num{ 0 };
			while (!fin.eof())
			{
				fin >> num;
				if (num == 0)
					break;
				encoded.push_back(num);
			}

			int pub_k = 0, priv_k = 0, n = 0;
			fin >> pub_k;
			fin >> priv_k;
			fin >> n;

			fin.close();

			crypto::rsa_bundle bundle{ std::make_tuple(encoded, pub_k, priv_k, n) };

			std::string decrypted_msg{ crypto::rsa_cipher(bundle) };

			std::cout << "The decrypted message is: " << decrypted_msg;
			std::cout << "Bye!";
			std::cout << "\nPress enter to continue...";
			get_char();
			return;
		}
		break;
		default: std::cout << "You choose wrong answer \n";
			break;
		}
	}
}

void otp_implementation()
{
	std::cin.unsetf(std::ios::skipws);
	auto get_char{ [] { char ch{static_cast<char>(getchar())}; /*reset*/ getchar(); return ch; } };
	while (true)
	{
		std::cout << "Choose action (E - encrypt, D - Decrypt) : ";
		std::string str;
		switch (std::getline(std::cin, str); std::toupper(str[0]))
		{
		case 'E':
		{
			std::string user_msg{prompt("Enter a message to encrypt: ")};
			auto bundle{ crypto::otp_cipher(user_msg) };

			std::cout << "Your message was encrypted. \n";
			std::cout << "Cipher text is: " << bundle._Text << '\n';
			std::cout << "Keyword is: " << bundle._Keyword << '\n';
			std::cout << "Pass your friend the cipher text and the keyword so that he can know what is the genuine content. Bye!\n";
			programm_hang();
		}
		break;
		case 'D':
		{
			std::string cipher_keyword{prompt("Enter a cipher text and a keyword: ")};
			auto it{ std::find_if(std::begin(cipher_keyword), std::end(cipher_keyword), [](auto& c)
				{
					return c == ' ';
				}) };
			auto decrypted_msg{ crypto::otp_cipher({std::string{std::begin(cipher_keyword), it}, std::string{it + 1, std::end(cipher_keyword)}, true})};
			std::cout << '\n';
			std::cout << "Decrypted message is " << decrypted_msg << '\n';
			programm_hang();
		}
		break;
		default: std::cout << "You choose wrong answer \n";
			break;
		}
	}
}

int main()
{
	otp_implementation();
}
