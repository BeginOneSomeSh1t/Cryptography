#pragma once
#include <string>
#include <bitset>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>


namespace std
{

	using binary_container = std::vector<bool>;

	template<size_t _Size>
	struct binary
	{
		enum _Converter_Type
		{
			_String,
			_Binary,
			_Ullong,
		};
		binary_container _Mask;
		explicit binary(const string& str)
		{
			size_t char_in_del{ 0u };
			// reserve place in mask
			_Mask.reserve(str.size() * _Size);
			// convert char by char string to binary_container
			for (char c : str)
			{
				char_in_del = static_cast<size_t>(c);
				auto char_bytes{ to_binary(char_in_del) };
				_Mask.insert(end(_Mask), make_move_iterator(begin(char_bytes)), make_move_iterator(end(char_bytes)));
			}
		}
		explicit binary(size_t _Del)
			:
			_Mask{to_binary(_Del)}
		{}
		/*Converts a decimal unsigned number to a binary container*/
		static binary_container to_binary(std::size_t _Del)
		{
 			binary_container temp;
			while(_Del >= 1)
			{
				temp.push_back(static_cast<bool>(_Del % 2));
				_Del /= 2;
			}
			if (temp.size() < _Size)
			{
				auto size_dif{ _Size - temp.size() };
				temp.reserve(size_dif);
				for (size_t i{ 0u }; i < size_dif; ++i)
					// push back 0
					temp.push_back(false);
				
			}
			binary_container output;
			output.reserve(temp.size());
			copy(rbegin(temp), rend(temp), back_inserter(output));
			return output;
		}
		/*Converts binary container to a decimal unsigned number*/
		static size_t to_ullong(const binary_container& _Bin)
		{
			size_t out{ 0u };
			for (auto b : _Bin)
			{
				out = (out * 2u) + static_cast<size_t>(b);
			}
			return out;
		}
		size_t to_ullong() const
		{
			return size_t{ to_ullong(_Mask) };
		}
		/*Convert binary container do a string of 1s and 0s*/
		static string to_string(const binary_container& _Bin)
		{
			string out;
			transform(begin(_Bin), end(_Bin), back_inserter(out), [](auto b) {return *std::to_string(static_cast<size_t>(b)).c_str(); });
			return out;
		}
		/*Convert this object's mask to a string of binary container*/
		string to_string(_Converter_Type _Ty = _Binary) const
		{
			switch (_Ty)
			{
			case _Converter_Type::_Binary: return string{ to_string(_Mask) };
										 break;
			case _Converter_Type::_String: return string{to_string(_Mask, _Size)};
										 break;
			case _Converter_Type::_Ullong: return string{std::to_string(to_ullong(_Mask))};
			default:
				break;
			}
		}
		static string to_string(const binary_container& _Bin, size_t _Bin_Size)
		{
			string out;
			for (auto it{ begin(_Bin) }; it != end(_Bin); it += _Bin_Size)
			{
				auto ch{ static_cast<char>(to_ullong(binary_container{it, it + _Bin_Size})) };
				out += ch;
			}
			return out;
		}

	};
	
	


	
}