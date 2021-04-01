/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    intrinsics.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_INTRINSICS_HPP
#define BOOST_HOF_GUARD_INTRINSICS_HPP

#include <type_traits>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/config.hpp>

// *** clang ***
#if defined(__clang__)
// #define BOOST_HOF_IS_CONSTRUCTIBLE(...) std::is_constructible<__VA_ARGS__>::value
// #define BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(...) std::is_nothrow_constructible<__VA_ARGS__>::value
// #define BOOST_HOF_IS_CONVERTIBLE(...) std::is_convertible<__VA_ARGS__>::value
#define BOOST_HOF_IS_CONSTRUCTIBLE(...) __is_constructible(__VA_ARGS__)
#define BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(...) __is_nothrow_constructible(__VA_ARGS__)
#define BOOST_HOF_IS_CONVERTIBLE(...) __is_convertible_to(__VA_ARGS__)
#define BOOST_HOF_IS_BASE_OF(...) __is_base_of(__VA_ARGS__)
#define BOOST_HOF_IS_CLASS(...) __is_class(__VA_ARGS__)
#define BOOST_HOF_IS_EMPTY(...) __is_empty(__VA_ARGS__)
#define BOOST_HOF_IS_LITERAL(...) __is_literal(__VA_ARGS__)
#define BOOST_HOF_IS_POLYMORPHIC(...) __is_polymorphic(__VA_ARGS__)
#define BOOST_HOF_IS_FINAL(...) __is_final(__VA_ARGS__)
#define BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(...) __has_nothrow_copy(__VA_ARGS__)
// *** gcc ***
#elif defined(__GNUC__)
#define BOOST_HOF_IS_CONSTRUCTIBLE(...) std::is_constructible<__VA_ARGS__>::value
#define BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(...) std::is_nothrow_constructible<__VA_ARGS__>::value
#define BOOST_HOF_IS_CONVERTIBLE(...) std::is_convertible<__VA_ARGS__>::value
#define BOOST_HOF_IS_BASE_OF(...) __is_base_of(__VA_ARGS__)
#define BOOST_HOF_IS_CLASS(...) __is_class(__VA_ARGS__)
#define BOOST_HOF_IS_EMPTY(...) __is_empty(__VA_ARGS__)
#define BOOST_HOF_IS_LITERAL(...) __is_literal_type(__VA_ARGS__)
#define BOOST_HOF_IS_POLYMORPHIC(...) __is_polymorphic(__VA_ARGS__)
#define BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(...) __has_nothrow_copy(__VA_ARGS__)
#if __GNUC__ == 4 && __GNUC_MINOR__ < 7
#define BOOST_HOF_IS_FINAL(...) (false)
#else
#define BOOST_HOF_IS_FINAL(...) __is_final(__VA_ARGS__)
#endif
#define BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(...) __has_nothrow_copy(__VA_ARGS__)
// *** other ***
#else
#define BOOST_HOF_IS_CONSTRUCTIBLE(...) std::is_constructible<__VA_ARGS__>::value
#define BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(...) std::is_nothrow_constructible<__VA_ARGS__>::value
#define BOOST_HOF_IS_CONVERTIBLE(...) std::is_convertible<__VA_ARGS__>::value
#define BOOST_HOF_IS_BASE_OF(...) std::is_base_of<__VA_ARGS__>::value
#define BOOST_HOF_IS_CLASS(...) std::is_class<__VA_ARGS__>::value
#define BOOST_HOF_IS_EMPTY(...) std::is_empty<__VA_ARGS__>::value
#define BOOST_HOF_IS_LITERAL(...) std::is_literal_type<__VA_ARGS__>::value
#define BOOST_HOF_IS_POLYMORPHIC(...) std::is_polymorphic<__VA_ARGS__>::value
#if defined(_MSC_VER)
#define BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(...) (std::is_nothrow_copy_constructible<__VA_ARGS__>::value || std::is_reference<__VA_ARGS__>::value)
#else
#define BOOST_HOF_IS_NOTHROW_COPY_CONSTRUCTIBLE(...) std::is_nothrow_copy_constructible<__VA_ARGS__>::value
#endif
#if defined(_MSC_VER)
#define BOOST_HOF_IS_FINAL(...) __is_final(__VA_ARGS__)
#else
#define BOOST_HOF_IS_FINAL(...) (false)
#endif
#endif

#if BOOST_HOF_NO_STD_DEFAULT_CONSTRUCTIBLE
#define BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE(...) boost::hof::detail::is_default_constructible_helper<__VA_ARGS__>::value
#else
#define BOOST_HOF_IS_DEFAULT_CONSTRUCTIBLE BOOST_HOF_IS_CONSTRUCTIBLE
#endif

#define BOOST_HOF_IS_NOTHROW_MOVE_CONSTRUCTIBLE(...) BOOST_HOF_IS_NOTHROW_CONSTRUCTIBLE(__VA_ARGS__, __VA_ARGS__ &&)

namespace boost { namespace hof { namespace detail {

template<class T, class=void>
struct is_default_constructible_check
: std::false_type
{};

template<class T>
struct is_default_constructible_check<T, typename holder<
    decltype(T())
>::type>
: std::true_type
{};

template<class T>
struct is_default_constructible_helper
: std::conditional<(std::is_reference<T>::value), 
    std::false_type,
    is_default_constructible_check<T>
>::type
{};

template<class T, class... Xs>
struct is_constructible
: std::is_constructible<T, Xs...>
{};

template<class T>
struct is_constructible<T>
: is_default_constructible_helper<T>
{};

}

}} // namespace boost::hof

#endif

/* intrinsics.hpp
uIomL33Q93NJIDPB6HPq9YaaouVtVumSmcTT3pANfhQVZpSKY+zGH/pBpJW6nPP30crpC8I5EDBX3LrKRHZi2LQzRQ67v3xNP25vxiS43f3FC/rWnatlImZXK+bpb5b7MKwTsJv1SlMWwgdjFnejdUz2X9sDdEd9Z0SKN47C12caegYMy2F89qq3k803Tjk0Ow6wWMEkuvy2tnE7hYZjAPf8eew6N+tizI7Ht59wVaCPhmyw7haBlsi7GYZi9u9MZYQvqcAXZHZ0v+3QPFkS/9YNbCCNkhUH0zzteDfddE72xlJNRWFHwuBrCldNklGjCuXWmXBP5w+CoTxILDn8wp6b4XMSHshJ17qPercnbmtlD4x8Mmgv3shapIDaTRzvN1OQh8ib1Dpq4e8JTA4WedfUhaBnuisAJ2J1WrgkjjXyyzuhs1DAwt4+cLPE8v1CKveEsCb8z1P2uexHg1TgDC8GFfLpKoZvyt266uKcWMpuNAULwN5aDBwIb59HEF9pXx4F+iEXefBdixujxCAEuTpyBemvCpqZHNbxEGJInMVvcGtEiMJTpCXLbA==
*/