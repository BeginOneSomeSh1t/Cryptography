#pragma once


namespace helpers
{
	struct do_n
	{
		template<typename _Func, typename..._Ts>
		do_n(size_t _Times, _Func _Lambd, _Ts&&..._Args)
		{
			for (size_t i{ 0u }; i < _Times; ++i)
				_Lambd(std::forward<_Ts>(_Args)...);
		}
	};
}