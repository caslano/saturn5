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
#ifdef _MSC_VER
#define BOOST_HOF_IS_LITERAL(...) __is_literal_type(__VA_ARGS__)
#else
#define BOOST_HOF_IS_LITERAL(...) std::is_literal_type<__VA_ARGS__>::value
#endif
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
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
*/