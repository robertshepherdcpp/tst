#pragma once

namespace meta
{
	template<auto x, auto... args>
	struct invoke_wrapper
	{
		constexpr auto invoke()
		{
			return invoke_wrapper<x(args...)>{};
		}

	    constexpr auto final_invoke()
		{
			return x(args...);
		}
	};

	template<auto x>
	struct invoke_wrapper<x>
	{
		constexpr auto invoke()
		{
			return invoke_wrapper<x()>{};
		}

		constexpr auto final_invoke()
		{
			return x();
		}
	};

	// -----------------------------------------------------------------------------------------------------------------


};