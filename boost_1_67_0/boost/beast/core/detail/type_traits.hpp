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