#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <tuple>
#include <random>
#include <cassert>
#include <map>

namespace std
{
	template<typename _Ty>
	using min_max = tuple<_Ty, _Ty>;

	template<typename _Ty>
	min_max<_Ty> get_minmax_element(_Ty _First, _Ty _Last)
	{
		if (_First > _Last)
			return { _Last, _First };
		else if (_First < _Last)
			return { _First, _Last };
		else if (_First == _Last)
			return { (_Ty)0, (_Ty)0 };
	}


	template<typename _Ty>
	static bool nearly_equal(_Ty _A, _Ty _B, double _Err)
	{
		if (_A == _B)
			return true;
		else
			if (auto [min, max] {get_minmax_element<_Ty>(_A, _B)}; (max - min) <= _Err)
				return true;
			else
				return false;
		
	}

	template<typename _Ty>
	_Ty pow(_Ty _Init)
	{
		return _Init * _Init;
	}
	
	/*Find all primes up to given limit by using Sieve of Eratosthenes*/
	static std::vector<std::size_t> generate_prime_numbers(std::size_t _Count)
	{
		assert(_Count > 1 && "Count must be bigger than 1");

		// lost of consecutive_nums 2,3,4...n
		std::vector<std::size_t> consecutive_nums;

		consecutive_nums.reserve(_Count);

		// populate the vec
		for (size_t i{ 2u }; i <= _Count; ++i)
			consecutive_nums.push_back(i);

		std::map<size_t, bool> bool_map;
		// initially all elements in the map set to true
		for (auto it{ std::begin(consecutive_nums) }; it != std::end(consecutive_nums); ++it)
			bool_map[*it] = true;



		for (size_t i{ 2u }; i <= std::sqrt(_Count); ++i)
			if (bool_map[i])
				for (size_t j = std::pow(i), k{ 1u }; j <= _Count; ++k)
				{
					bool_map[j] = false;
					j = std::pow(i) + (k * i);
				}

		std::vector<std::size_t> results;

		for (auto [num, isPrime] : bool_map)
			if (isPrime)
				results.push_back(num);

		return results;
	}



}


namespace crypto
{

