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
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
*/