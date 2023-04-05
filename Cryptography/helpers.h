#pragma once
#include <vector>
#include <string>

namespace helpers
{
	/*Calls a passed lambda object n times with passing an index*/
	struct do_n
	{
		size_t i;
		template<typename _Func>
		do_n(size_t _Times, _Func _Lambd)
			:
			i{0u}
		{
			for (; i < _Times; ++i)
				_Lambd(i);
		}
	};
}