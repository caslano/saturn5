/*=============================================================================
    Copyright (c) 2015 Paul Fultz II
    result_of.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_DETAIL_RESULT_OF_H
#define BOOST_HOF_GUARD_DETAIL_RESULT_OF_H

#include <boost/hof/returns.hpp>
#include <boost/hof/config.hpp>

#if BOOST_HOF_HAS_MANUAL_DEDUCTION || BOOST_HOF_NO_EXPRESSION_SFINAE

#include <boost/hof/detail/and.hpp>
#include <boost/hof/detail/holder.hpp>
#include <boost/hof/detail/can_be_called.hpp>

namespace boost { namespace hof { namespace detail {

template<class F, class Args, class=void>
struct result_of_impl {};

template<class F, class... Ts>
struct result_of_impl<
    F, 
    holder<Ts...>, 
    typename std::enable_if<can_be_called<F, typename Ts::type...>::value>::type
>
{
    typedef decltype(std::declval<F>()(std::declval<typename Ts::type>()...)) type;
};
}

template<class T>
struct id_
{
    typedef T type;
};

template<class F, class... Ts>
struct result_of
: detail::result_of_impl<F, detail::holder<Ts...>>
{};

// template<class F, class... Ts>
// using result_of = detail::result_of_impl<F, detail::holder<Ts...>>;
// using result_of = id_<decltype(std::declval<F>()(std::declval<typename Ts::type>()...))>;

}} // namespace boost::hof
#endif

#if BOOST_HOF_NO_EXPRESSION_SFINAE

#define BOOST_HOF_SFINAE_RESULT(...) typename boost::hof::result_of<__VA_ARGS__>::type
#define BOOST_HOF_SFINAE_RETURNS(...) BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(__VA_ARGS__) { return __VA_ARGS__; }

#else

#define BOOST_HOF_SFINAE_RESULT(...) auto
#define BOOST_HOF_SFINAE_RETURNS BOOST_HOF_RETURNS

#endif

#if BOOST_HOF_HAS_MANUAL_DEDUCTION

#define BOOST_HOF_SFINAE_MANUAL_RESULT(...) typename boost::hof::result_of<__VA_ARGS__>::type
#if BOOST_HOF_HAS_COMPLETE_DECLTYPE && BOOST_HOF_HAS_MANGLE_OVERLOAD
#define BOOST_HOF_SFINAE_MANUAL_RETURNS(...) BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(__VA_ARGS__) { return (__VA_ARGS__); }
#else
#define BOOST_HOF_SFINAE_MANUAL_RETURNS(...) BOOST_HOF_RETURNS_DEDUCE_NOEXCEPT(__VA_ARGS__) { BOOST_HOF_RETURNS_RETURN(__VA_ARGS__); }
#endif

#else

#define BOOST_HOF_SFINAE_MANUAL_RESULT BOOST_HOF_SFINAE_RESULT
#define BOOST_HOF_SFINAE_MANUAL_RETURNS BOOST_HOF_SFINAE_RETURNS

#endif

#endif

/* result_of.hpp
S0BIB8FBWwhEuBiES0DoC0JfIlwEwsUgXADCBURIA+EiEPqB0I8IA0BIAyEVhFQiXAjCABD6l9YgPBW/ItkJ2uViVwJPKDQOv2qSJciFxwz4y6CXr8MXES4D4TIiDAfh60sQFITLiZADwnAQBoEwiAjXgJADwmAQBhPhahCuAWEICEOIMAyEq0G4AoQriJANwjAQrgThSiJkgZANQiYImUQYCkIWCFe5QBlGt2nIElwremgl8DjExZD585nFJFepW/QD9wSXNhtM8ifSEeY4Zv8tvHLKcIr1mDfxyoNTSgZ6ANmnCDTKvaTTXbj/ne8o8L8LLh6epLDaAimIdswrm67TS0lGtdF3ZJYzMBsYS8TsvBgvyuWh6fiXf+e2gFctNrvo/RbTPtfuqba+HBCv60OwhkagKN2Pbg3jLyPoi8Z9U+8H9axe5FIO/Ib4kS0IpRTE67kyc64cbd2VTnZ/BO4IQoIC3NSBApLOFHUXsofyYJKu14DLI5IfogAeNQAlHeOZpOQwdYqkKgPi7jZh/BI72+TAD4tTVmSgmD0NZ08O3dMPzmiecq3yOmZ4SoYnRJ4Jj7DHl1JhYu+l4KyOtas3iNkfTfNkQGXnuI2OkbjcZWIJibsmhEp5YTv7zcHWKOz0dUXonB7yXgnxhJkXD1/lVTvUPKTu1kvJQB1zw19rlobiGkrL6LB/xWDMLtcEhPgOHkDnm46uho7tUFYWUgoQziW6mPnMUpkyiV8/iqNXR6mylF/b8AohxxSlr1buMnEptgWVC7T3UtEb76jIyTd9Lg1RuV//RGzkfv14iNYxxFEPzPDPhLVJ6Dv4x9D2UppPwO7OX9Cp8eDpCQMS6ub1H7nB0yADgBbHuGDKPPpeOkmK9D5tWfQn4RHsH7CEqkzc36pJqOwsoXIHd2kXREUIpBzCHa9yupr2J4dx6UF+x9a24geFC6RcqO1E9EqpYTiRlby38Hmj8zs/pzyOmOi0raxq27IGUYc5XCr9VD+kl4d0zvh8Rlhxqy/gcwk3hWpmqZlrJozFzthxDkHY5g/PxlVkEFfRezdzFZk6V3Hb2+GCMJfozTnMaKULVHiY19K3q+lXmG5QEk2JJhI0oYHmyykhbTK8tMf9G1QLvhBgPSZVXq2miPUYFmMWd2NRp4ltzKeRErONdZdjbT95nEVy0B7+hK/qpUWWXJ0FvVbmi/bgGwRz8wb1JnM/kd6V1malTvbgLzou/SBK1sBXg86JCLpKDdraRQ86B0E7Q0EXyWvCSUzihXjwOG6bi2HdwtoZQl/feGPl+qYCXfi7ML+s6T2NdiMnsEd4Oqif4U4mwRzHYEE6pXIO4iNA91BDFnWGx9tfjTerPpyaGPvVr6Z4PSAP1DjMpKd3J2Yq1IlGdogHNvE4dY5VCI2Jn3/+vQBS4rObN5MmSbKChMUTsJmuzZp9IcFAGhT31azlPRT54SNpyvHQR7XxPY6YvqezV1udg+X/YMhD42cyT93pVJRMmh8ylQ36Z27345QU6zbeZQopEi5+ErWBVQ20BZ2+fAst7zyj1+79OZ2sLQ/Yy3N7eC8shz3JlPKAM7Y8d1ys14Z7J6FlD6L3jfATsz2eVRCKrAlSxvzy6ignDvnHzi/xLcA9h4VusRcX6ND5j2b8kjYzzatKHaZtXMH1DhawL4WVH5t0SnNI2v6Xd6k+sgNFqbV3mjcKq6+FDablaUbT3JrkwjshNNwN36YNd6/GhyQK33OKVzrONtyl0XD3tZd4uMvQh7sqZndT234YQHK1Iy1OF5T/U3I4MVt1TYQIpKlJS3C/nuAPKMHp505wzY6oBG0yQbIOpcpf3g1Ntn8AKy6PVkpdsWQMoo+e4Y4=
*/