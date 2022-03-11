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