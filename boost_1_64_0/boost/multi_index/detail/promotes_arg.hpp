/* Copyright 2003-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_PROMOTES_ARG_HPP
#define BOOST_MULTI_INDEX_DETAIL_PROMOTES_ARG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

/* Metafunctions to check if f(arg1,arg2) promotes either arg1 to the type of
 * arg2 or viceversa. By default, (i.e. if it cannot be determined), no
 * promotion is assumed.
 */

#if BOOST_WORKAROUND(BOOST_MSVC,<1400)

namespace boost{

namespace multi_index{

namespace detail{

template<typename F,typename Arg1,typename Arg2>
struct promotes_1st_arg:mpl::false_{};

template<typename F,typename Arg1,typename Arg2>
struct promotes_2nd_arg:mpl::false_{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#else

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/multi_index/detail/is_transparent.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost{

namespace multi_index{

namespace detail{
  
template<typename F,typename Arg1,typename Arg2>
struct promotes_1st_arg:
  mpl::and_<
    mpl::not_<is_transparent<F,Arg1,Arg2> >,
    is_convertible<const Arg1,Arg2>,
    is_transparent<F,Arg2,Arg2>
  >
{};

template<typename F,typename Arg1,typename Arg2>
struct promotes_2nd_arg:
  mpl::and_<
    mpl::not_<is_transparent<F,Arg1,Arg2> >,
    is_convertible<const Arg2,Arg1>,
    is_transparent<F,Arg1,Arg1>
  >
{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
#endif

/* promotes_arg.hpp
3p1vgMtrEPp8h3N1cxB83mKAUqXel+f1HS1ECn8OtdnaU97YsoXm0NRfzk6YxbRRcoXFNVeJBtGc4aUST81e9WtG0nXLCa/OM/omMLROnSz88GeIqNvGV6PYDa8tP7efOY5a5f/tw67WmCO5vSm610PVd816Udjj4IKnr4mF/HjwT3QHTTNMU5rE4zJ2V6kG8mn5lziC/R9TqpXna1QWRpY+hteSM7jqNkL/ilmqo7Ivy5r1sSR3hteDzjmy3zfRFVvkVc12PgyMay+FPYDjpkdQaYkX3W9e4aQW4XSq3yCh4uoO67vYX+XF0wcGGeKuDezI1TWCl3EFT6aONs6cIZNr+6nQx/L0B5UZPF3S61vs3StaSiJF59cTZMA/VgPrFCxbPCdPsmB5WiTRRCVsr3iM7KtGKq1nq18bBIzzlNeqeTmZZoS6mrksGcWfVEn2cHAFC9Zx5vAJOWW4TIi8NlRLozsuo3H7ZedZa9mcA4MIXc2n6WUgT6EjoVY/k1AgVXSFnNXy5F9bPz+BnwVNbBY0oqrnvu/+VKISFxQMHzTtBiaFV3P5Lm42sA==
*/