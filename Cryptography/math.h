#pragma once
#include <vector>
#include <random>
#include <iterator>
#include <cassert>
#include <map>
#include <numeric>
#include <cmath>

namespace std
{
	template<typename _Ty>
	using min_max = tuple<_Ty, _Ty>;
	/*Returns a tuple with min and max elements*/
	template<typename _Ty>
	min_max<_Ty> get_minmax_element(_Ty _First, _Ty _Last) noexcept
	{
		if (_First > _Last)
			return { _Last, _First };
		else if (_First < _Last)
			return { _First, _Last };
		else
			return { (_Ty)0, (_Ty)0 };
	}

	/*Allows to compare two values with the passed error tolerance*/
	template<typename _Ty>
	static bool nearly_equal(_Ty _A, _Ty _B, double _Err) noexcept
	{
		if (_A == _B)
			return true;
		else
			if (auto [min, max] {get_minmax_element<_Ty>(_A, _B)}; (max - min) <= _Err)
				return true;
			else
				return false;

	}
	/*Pows the argument in 2*/
	template<typename _Ty>
	_Ty pow(_Ty _Init) noexcept
	{
		return _Init * _Init;
	}

	using primes = std::vector<size_t>;

	/*Find all primes up to given limit by using Sieve of Eratosthenes*/
	static primes generate_prime_numbers(std::size_t _Count) noexcept
	{
		assert(_Count > 1 && "Count must be bigger than 1");

		std::map<size_t, bool> bool_map;
		// initially all elements in the map set to true
		for (size_t i{ 2u }; i <= _Count; ++i)
			bool_map[i] = true;

		for (size_t i{ 2u }; i <= std::sqrt(_Count); ++i)
			if (bool_map[i])
				for (size_t j = std::pow(i), k{ 1u }; j <= _Count; ++k)
				{
					bool_map[j] = false;
					j = std::pow(i) + (k * i);
				}

		primes results;

		for (auto [num, isPrime] : bool_map)
			if (isPrime)
				results.push_back(num);

		return results;
	}

	using prime_range = std::pair<size_t, size_t>;
	/*Generate and distribute prime numbers.*/
	class distribute_prime_numbers
	{
	public:
		/*Generates primes from the passed count.*/
		explicit distribute_prime_numbers(size_t _Count)
			:
			p{ generate_prime_numbers(_Count) },
			pr{ 0u, p.size() - 1 }
		{}
		/*Generates primes from the passed count and sets the minimum limit for index distribution*/
		explicit distribute_prime_numbers(size_t _First, size_t _Count)
			:
			p{ generate_prime_numbers(_Count) },
			pr{ _First, p.size() - 1 }
		{}
		/*Returns random prime number from generated primes*/
		size_t random() const
		{
			random_device r;
			uniform_int_distribution<size_t> index_dist{ pr.first, pr.second };
			auto rand_indx{ index_dist(r) };
			return p.at(rand_indx);
		}
	public:
		primes p;
		prime_range pr;
	};

	template<typename _Ty>
	static auto totient(_Ty n)
	{
		unsigned int result{ 1 };
		for (int i{ 2 }; i < n; ++i)
			if (gcd(i, n) == 1)
				result++;
		return result;
	}

	template<typename _Ty>
	static auto factors(_Ty _Init)
	{
		std::vector<_Ty> output;
		auto z{ 2 };

		while (z * z <= _Init)
			if (_Init % z == 0)
			{
				output.push_back(z);
				_Init /= z;
			}
			else
				z++;

		return output;
	}

	template<typename _Ty>
	tuple<int, int, int> egcd(_Ty _Mx, _Ty _Nx)
	{
		if (_Mx == 0) {
			return make_tuple(_Nx, 0, 1);
		}

		int gcd, x, y;

		// unpack tuple returned by function into variables
		tie(gcd, x, y) = egcd(_Nx % _Mx, _Mx);

		return make_tuple(gcd, (y - (_Nx / _Mx) * x), x);
	}

	template<typename _Ty>
	static auto positive(_Ty _Mx, _Ty _Nx)
	{
		if (_Mx >= 0 && _Nx < 0)
			return _Mx;
		else if (_Mx >= 0 && _Nx >= 0)
			return _Mx;
		else if (_Mx < 0 && _Nx < 0)
			return 0;
		else
			return _Nx;
	}
}