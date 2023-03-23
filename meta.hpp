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

	template<auto T>
	struct trait_module
	{
		constexpr auto operator()(auto X) const
		{
			// we call our NTTP
			T(X);
			return true;
		}
	};


	template<auto T, auto... trait_modules>
		requires((trait_modules(T), ...))
	struct trait
	{
		constexpr trait() {}

		static constexpr auto value = true;
	};
};