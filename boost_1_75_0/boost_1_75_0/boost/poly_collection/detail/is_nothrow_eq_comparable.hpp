/* Copyright 2016-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/poly_collection for library home page.
 */

#ifndef BOOST_POLY_COLLECTION_DETAIL_IS_NOTHROW_EQ_COMPARABLE_HPP
#define BOOST_POLY_COLLECTION_DETAIL_IS_NOTHROW_EQ_COMPARABLE_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/poly_collection/detail/is_equality_comparable.hpp>
#include <type_traits>
#include <utility>

namespace boost{

namespace poly_collection{

namespace detail{

template<typename T,typename=void>
struct is_nothrow_equality_comparable:std::false_type{};

template<typename T>
struct is_nothrow_equality_comparable<
  T,
  typename std::enable_if<
    is_equality_comparable<T>::value
  >::type
>:std::integral_constant<
  bool,
  noexcept(std::declval<T>()==std::declval<T>())
>{};

} /* namespace poly_collection::detail */

} /* namespace poly_collection */

} /* namespace boost */

#endif

/* is_nothrow_eq_comparable.hpp
ewPoYvQpQuSPSWgD0lTynvDJRvskLeHf05p6kBAwPbI9hQb84fCjAVRN/jSZeDK3Vt+SnI0sI7/lnAwsqzeJ/OFT8yR1P6V3f0pxMh8DDIEy0oVeUD15+9Y9hSc8LaZfDkcysGz8USDBU4jnpweczsGnEL+nEMBTSkRsA8gJ8Mek5mmS2tAZmvMY8iQZP0mgP+4j6inJ/h/l6QqAnAKeVOM/ouKfVJ0nFav69tfLxPU/Rn84pz/JguVwTqrbh3D09/LFaqXUijSC8U4U7m0ve3ZDCIkq/2SgtKiw6KJ+T45eNDhfISMmrr4IOgy/4CsC9Fyn+WNzm8Do2qIOw51ezxBu7qpIhOi8gb8wGv5pz8miw/M0AkOkhcKezBxPZvwn83aqP3Zds3i207Mnwf5J8HzyWh+HbHOxQJ8iJ57SlVs+pUx5WkN8XgL73BoefIH6NABYwYOddChZlHA8GezoVrPGx+xLQET+2U6EPe3YnWp37D1iOA9EZ7JCURdUIfnYndJCWU4vTA0zwnz8VIR6IJIQUTK/j+/XC49noy+EKYVEseVJ/GOcODa7QwRfEPyJWt5LfNPr6ZUiwbbFKcMhJ1F7bfentrjqRx7JNJmnN8qixxDbFhvKmCnl9XpTNcTmhYYDE7Xi4js09RFzaHQZ8NEupDIHtR7CI/k5ysFJinxZQM3xNGS9G2etF6c9hcTHmBnSrXbgr3agxAy5
*/