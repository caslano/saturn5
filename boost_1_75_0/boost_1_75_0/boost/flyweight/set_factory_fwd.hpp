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
GhkRVUjESV/c9RDazCEvymWJ/Ee9aRgFpljeYq+P5dN3KVnH5FXpfK5+SwgDYEHV4UzhN5ryTbpJs42y0Tj8cKbJ2MYGz8xgp0ttfhajafVyw2gKiPeJPerXFBoyB/j1Piv2sFl87p5BInddihrjTY/XNW9yEJI9jSjj8uHJP4OWD9DNFiNVjayv3L67rcnRY0fY+E9MNcJR44DYU9nn6XD5r/oTRt35xbBt0sgH512FHPC4d8uOs0ABL/0wwxgeGttkezK1QXpg3C2QH75JBrzbIqa7qxGibSbVy+GlQ/o621idPatg/jYBAsrifC4C2jGuse7CMlkPC05C+5sN5z8G49LtSjx40uj0LUYD+tGdxR0airusxq2A8kJYzBSCr8GILLsyNAs/7qf2rfMOicWYwQ1RawFcHTzzQYYBb57V25OG1d/ahnjuWQG7TSZXnuRZUYe/Lp63xnlGUTwnrDOGISSdtaL1ScXyYXXMwX/iTPLC+35kFyn2c2W/lrA7JbyeJ0w9ggnjjvCECJS3VlWWtrEMdv8D8JbwJPC/8jrxfj+lidH/R2m++CKvYd4JyNDycMPaALweMF5+drtmvCyWm4vlfSAijxMKq+b2u+d3zsdEfC7vmadgpjXPYuxZFxv+8xpL4Vw71xkcaozhBp6iVJ0O2+sM0T8lWLl8XMrTZZN6UBp3StFshf5ue1LR1+MBE6WSeEESFFT3
*/