#include <algorithm>    // std::copy_n
#include <array>        // std::array
#include <cstddef>      // std::size_t
#include <string_view>  // std::string_view
#include <utility>      // std::index_sequence

template <auto i>
struct fixed_string {
    constexpr fixed_string(const char(&arr)[i + 1]) {
        std::copy_n(arr, i + 1, data);
    }

    template<typename T, auto Size>
    constexpr fixed_string(std::array<T, Size> arr)
    {
        std::copy_n(arr.data(), i + 1, data);
    }

    constexpr auto size() const { return i; }

    template <auto I>
    constexpr auto nth_element() const {
        return data[I];
    }

    auto operator<=>(const fixed_string&) const = default;

    char data[i + 1] = {};
};

template <auto i>
fixed_string(const char(&arr)[i])->fixed_string<i - 1>;

template <char c, std::size_t>
constexpr auto function_return() {
    return c;
}

template <bool condition, auto value, char return_>
struct if_is {
    constexpr if_is() {}

    constexpr auto operator()() const noexcept {
        if constexpr (condition) {
            return value;
        }
        else {
            return return_;
        }
    }
};

template <typename T, std::size_t I>
constexpr auto array_to_fixed_string(std::array<T, I> arr) {
    return fixed_string<I>{arr.data()};
}

template <fixed_string str, char c, int index>
constexpr auto find_index_arr() {
    if constexpr (str.template nth_element<index>() == c) {
        return index;
    }
    else {
        if constexpr (str.size() <= index) {
            return -1;
        }
        else {
            return find_index_arr<str, c, index + 1>();
        }
    }
}

template <fixed_string str, char c>
constexpr auto find_index_arr() {
    if constexpr (str.template nth_element<0>() == c) {
        return 0;
    }
    else {
        return find_index_arr<str, c, 1>();
    }
}

template <fixed_string str>
struct string_parse {
    template <auto A, auto B>
    constexpr auto substr() const noexcept {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return std::array{ (str.template nth_element<A + indexes>())...,
                              '\0' };
        }(std::make_index_sequence<B - A>{});
    }

    template <std::size_t... indexes>
    constexpr auto take() const noexcept {
        return std::array{ (str.template nth_element<indexes>)..., '\0' };
    }

    template <char c>
    constexpr auto consume_until() const noexcept {
        constexpr int index = find_index_arr<str, c>();
        return substr<0, index>();
    }

    template <char c>
    constexpr auto find() const noexcept {
        return find_index_arr<str, c>();
    }

    // make this private
    template <auto Char, auto Index>
    constexpr auto function_return_index() const noexcept {
        return Char;
    }

    template <char c, auto lamda>
    constexpr auto if_string_has() const noexcept {
        if constexpr (find<c>() != -1) {
            return change_with<lamda>();
        }
    }

    template <char c>
    constexpr auto blur_with() const noexcept {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return std::array{ (function_return_index<c, indexes>())..., '\0' };
        }(std::make_index_sequence<str.size()>{});
    }

    template <auto lambda>
    constexpr auto change_with() const noexcept {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return std::array{ (lambda(str.template nth_element<indexes>()))...,
                              '\0' };
        }(std::make_index_sequence<str.size()>{});
    }

    template <auto lambda>
    constexpr auto occurences() const noexcept {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return (lambda.template
                operator() < str.template nth_element<indexes>() > () +
                ...);
        }(std::make_index_sequence<str.size()>{});
    }

    template <auto blur, auto other, auto until, auto index>
    constexpr auto when_less_than_idx() const noexcept {
        if constexpr (index < until) {
            return blur;
        }
        else {
            return other;
        }
    }

    template <char c, int X>
    constexpr auto blur_until() const noexcept {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return std::array{
                (when_less_than_idx<c, str.data[indexes], X, indexes>())... };
        }(std::make_index_sequence<str.size()>{});
    }

    template <auto lambda>
    constexpr auto remove_if() const noexcept {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return std::array{
                if_is<!lambda(str.template nth_element<indexes>()),
                      str.template nth_element<indexes>(), ' '>{}()...,
                '\0' };
        }(std::make_index_sequence<str.size()>{});
    }

    template <auto lambda, char c>
    constexpr auto replace_with_if() const noexcept {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return std::array{
                if_is<!lambda(str.template nth_element<indexes>()),
                      str.template nth_element<indexes>(), c>{}()...,
                '\0' };
        }(std::make_index_sequence<str.size()>{});
    }

    template <auto character>
    constexpr auto character_occurences() const noexcept {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return ((str.data[indexes] == character) + ...);
        }(std::make_index_sequence<str.size()>{});
    }

    template <auto character, auto from>
    constexpr auto character_occurences_from() const noexcept {
        return[&]<std::size_t... indexes>(std::index_sequence<indexes...>) {
            return ((str.data[indexes + from] == character) + ...);
        }(std::make_index_sequence<str.size() - from>{});
    }

    template <auto from, auto character>
    constexpr auto from_up_to() const noexcept {
        constexpr auto index = find<character>();
        return substr<from, index>();
    }

    template <auto from>
    constexpr auto from_to_end() const noexcept {
        constexpr auto index = find<from>();
        return substr<index, size()>();
    }

    constexpr auto data() const noexcept { return str.data; }
    constexpr auto string_view() const noexcept {
        return std::string_view{ str.data };
    }
    constexpr auto string() const noexcept { return str; }
    constexpr auto number_of_characters() const noexcept { return str.size(); }
    constexpr auto size() const noexcept { return str.size(); }
};

// --------------------------- Above are all in mlib library
// -----------------------------------------------------

// string_parsing like things, at compile time

// "integer" -> fixed_string
// "integer"
// type_pack<int, bool, float, char>

template<fixed_string s>
struct string_to_type;

template<typename T>
struct type_wrapper
{
};

template<typename T>
static constexpr auto t = type_wrapper<T>{};

template<>
struct string_to_type<"integer">
{
    static constexpr auto type = t<int>;
};

template<>
struct string_to_type<"boolean">
{
    static constexpr auto type = t<bool>;
};

template<>
struct string_to_type<"floating">
{
    static constexpr auto type = t<float>;
};

template<>
struct string_to_type<"character">
{
    static constexpr auto type = t<char>;
};

template<auto... Ts>
struct type_pack;

template <fixed_string s>
constexpr auto parse_type_sequence() {
    constexpr string_parse<s> string_parser{};
    // constexpr auto index_of_first_paren = 0;
    // constexpr auto index_of_last_paren = s.size() - 1;
    // constexpr /*std::array*/ auto x =
    //     string_parser.template substr<index_of_first_paren + 1,
    //                                   index_of_last_paren - 1>();

    //constexpr fixed_string<index_of_last_paren -1 - index_of_first_paren + 1> string_types = fixed_string{x};

    // constexpr auto first_index = string_parser.template find<','>();
    // constexpr auto array = string_parser.template from_up_to<0, ','>();

    return type_pack < string_to_type<s>{}.type > {};

}

template <auto... Ts>
struct type_pack
{
    constexpr auto operator==(type_pack<Ts...> t) { return true; }
    template<auto... Xs> constexpr auto operator==(type_pack<Xs...> t) { return false; }
};

/*
int main()
{
    constexpr auto types = parse_type_sequence<"integer">();
    static_assert(types == type_pack<t<int>>{});
}
*/
