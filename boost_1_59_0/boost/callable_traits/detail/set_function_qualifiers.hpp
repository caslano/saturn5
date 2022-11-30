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
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
*/