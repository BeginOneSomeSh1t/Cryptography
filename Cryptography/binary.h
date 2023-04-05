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
	/*This class decomposes an incmoing string or unsigned long long number into bytes and store it in _Bin_Str.
	Size template parameter means a size of every byte*/
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
	public:
		/*Converts a string to a binary string character by character*/
		static string to_binary(const string& _Str)
		{
			string out;
			for (auto it{ std::begin(_Str) }; it != std::end(_Str); ++it)
			{

				auto octane{ std::bitset<_Size>{static_cast<unsigned __int64>(*it)}.to_string()};
				out += octane;
			}
			return out;
		}
		/*Converts a ascll string to a binyary string*/
		/*Converts a decimal number to a binary string*/
		static string to_binary(size_t _Long)
		{
			string out;
			while (_Long >= 1)
			{
				out += std::to_string(_Long % 2);
				_Long /= 2;
			}
			string reversed_out;
			move(rbegin(out), rend(out), back_inserter(reversed_out));
			return reversed_out;
		}
	public:
		/*Converts a binary string to a string*/
		static string to_string(const string& _Bin)
		{
			assert(is_binary(_Bin) && "Binary string can contain only 1s and 0s");

			string out;
			for (auto it{ std::begin(_Bin) }; it != std::end(_Bin); it += _Size)
			{
				unsigned char dcd_ch{ static_cast<unsigned char>(std::bitset<_Size>{std::string{it, it + _Size}}.to_ullong()) };
				out += dcd_ch;
			}
			return out;
		}
		string to_string() const
		{
			return to_string(_Bin_Str);
		}
	public:
		/*Converts a binary string to unsigned long long*/
		static size_t to_ullong(const string& _Bin)
		{
			assert(is_binary() && "Binary string can contain only 1s and 0s");
			size_t out{ 0u };
			helpers::do_n{ _Bin.size(), [&](auto i)
				{
					out = (out * 2) + static_cast<size_t>(_Bin[i]) - '0';
				} };
			return out;
		}
		size_t to_ullong() const
		{
			return to_ullong(_Bin_Str);
		}
	public:
		/*Checks validaton of a binary string*/
		static bool is_binary(const string& _Bin)
		{
			auto it_bad{ find_if_not(begin(_Bin), end(_Bin), [](char c)
				{
					return isdigit(c) != 0 && (int)(c - '0') < 2;
				}) };
			return it_bad == end(_Bin);
		}
	};
}