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

	/*tuple<public key, private key, mod,  encrypted message>*/
	using rsa_bundle = std::tuple<size_t, size_t, size_t, std::string>;

	static rsa_bundle rsa_cipher(const std::string& _Msg)
	{
		std::random_device r;
		std::uniform_int_distribution<size_t> size_dist{10u, 1000u};
		std::distribute_prime_numbers prime_dist{ size_dist(r) };

		// two random primes
		auto p{ prime_dist.random() }, q{ prime_dist.random() };
		// totiend dist
		auto n{ p * q };

		auto prime{ std::totient(n) };
		// gather factors to make sure we're not repeat them
		auto prime_factors{ std::factors(prime) };

		// distribute other factors that would not include the factor of prime
		std::distribute_prime_numbers distinct_prime_dist{ prime_factors.back(), 100u };
		
		std::vector<size_t> e_factors;
		// define random amount of factors
		std::uniform_int_distribution<int> fac_amount_dist{ 2, 10 };
		auto fac_amount{ fac_amount_dist(r) };
		// populate the vector of factors
		e_factors.reserve(fac_amount);
		for (int i{ 0 }; i < fac_amount; ++i)
			e_factors.push_back(distinct_prime_dist.random());

		std::uniform_int_distribution<int> pows_dist{ 2, 8 };
		// public key
		std::uniform_int_distribution<size_t> fac_times_dist{ 2, e_factors.size() - 1};
 		size_t factorized_decimal{ 1 };
		auto fact_times{ fac_times_dist(r) };
		for (std::size_t i{0u}; i < fact_times; ++i)
			factorized_decimal += std::pow(e_factors[i], pows_dist(r));
		
		std::uniform_int_distribution<int> integer_for_prime_dist{ 20, 100 };
		std::distribute_prime_numbers egcd_primes{ static_cast<size_t>(integer_for_prime_dist(r))};
		auto [gcd, x, y] {std::egcd(egcd_primes.random(), egcd_primes.random())};

		// private key
		auto d{ std::positive(x, y) };

		std::binary<32> bin_msg{ _Msg };
		// decimal message
		auto del_msg{ bin_msg.to_ullong()};

		auto c{ static_cast<size_t>(std::fmod(std::pow(del_msg, d), n))};
		
		std::binary<32> output{ c };
		std::string encrypted_msg( output.to_string(decltype(output)::_String) );

		return std::make_tuple(factorized_decimal, d, n, encrypted_msg);

	}

}








