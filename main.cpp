// This is a project for testing things.

#include"meta.hpp"
#include<windows.graphics.h>

int main()
{
	meta::invoke_wrapper < []() constexpr {return []() constexpr {return 56; }; } > x{};
	static_assert(x.invoke().final_invoke() == 56);
}