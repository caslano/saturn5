/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_SET_FACTORY_FWD_HPP
#define BOOST_FLYWEIGHT_SET_FACTORY_FWD_HPP

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
  typename Compare=mpl::na,typename Allocator=mpl::na
>
class set_factory_class;

template<
  typename Compare=mpl::na,typename Allocator=mpl::na
  BOOST_FLYWEIGHT_NOT_A_PLACEHOLDER_EXPRESSION
>
struct set_factory;

} /* namespace flyweights */

} /* namespace boost */

#endif

/* set_factory_fwd.hpp
CWeUeb99SXoGW3yh39r0sue3pItZaiDduq1xVajpEpT7WYETSIkNToL5EaXfi3GVTK6YPqXK+4x+EmfLCMtcG+ZvJXwtAvH9gEKN55HyjFJKQoh9TBpLKxn9vmms+Dfbpuf34lcT33a5AN1aud81MJde4Dan0BwcSJJ8M1wC7PYWY2F9S+zmckpKICBl3/VNnjfdftvzFXrv91Lv1uTTQHYsvsjmGmfqx8HyPivlS8bjiO25
*/