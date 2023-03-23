#include<tuple>
#include<cstddef>
#include<utility>
#include<iostream>

template<auto lambda, typename... Ts>
constexpr auto for_each(std::tuple<Ts...> tup)
{
	[&] <std::size_t... indexes>(std::index_sequence<indexes...>)
	{
		(lambda(std::get<indexes>(tup)), ...);
	}(std::make_index_sequence<sizeof...(Ts)>{});
}

int main()
{
	std::tuple t{ 'c', true, 4, 'b', false, 56 };
	for_each < [](auto x) {std::cout << x << ", "; } > (t);
}