	// crypto algortihms
	/*Ciphers a plain text and returns a decrypted message. It is up to user to remember the shift*/
	static std::string caesar_cipher(const std::string& _Msg, unsigned _Shift, bool _Encrypt = true)
	{
		std::string out_msg;

		std::transform(std::begin(_Msg), std::end(_Msg), std::back_inserter(out_msg), [=](char c)
			{
				return (_Encrypt) ? (char)(c + _Shift) : (char)(c - _Shift);
			});
	
		return out_msg;
	}
	/*Diffie-Hellman cipher ciphers two numbers with the random modulo and base*/
	template<typename _Ty>
	static _Ty diffie_hellman_cipher(std::vector<_Ty> secrts_vec)
	{
		assert(secrts_vec.size()<= 2u && "Algorithm can't compute more than two secrets");
		std::random_device r;
		std::uniform_int_distribution<unsigned int> dist_p{ 1 };
		std::uniform_int_distribution<std::size_t> dist_g{ 1, 10 };
		//distribute p and g
		auto p{ dist_p(r) };
		auto g{ dist_g(r) };

		std::vector<_Ty> comptd_secrts;
		comptd_secrts.reserve(secrts_vec.size());
		
		for (auto it{ std::begin(secrts_vec) }; it != std::end(secrts_vec); ++it)
			comptd_secrts.push_back(std::fmod(std::pow(g, *it), p));
	
		
		auto revit_begin{ std::rbegin(comptd_secrts) };
		const auto revit_end{ std::rend(comptd_secrts) };
		// to collate with every new result
		_Ty prev_res;
		
		auto it_scrts{ std::begin(secrts_vec) };

		for (auto it{revit_begin}; it != revit_end; ++it, ++it_scrts)
		{
			const _Ty result{ static_cast<const _Ty>(std::fmod(std::pow(*it, *it_scrts), p))};
			// skip the collation in the beginning
			if (it == revit_begin)
				prev_res = result;
			else if (std::nearly_equal(result, prev_res, 0.05))
				prev_res = result;
			else // if there's no match, there's an error
				return 0u;
		}
		// to this moment prev_res should be match to one of the results
		return prev_res;
	}
	/*Diffie-Hellman cipher ciphers two numbers with the pointed modula and base*/
	template<typename _Ty>
	static _Ty diffie_hellman_cipher(std::vector<_Ty> secrts_vec, std::size_t _P, std::size_t _G)
	{
		assert(secrts_vec.size()<= 2u && "Algorithm can't compute more than two secrets");
		//distribute p and g
		auto p{ _P };
		auto g{ _G };

		std::vector<_Ty> comptd_secrts;
		comptd_secrts.reserve(secrts_vec.size());

		for (auto it{ std::begin(secrts_vec) }; it != std::end(secrts_vec); ++it)
			comptd_secrts.push_back(std::fmod(std::pow(g, *it), p));


		auto revit_begin{ std::rbegin(comptd_secrts) };
		const auto revit_end{ std::rend(comptd_secrts) };
		// to collate with every new result
		_Ty prev_res;

		auto it_scrts{ std::begin(secrts_vec) };

		for (auto it{ revit_begin }; it != revit_end; ++it, ++it_scrts)
		{
			const _Ty result{ static_cast<const _Ty>(std::fmod(std::pow(*it, *it_scrts), p)) };
			// skip the collation in the beginning
			if (it == revit_begin)
				prev_res = result;
			else if (std::nearly_equal(result, prev_res, 0.01))
				prev_res = result;
			else if (std::nearly_equal(result, prev_res, 0.05))
				prev_res = result;
			else if (std::nearly_equal(result, prev_res, 0.10))
				prev_res = result;
			else // if there's no match, there's an error
				return 0u;
		}
		// to this moment prev_res should be match to one of the results
		return prev_res;
	}
	/*Diffie-Hellman cipher ciphers two numbers with the pointed modula and base including ErrorTolerance in the
	comparison of numbers*/
	template<typename _Ty>
	static _Ty diffie_hellman_cipher(std::vector<_Ty> secrts_vec, std::size_t _P, std::size_t _G, double _ErrTolerance)
	{
		assert(secrts_vec.size()<= 2u && "Algorithm can't compute more than two secrets");
		//distribute p and g
		auto p{ _P };
		auto g{ _G };

		std::vector<_Ty> comptd_secrts;
		comptd_secrts.reserve(secrts_vec.size());

		for (auto it{ std::begin(secrts_vec) }; it != std::end(secrts_vec); ++it)
			comptd_secrts.push_back(std::fmod(std::pow(g, *it), p));


		auto revit_begin{ std::rbegin(comptd_secrts) };
		const auto revit_end{ std::rend(comptd_secrts) };
		// to collate with every new result
		_Ty prev_res;

		auto it_scrts{ std::begin(secrts_vec) };

		for (auto it{ revit_begin }; it != revit_end; ++it, ++it_scrts)
		{
			const _Ty result{ static_cast<const _Ty>(std::fmod(std::pow(*it, *it_scrts), p)) };
			// skip the collation in the beginning
			if (it == revit_begin)
				prev_res = result;
			else if (std::nearly_equal(result, prev_res, _ErrTolerance))
				prev_res = result;
			else // if there's no match, there's an error
				return 0u;
		}
		// to this moment prev_res should be match to one of the results
		return prev_res;
	}
	/*Diffie-Hellman cipher ciphers two numbers with the random modulo and base including ErrorTolerance in the
	comparison of numbers*/
	template<typename _Ty>
	static _Ty diffie_hellman_cipher(std::vector<_Ty> secrts_vec, double _ErrTolerance)
	{
		assert(secrts_vec.size() <= 2u && "Algorithm can't compute more than two secrets");
		std::random_device r;
		std::uniform_int_distribution<unsigned int> dist_p{ 1 };
		std::uniform_int_distribution<std::size_t> dist_g{ 1, 10 };
		//distribute p and g
		auto p{ dist_p(r) };
		auto g{ dist_g(r) };

		std::vector<_Ty> comptd_secrts;
		comptd_secrts.reserve(secrts_vec.size());

		for (auto it{ std::begin(secrts_vec) }; it != std::end(secrts_vec); ++it)
			comptd_secrts.push_back(std::fmod(std::pow(g, *it), p));


		auto revit_begin{ std::rbegin(comptd_secrts) };
		const auto revit_end{ std::rend(comptd_secrts) };
		// to collate with every new result
		_Ty prev_res;

		auto it_scrts{ std::begin(secrts_vec) };

		for (auto it{ revit_begin }; it != revit_end; ++it, ++it_scrts)
		{
			const _Ty result{ static_cast<const _Ty>(std::fmod(std::pow(*it, *it_scrts), p)) };
			// skip the collation in the beginning
			if (it == revit_begin)
				prev_res = result;
			else if (std::nearly_equal(result, prev_res, _ErrTolerance))
				prev_res = result;
			else // if there's no match, there's an error
				return 0u;
		}
		// to this moment prev_res should be match to one of the results
		return prev_res;
	}

}








