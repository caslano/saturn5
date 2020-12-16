//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_TYPE_TRAITS_HPP
#define BOOST_BEAST_DETAIL_TYPE_TRAITS_HPP

#include <boost/type_traits/make_void.hpp>
#include <type_traits>
#include <new>

namespace boost {
namespace beast {
namespace detail {

template<class U>
std::size_t constexpr
max_sizeof()
{
    return sizeof(U);
}

template<class U0, class U1, class... Us>
std::size_t constexpr
max_sizeof()
{
    return
        max_sizeof<U0>() > max_sizeof<U1, Us...>() ?
        max_sizeof<U0>() : max_sizeof<U1, Us...>();
}

template<class U>
std::size_t constexpr
max_alignof()
{
    return alignof(U);
}

template<class U0, class U1, class... Us>
std::size_t constexpr
max_alignof()
{
    return
        max_alignof<U0>() > max_alignof<U1, Us...>() ?
        max_alignof<U0>() : max_alignof<U1, Us...>();
}

// (since C++17)
template<class... Ts>
using make_void = boost::make_void<Ts...>;
template<class... Ts>
using void_t = boost::void_t<Ts...>;

// (since C++11) missing from g++4.8
template<std::size_t Len, class... Ts>
struct aligned_union
{
    static
    std::size_t constexpr alignment_value =
        max_alignof<Ts...>();

    using type = typename std::aligned_storage<
        (Len > max_sizeof<Ts...>()) ? Len : (max_sizeof<Ts...>()),
            alignment_value>::type;
};

template<std::size_t Len, class... Ts>
using aligned_union_t =
    typename aligned_union<Len, Ts...>::type;

//------------------------------------------------------------------------------

// for span
template<class T, class E, class = void>
struct is_contiguous_container: std::false_type {};

template<class T, class E>
struct is_contiguous_container<T, E, void_t<
    decltype(
        std::declval<std::size_t&>() = std::declval<T const&>().size(),
        std::declval<E*&>() = std::declval<T&>().data()),
    typename std::enable_if<
        std::is_same<
            typename std::remove_cv<E>::type,
            typename std::remove_cv<
                typename std::remove_pointer<
                    decltype(std::declval<T&>().data())
                >::type
            >::type
        >::value
    >::type>>: std::true_type
{};

template <class T, class U>
T launder_cast(U* u)
{
#if defined(__cpp_lib_launder) && __cpp_lib_launder >= 201606
    return std::launder(reinterpret_cast<T>(u));
#elif defined(BOOST_GCC) && BOOST_GCC_VERSION > 80000
    return __builtin_launder(reinterpret_cast<T>(u));
#else
    return reinterpret_cast<T>(u);
#endif
}

} // detail
} // beast
} // boost

#endif

/* type_traits.hpp
kN+71/M/8ZKXvPTfSw1n/zfN/6H7/89INNT+Sk19ai9ylYpRk7rRZns6In1KZiaqqt0j1bYPI30LLkLnXYmmDjXN0bfSntrtDlD6VNjzrxGaw2Fz5R5IUl4Qnm98q9Ohss3RRgztYDdKeUj4dN8qn/8YLNebcAxRCHsZ09xsEmrfrOuF9tDw5cZc6lcD/R9lxFG3N/kxsVWHfYj/PzMynPYKZQO+QuhGhL9hjJa+xqi+hqp9efaXcXVWNgOf1WZAnfC5QjM+fJ0vwqKXZV/Un2a46WWpg14q7UaFF/uiFH2ygz67Sl2tvW0e214rexHJ6VNzzjR5g/neZ3R1ztFVb1vEa6EwYO9gX+PQ12vymx+GjfC1t+/nxXN1qPT7Gs9dxTlORrRwp643jvbOZjK+ojBzr6QwX1dDp9NtBuwgbduyHDjvjdV+Yt2lfH6YU8cbQ7+RJTL+seFlvkZGjJo71IcWH4IMzn9FtIz19MDx4cBKul/eE+3ld1OVP8uBUr44jHOR3+D+dmouYcKbcCOGuuHGUr4ZV1RvHrPfI9gnSnSokxvTDyG84JsmnZv0oAuC1gfhUBlLa5YVz7Q+CEPIY9MH4QzoqQ/AsW8seul1yLH8Ow7YCbkd89dolxsvPgs87i9HUL9tosG/gZKpt2aWPtVeVlG+qnXY5RYd9u2PO9b/+JQOW24IHMP8K+uw0zQ67Al2Hba0zVA6bD4T2DbbRZed56LLLnLosqVPdYzXoWWt0goZK65Bh257WaS7bnvTE8HrttG2St32E0+Ertveleul/m867EdFhz2rQ/6ZUy7qMeKWd3b+fcLciEM9HXZNddgTlA6bfjAbGTua66jCLPddc+q84qhzXBb4nuA3Vzbf60t9vE+pa+xI3WIX4DTG9F5MXfeF1HXfw1jeq6nz3kid95PUdT9PXferwBTqGA+mjvsQ4OfAQcBvqANv6vPrvmOBqcCWwEOBBwGzgEOBU4GHA48Angg8ijrHEcBLgCOBVwFHAVdSV76OuvKHgGnAF4DTgNuAY4Amw44DxgHHAnsCxwGPBJr1o4ATgXOAJwKvAE6ijnwy8GvgycDW4GcGsBtwCnAQ8BTgSOCpwDHALOBE4FTgFGBX4LnAbiq2OJ97PIcTQtBhjqonHWZ96S//b7rLTQsae2vjGkBfGYqucuuqSGM7cuzq2ukoG0D+n4mdXefW1fr/k+n/z30qJB3DT+FhyK/iW6P0IbX+f9iItOFHHJeeOQt7hs4IfMttTpJ9TmdKmf5EzwlNL37bBfpoad9nmO1Hqvo45bvyjJQPkvbPJ4lf9akBuSfB4p95lrlvdxDr8QM+X5vF50vGWnnfYR5LAD4v7fCbDh/KP8PceZTwsDuP0ufOmpOflanl08CHrXxiP3o+od7OpwEPB8+nUxqATwFdUptGlfn0LtoWVvBp9OGO6+glF/6scPCnsBr+FDr4c4+FP6/U4XX0UpD8ecXOH3WvpTZ254/xSGX+8BrS8qjlI1YesQ89j1Bv51HcI8HzqCbXUG15FLiGEqgzHIe8H/Io5LWQS/MUj0xNZLoSfG2+ieTNYmk71DD/J39IHyPtqZNRMuY9UtdE6XMulHKYigMyBI3GYNBDidxbWMcL7gOvZHTb/EbxFXMnr4FlyCPA43L7/LgAwUV3xzn+Iu0vNDqhb86RfcTZ5tiWc4zeYNbNResmRjwkjUHIE5AplyOZr5gKfc1f0te+Sn/XROjnG83xf2fwJaoSX2rOJ66LUDoL5/3SiOsiDua1YLa9rC3eGxsUr6Zl5fNaOGWhTKBCzyBFxa8nhKaDjJ/8Yj8xtms9KzH4cft1DfI7tnFvcBn3P+jbeNQ6bp7jKsc=
*/