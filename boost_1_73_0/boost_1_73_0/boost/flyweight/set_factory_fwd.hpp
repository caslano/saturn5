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
YF81uXvlhbSSttUJL7z6d11dXYkv618iNiXFbBzo2hOzjQKsbxri+jimVhOuTjhZeb4gYG5LA/VU3qzcRfEB62cx5eNd85jyA41b6w7Hu2ZaFTEyCpxUtURSQ6oetyna0RPTWBRPjOk1VEJEUtWYCBlQQX9k+8sAAwNdg6xSZWQfVKMnqiBbBXkqKFGBQ9Vglkazx9w4YaoKZqix5WpsknmJF9ebRLxrE09xbm9Su3ojqivhcl1dH/o8Z8DcqQg=
*/