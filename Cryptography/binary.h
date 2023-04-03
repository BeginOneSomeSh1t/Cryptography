#pragma once
#include <string>
#include <bitset>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <stdexcept>


namespace std
{

	
	class binary_exception : exception
	{
	private:
		string _Err_Msg;
	public:
		binary_exception(const string& _Msg)
			:
			_Err_Msg{_Msg}
		{}
		const char* what() const override
		{
			return _Err_Msg.c_str();
		}
	};
	

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
			_Mask.reserve(str.size() * (_Size <= 16) ? _Size / 2 : _Size / 8);
			// convert char by char string to binary_container
			for (unsigned char c : str)
			{
				char_in_del = static_cast<size_t>(c);
				auto char_bytes{ to_binary(char_in_del, (_Size <= 16) ? _Size / 2 : _Size / 8) };
				_Mask.insert(end(_Mask), make_move_iterator(begin(char_bytes)), make_move_iterator(end(char_bytes)));
			}
		}
		explicit binary(size_t _Del)
			:
			_Mask{to_binary(_Del, _Size)}
		{}
		/*Converts a decimal unsigned number to a binary container*/
		static binary_container to_binary(std::size_t _Del, std::size_t _Bin_Size = 8u)
		{
 			binary_container temp;
			for(size_t i{0u}; _Del >= 1 && i < _Bin_Size; ++i, _Del /= 2)
				temp.push_back(static_cast<bool>(_Del % 2));
			
			if (_Del != 0)
				throw binary_exception("Not enoght size for adding content");

			if (temp.size() < _Bin_Size)
			{
				auto size_dif{ _Bin_Size - temp.size() };
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
			case _Converter_Type::_String: return string{ to_string(_Mask, (_Size <= 16) ?  _Size / 2 : _Size / 8) };
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
				auto ullong{ to_ullong(binary_container{it, it + _Bin_Size}) };
				unsigned char ch{ static_cast<unsigned char>(ullong) };
				out += ch;
			}
			return out;
		}

	};
	
	


	
}