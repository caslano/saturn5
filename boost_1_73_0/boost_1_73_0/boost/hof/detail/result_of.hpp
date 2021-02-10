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
EgtZiGJA5QNg649VIVYafVkl6QrYjBQxLFDSlJaCcpCJNhDTsKy7SopSJcuqTDKpRRmAB5aJjNSuJXR96kXETkIskyBZlJkCLOtuoxLfcXEojiSJ51zEJUWMcT8LqNgVpdhyeMAmWqY6UuK5VBGkvHEw/JnWiLmMtgI25Ar8FAAylYhiHxyY3UaPIszjIgnBOWRxzghJIVZFg64qiRsoMdGkoLyTHIbBey4U2LO29oUtFzX7NmB1ElcH0wBiMcK9GaO1guWI4Feecsb1eBvGvFJ5ViBOa+asE14ykoiKRCimmmeqpIVMnpHylRggR6pM4iqNmFvGSW/yy8OsgDiaTRxU7R/82CZFwSlkfkoIqG5UJMumIiK54/Jo3Rhl+U4lm4eS3l9c/I2GuL2/GNCn7EHSLEq3S6E2bUkfoGEaGAPwyHcD1OQqWeOOJJ3Dwr6OmmgX2br8zkXSmNcRb2Khiw+f+Z5VKDmh48nuLPe8B5ygp2QFD3RGOJjRMnsSjBTvHZAZgiV0qdRZPvBth/JcRErPM+QUmt1SurUp8Cbzz5ZvkxPQne/dO2N7TIYV4N0gyx1rIWsxv/V8GjvBaGo5KGRrOiVo+ZY7d+yAsT4781vy7RvLh4oHLeAdsN3RdDF23But6Mzupg6sHADI
*/