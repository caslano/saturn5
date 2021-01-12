/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_HASHED_FACTORY_FWD_HPP
#define BOOST_FLYWEIGHT_HASHED_FACTORY_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/detail/not_placeholder_expr.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost{

namespace flyweights{

template<
  typename Entry,typename Key,
  typename Hash=mpl::na,typename Pred=mpl::na,typename Allocator=mpl::na
>
class hashed_factory_class;

template<
  typename Hash=mpl::na,typename Pred=mpl::na,typename Allocator=mpl::na
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION
>
struct hashed_factory;

} /* namespace flyweights */

} /* namespace boost */

#endif

/* hashed_factory_fwd.hpp
XAJXwT/C1XApXA+vgBvgcrgFXgm/g1fDHIe8DFvC62AreCfsBG+Ew+FNsBLeDGfB2+AceAecq/bXxM3jrfuVa+d1vu43n6f7T+8t9d82Vxc/T9fq1oAZhpp1a908Xd1Vd/23Xf/28f+Y8dOnTKr8zcb/dOjtWl3aCLmGmBiHu+vlv4iN8eTxZaXFlbyCHCSl4zzOUJJxXmmZ/7gZP/bp/I90EwHUva598SMxq7jmf9MBx7Vt
*/