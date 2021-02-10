/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_ARGS_HPP
#define BOOST_MULTI_INDEX_DETAIL_ORD_INDEX_ARGS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <functional>

namespace boost{

namespace multi_index{

namespace detail{

/* Oredered index specifiers can be instantiated in two forms:
 *
 *   (ordered_unique|ordered_non_unique)<
 *     KeyFromValue,Compare=std::less<KeyFromValue::result_type> >
 *   (ordered_unique|ordered_non_unique)<
 *     TagList,KeyFromValue,Compare=std::less<KeyFromValue::result_type> >
 *
 * index_args implements the machinery to accept this argument-dependent
 * polymorphism.
 */

template<typename KeyFromValue>
struct index_args_default_compare
{
  typedef std::less<typename KeyFromValue::result_type> type;
};

template<typename Arg1,typename Arg2,typename Arg3>
struct ordered_index_args
{
  typedef is_tag<Arg1> full_form;

  typedef typename mpl::if_<
    full_form,
    Arg1,
    tag< > >::type                                   tag_list_type;
  typedef typename mpl::if_<
    full_form,
    Arg2,
    Arg1>::type                                      key_from_value_type;
  typedef typename mpl::if_<
    full_form,
    Arg3,
    Arg2>::type                                      supplied_compare_type;
  typedef typename mpl::eval_if<
    mpl::is_na<supplied_compare_type>,
    index_args_default_compare<key_from_value_type>,
    mpl::identity<supplied_compare_type>
  >::type                                            compare_type;

  BOOST_STATIC_ASSERT(is_tag<tag_list_type>::value);
  BOOST_STATIC_ASSERT(!mpl::is_na<key_from_value_type>::value);
  BOOST_STATIC_ASSERT(!mpl::is_na<compare_type>::value);
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* ord_index_args.hpp
YU31YHzhfHUca6N1vJ9kTMGQytQkZgsGQ3sF2BCLIqPhFzi7cOh7L+SWiZgX3NSljWeLcOIvYirqoAYg08dm2VI8m9No6LKoZ91aJFxGMQ0uWOmL/4VF89+v6Ki50Bey2A/enoAH4Xo+C/xFhx+fwL+0zX3RX68Mv/Qj34Vgszi1nSDsQroMzxqjGqctOK6j6dqjE5k/WmnrFScCWVGVH2yAN7R3nEyqHAt72Ns1ulr/qrBIkP5TmWOJsPHrswbPuFtox90utfXtFru06r6h7Gzn/ANQSwMECgAAAAgALWdKUgsvxgZIBAAAlQkAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE1MTQuY1VUBQABtkgkYK1VYW/aSBD9zq+YUukE1MTQ00mXkFZHSdKicoACuSjXVO5ir/Fe7F1rdx3CNfnvN7M2kCjN8aWOkrVn5715OzM78Vs/76lBC/Y+gfsN8MHVIaZa/cND+2PvILiH8gdR17juC+LDDnIfNGE/5B4aDhJUUY7pPQj2BbombfTHJ+R1QK9oQRghBypfa7FMLDQGTegeHv4ObXjbedvx4IRJwVOYWS4XXC89OI6c5Y+E3d0dGP7eA26BpQcV1TwRBoyK7YppDvieipBLwyNgBiJu
*/