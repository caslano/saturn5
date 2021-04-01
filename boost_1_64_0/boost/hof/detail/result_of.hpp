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
9claQFA9AhVoL42svyjDiqTx7+7UGgCLZLYsRxcYwf/rUOQ7epXU9JKTA4J2KCVnsrcn5mwr7DvTkunZLBuai67A8TpydKehKMVPqEOMmR28aQ6+JAFWJBUFnIzqPL0wHN1AVYAkxHwAT4LNjqIxe9U75N/lawkLIjOM5/dQIg3nVm9vnx3nip7jWXwcQA3Js8nikFhhp0cmwfVmvC5y7vNeV58Vwph8UeMKd4qNI6T+3J6VMWQAx9AZEhlzy9MO72ak7TU8nGEyi3+AIqhQPaOrupvvUCtdZOwF6w6gyEgeYnh/WU07aKG6ROl8Efj3ZghnbDX4FfUiGQ921Lu5Pzb0t0T5MdUCyH5c8DncSawxhAg6yuMAby9CJqFBwvXCc0XxjGj/x8G7ahruGbXs2Kp6MoP+p9zBOC1xibJhVdYrAZZisDMuzdLZSY3Ao8+LyLPSjPqWDMnx5L20MgT7y+MzufZOr8muGpQLBaVMRzDk0+RndUaj7kVhQAktRFzyw3MrWZnPZGZwqH5WBEhUxNR7hgHgNgdpuy2P+KQQsYHBXpNdHMyH4mPmvQ==
*/