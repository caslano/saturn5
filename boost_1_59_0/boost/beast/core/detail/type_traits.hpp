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
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
*/