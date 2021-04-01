/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP
#define BOOST_CLBL_TRTS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP

#include <boost/callable_traits/detail/qualifier_flags.hpp>

#define BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(QUAL)              \
template<typename Return, typename... Args>                        \
struct set_function_qualifiers_t <                                 \
    flag_map<int QUAL>::value, false, false, Return, Args...> {    \
    using type = Return(Args...) QUAL;                             \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_function_qualifiers_t <                                 \
    flag_map<int QUAL>::value, true, false, Return, Args...> {     \
    using type = Return(Args...) QUAL                              \
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER;                \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_function_qualifiers_t <                                 \
    flag_map<int QUAL>::value, false, true, Return, Args...> {     \
    using type = Return(Args...) QUAL                              \
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;                        \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_function_qualifiers_t <                                 \
    flag_map<int QUAL>::value, true, true, Return, Args...> {      \
    using type = Return(Args...) QUAL                              \
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER                 \
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;                        \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_varargs_function_qualifiers_t <                         \
    flag_map<int QUAL>::value, false, false, Return, Args...> {    \
    using type = Return(Args..., ...) QUAL;                        \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_varargs_function_qualifiers_t <                         \
    flag_map<int QUAL>::value, true, false, Return, Args...> {     \
    using type = Return(Args..., ...) QUAL                         \
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER;                \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_varargs_function_qualifiers_t <                         \
    flag_map<int QUAL>::value, false, true, Return, Args...> {     \
    using type = Return(Args..., ...) QUAL                         \
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;                        \
};                                                                 \
                                                                   \
template<typename Return, typename... Args>                        \
struct set_varargs_function_qualifiers_t <                         \
    flag_map<int QUAL>::value, true, true, Return, Args...> {      \
    using type = Return(Args..., ...) QUAL                         \
        BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER                 \
        BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER;                        \
}                                                                  \
/**/

namespace boost { namespace callable_traits { namespace detail {

        template<qualifier_flags Applied, bool IsTransactionSafe,
            bool IsNoexcept, typename Return, typename... Args>
        struct set_function_qualifiers_t {
            using type = Return(Args...);
        };

        template<qualifier_flags Applied, bool IsTransactionSafe,
            bool IsNoexcept, typename Return, typename... Args>
        struct set_varargs_function_qualifiers_t {
            using type = Return(Args..., ...);
        };

#ifndef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(volatile);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const volatile);

#ifndef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(&);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(&&);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const &);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const &&);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(volatile &);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(volatile &&);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const volatile &);
        BOOST_CLBL_TRTS_SET_FUNCTION_QUALIFIERS(const volatile &&);

#endif // #ifndef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS
#endif // #ifndef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

        template<qualifier_flags Flags, bool IsTransactionSafe, bool IsNoexcept,
            typename... Ts>
        using set_function_qualifiers =
            typename set_function_qualifiers_t<Flags, IsTransactionSafe, IsNoexcept,
                Ts...>::type;

        template<qualifier_flags Flags, bool IsTransactionSafe, bool IsNoexcept,
            typename... Ts>
        using set_varargs_function_qualifiers =
            typename set_varargs_function_qualifiers_t<Flags, IsTransactionSafe,
                IsNoexcept, Ts...>::type;

}}} // namespace boost::callable_traits::detail

#endif //BOOST_CLBL_TRTS_DETAIL_SET_FUNCTION_QUALIFIERS_HPP

/* set_function_qualifiers.hpp
F0/CkKAOyjzlGZLE+wWkiTOa40tMwP40HQCMwO5Dzl2a/RXdtm3p+I2nNqpqWHdBdaVEfQnl/CSq+ipyzSw9oSgUsRzvmqdkzUI4R+bUlhkQtt77Pow2Orfvc9/ju815FJ6d0NtB8T/1FvrhlsQW6JaKnTGvcsUOYQQtfc+QBzqMSzHiahrCFyQvqwWPhBHf7hAx1jVEWeHLY7XhnzPWyA1Esx6y6UINwSr90qPif+KjsSCW0Uznw4hG6wkRL6Tp/U1PrgfmKkfHfxof6bMmfJGA9Q1rhdl0l63PXP0JOHrYQq5r7oPdJRl1bi39l0goy95r1zsH1VfTjF9tyHwm4/wgeEbk3Z3HAN1G/DU3x0pBkwFx36NUbbMORIwegCFkGaoXJJz3i3dJhs8kr0Y8i0RChOh3QjYqIZm1DCc3Wb9ODswPmaR75YbZhj7RBJsEmS4BX5sUHuj/YxynHI3TGo8+B3W7nSD17Hmt5jTOsdgO2fp436AXtt46zTcg8aOtjyS7mPLeXHvWOf9fGqnqb6ReHHOdK7g10SxBQcUyloF1AqWRtkIrkGjfiA==
*/