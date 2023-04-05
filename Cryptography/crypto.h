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

	/*tuple<cipher text, pub_key, pri_key, mod>*/
	using rsa_bundle = std::tuple<std::vector<int>, size_t, size_t, size_t>;

	static rsa_bundle rsa_cipher(const std::string& _Msg)
	{
		std::distribute_prime_numbers r_primes_dist{ 250u };
		size_t p{ r_primes_dist.random()}, q{ r_primes_dist.random() };

		auto n{ p * q };
		auto fi{ (p - 1) * (q - 1)};
		
		auto e{ 2u };
		while (true)
			if (std::gcd(e, fi) == 1)
				break;
			else
				e++;

		auto d{ 2u };
		while (true)
			if ((d * e) % fi == 1)
				break;
			else
				d++;
		
		auto encrypt{ [&e, &n](auto _Ascll_Num)
			mutable
			{
				auto loc_e{e};
				std::size_t encrypted{1u};
				while (loc_e--)
				{
					encrypted *= _Ascll_Num;
					encrypted %= n;
				}
				return encrypted;
			} };

		std::vector<int> form;
		form.reserve(_Msg.size());
		for (auto& let : _Msg)
			form.push_back(encrypt((int)let));

	
		return std::make_tuple(form, e, d, n);
	}

	static std::string rsa_cipher(const rsa_bundle& _Bundle)
	{
		auto [form, e, d, n] {_Bundle};

		auto decrypt{ [d = d, n = n](auto _Encrypted)
			{
				auto loc_d{d};
				std::size_t decrypted{1u};
				while (loc_d--)
				{
					decrypted *= _Encrypted;
					decrypted %= n;
				}
				return decrypted;
			} };

		std::string out;
		for (auto& num : form)
			out += decrypt(num);

		return out;
	}

}








