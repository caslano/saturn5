/* Copyright 2017-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_EQUALITY_COMPARABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_EQUALITY_COMPARABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/type_traits/has_equal_to.hpp>
#include <type_traits>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T>
using is_equality_comparable=std::integral_constant<
  bool,
  has_equal_to<T,T,bool>::value
>;

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_equality_comparable.hpp
jBHaCg89n+pI7Zb1XMl43czwvI2TOic2yWMH6os0uJWVuU2zbZhf1Be37XaGvUPSlfDm9SP7hecHi5W9MyDanKwPwfj8VP+7mTw+th+QReXdK8lro9Hu12wl51ru7UjPJOPnkpHxPLH1Qab/moDom2N+tTwpa39bJIN+n0PYnwZrWflHtPog+BOz6J+QZ8FjAZE/ib3V0l9S4Z0OTwTksgaMxH+9z0idUlhWEi4fM6msvNRub9I1bWuZ6wLizLY=
*/