#pragma once
#include <string>
#include <bitset>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <cassert>
#include "helpers.h"


namespace std
{

	// ASCII numbers that formate a string
	using ascll_string = std::vector<size_t>;

	template<size_t _Size = 8u>
	struct binary
	{
		string _Bin_Str;
		binary(const string& _Msg, bool _Binary_Form = false)
			:
			_Bin_Str{_Binary_Form ? _Msg : to_binary(_Msg) }
		{}
		binary(const size_t _Long)
			:
			_Bin_Str{to_binary(_Long)}
		{}
		binary(const ascll_string& _Codes)
			:
			_Bin_Str{to_binary(std::move(_Codes))}
		{}
	public:
		static string to_binary(const string& _Str)
		{
			string out;
			for (auto it{ std::begin(_Str) }; it != std::end(_Str); ++it)
			{
				auto octane{ std::bitset<_Size / 2>{static_cast<size_t>(*it)}.to_string()};
				//auto test{ std::bitset<_Size>{static_cast<size_t>(*it)}.to_ullong() };
				out += octane;
			}
			return out;
		}
		static string to_binary(const ascll_string& _Codes)
		{
			string decoded{to_string(std::move(_Codes))};
			return to_binary(decoded);
		}
		static string to_binary(size_t _Long)
		{
			string out;
			while (_Long >= 1)
			{
				out += std::to_string(_Long % 2);
				_Long /= 2;
			}

			if (out.size() < _Size)
			{
				auto size_diff{ _Size - out.size() };
				out.reserve(size_diff);
				helpers::do_n{ size_diff, [&] { out.push_back('0'); } };
			}
			string reversed_out;
			move(rbegin(out), rend(out), back_inserter(reversed_out));
			return reversed_out;
		}
	public:
		static string to_string(const string& _Bin)
		{
			auto it_bad{ find_if_not(begin(_Bin), end(_Bin), [](char c)
				{
					return isdigit(c) != 0 && (int)(c - '0') < 2;
				}) };

			assert(it_bad == end(_Bin) && "Binary string can contain only 1s and 0s");
				

			string out;
			for (auto it{ std::begin(_Bin) }; it != std::end(_Bin); it += _Size / 2)
			{
				unsigned char dcd_ch{ static_cast<unsigned char>(std::bitset<_Size>{std::string{it, it + _Size}}.to_ullong()) };
				out += dcd_ch;
			}
			return out;
		}
		static string to_string(const ascll_string& _Codes)
		{
			string out;
			transform(begin(_Codes), end(_Codes), back_inserter(out), [](size_t _Code)
				{
					return static_cast<unsigned char>(_Code);
				});
			return out;
		}
		string to_string() const
		{
			return to_string(_Bin_Str);
		}
	public:
		static size_t to_ullong(const string& _Bin)
		{
			return std::bitset<_Size>{_Bin}.to_ullong();
		}
		ascll_string to_ascll_string() const
		{
			ascll_string out;
			string decoded_str{ to_string(_Bin_Str) };
			transform(begin(decoded_str), end(decoded_str), back_inserter(out), [](char c)
				{
					return static_cast<size_t>(c);
				});
			return out;
		}
		size_t to_ullong() const
		{
			return to_ullong(_Bin_Str);
		}
	};
	
	


	
}