#pragma once
#include <string>
#include <bitset>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>


namespace std
{
	struct binary
	{
		string binary_string;
		explicit binary(const string& _Init)
		{
			for (auto& c : _Init)
				binary_string += bitset<8>(c).to_string();
		}
		explicit binary(int _Del)
		{
			//reversed string of a correct binary number
			string bin;
			// short division by two with reaminder being a binary 0 or 1
			while (_Del >= 1)
			{
				bin += std::to_string(_Del % 2);
				_Del /= 2;
			}
			// inreverse and copy the string to binary_string
			copy(rbegin(bin), rend(bin), back_inserter(binary_string));
		}
		explicit binary(size_t _Del)
		{
			//reversed string of a correct binary number
			string bin;
			// short division by two with reaminder being a binary 0 or 1
			while (_Del >= 1)
			{
				bin += std::to_string(_Del % 2);
				_Del /= 2;
			}
			// inreverse and copy the string to binary_string
			copy(rbegin(bin), rend(bin), back_inserter(binary_string));
		}
		static int to_integer(const string& _BinStr) 
		{
			vector<int> binary_int;
			binary_int.reserve(_BinStr.size());
			transform(begin(_BinStr), end(_BinStr), back_inserter(binary_int), [](char c) { return atoi(&c); });
			int previous_double{ 0 };

			for (const auto i : binary_int)
			{
				previous_double = (previous_double * 2) + i;
			}
			return previous_double;
		}
		int to_integer() const
		{
			return int{ *this };
		}
		operator int() const
		{
			vector<int> binary_int;
			binary_int.reserve(binary_string.size());
			transform(begin(binary_string), end(binary_string), back_inserter(binary_int), [](char c) { return atoi(&c); });
			
			int previous_double{ 0 };

			for (const auto i : binary_int)
			{
				previous_double = (previous_double * 2) + i;
			}
			return previous_double;
		}
		operator size_t() const
		{
			vector<size_t> binary_int;
			binary_int.reserve(binary_string.size());
			transform(begin(binary_string), end(binary_string), back_inserter(binary_int), [](char c) { return atoi(&c); });

			int previous_double{ 0 };

			for (const auto i : binary_int)
			{
				previous_double = (previous_double * 2) + i;
			}
			return previous_double;
		}
		operator string()
		{
			string out;
			auto pace{ std::factors(binary_string.size()).front()};
			// spliting the string into octanes, accumulate them and convert to decimals to do chars
			for (auto it{ begin(binary_string) }; it < end(binary_string); it = next(it, pace))
			{
				string bit;

				copy(it, next(it, pace), back_inserter(bit));

				char put_char = static_cast<char>(to_integer(bit));
				out += put_char;
			}
			return out;
		}
	};

	
}