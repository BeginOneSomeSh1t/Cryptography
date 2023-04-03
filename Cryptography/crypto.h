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
#include <numeric>
#include <map>
#include "math.h"
#include "binary.h"


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

	/*tuple<public key, private key, mod, cipher>*/
	using rsa_bundle = std::tuple<size_t, size_t, size_t, size_t>;

	static rsa_bundle rsa_cipher(const std::string& _Msg)
	{
		size_t p{ 89u }, q{ 101u };
		auto n{ p * q };
		auto phi_mod{ std::totient(n) };

		size_t e{ 1323u };

		size_t d{ 0u };

		std::modulus<size_t> mod;

		for (size_t i{ 1u }, m{ 0u }; true; ++i)
		{
			m = mod(i * e, phi_mod);
			if (m == 1)
			{
				d = i;
				break;
			}
		}

		
		//binary representation of a message
		std::binary<32> bin_msg{ _Msg };
		
		/*auto ullong_msg{ bin_msg.to_ullong() };
		
		size_t c{ static_cast<size_t>(std::fmod(std::pow(ullong_msg, e), phi_mod)) };*/
		
		return std::make_tuple(e, d, phi_mod, 3/*c*/);
	}

}








