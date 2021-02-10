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
4OrlaAyN/a1qNoeEv9paLgTzMtGS8TBkMYZWIry5K3tlhTssjgLMt7lB7a5l0Yng06zQqCdmpgPTci6yUnsOhyMUMteZ6KMt56p6DP2CJ1TxHbpSD41L+GAihj6+t4XUwizEXSByR2QLhN9FIWrh8fPnVh/Rq1P25+Bq5O065vbhJtSK+hJsBVfgypaOXsCMAOL7X8BLh+hVWl2gohBW2zDVlu82ptcqsLJGV6pwImMO29B5zplH1N8moLKjXSn/ZgKWlm1J4XdlfDYUON5d2tCSde850WZiMWOsFd50bKUeI81w7O4axse/Wm433S7HZ+x0NBw0OFvJrgoNjavCSitVk8IShlzzDvZQf1hhpzDgxm0+G5OrwqsGofUpSARPy/zAeLNivjuKv1r9lspaVfF6Gzg3fKJCCIbm9TZGwHL+AmEnsKlYm+lmzC7nqpm/xqCNqbkyIB0TWtXebY7MzcI6xovZ/hKfI4/ryCcrSK5jIKGugYWpYuYOcv/X/tNnf9dqZb0IsjI18vbdtFBpdQg1bL497LIVSNt3FwUlCtx1OuKO4w4mOkE2P3io8LuzfnIag3HzdG65sOGkKnRTiajSaprMkmzKEzfGTczY2cXo5fEFO764WBlXFm2XjguF70nbxCTpxZFzCetH
*/