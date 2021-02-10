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
pBbLXMm00vn3vXqt3j4dn5xOBi9Z/Zsyd+qZywopUo5HIbSdI4KgjSiUviJBFg8kPTFao2BBEFoa47Nx3KtxNmGR1wKGMyHhCJVLGl2+iadnF6f9kwkFNdZnC8SVIslq9LAVkXIMlZqVzg0f5RxYsWDAa9h3eTGERXiPz6enF/3p+Xg0IV0uUFI+Y2ohbeBvTXUPJ5zgPH0qrWNNQCexEusunTtQy3lDN46y55zIme9PLmO2mzzYEji4CUQCDzxHUSE5/LFr1JlOc7gO/3itdtmDBjDvjpfs3hU51AeKs5abm2InbAuQ7FqCUmBbXdozGVQ7w2ChqKpKAzXnSKfUrkLpeQCya+vkogbgNrESfMZUJvVarW+VTvIylXRsXapMN3vZWKrs213kXhAaApZBsxb5fMGSuXRJhmjPQ0eSOUf2bDp9O4n8ipahFtliQdPhBIWTfJbwd4XCCE4DLTfJZ6RBYAcBRDyR8vZ4KfVkMqTD7mH3OqLRZMKdNOlwEYk0Jd4LTidICOPab1pw8NtUzpWW3sQ9bmfoZlAg8sxY1/vn61d77EOTXFUa2B+wmzmDJKONAhadvQHZ5Py//+NhMrNCE9TrQNFAfdaMxNc1x6RbyjrdtGtik++Hh8+//1erZZ1wKqmpEnsfY+fp
*/