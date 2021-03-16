// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_WEIGHT_HPP
#define BOOST_HISTOGRAM_WEIGHT_HPP

#include <utility>

namespace boost {
namespace histogram {

/** Weight holder and type envelope.

  You should not construct these directly, use the weight() helper function.

  @tparam Underlying arithmetic type.
*/
template <class T>
struct weight_type {
  /// Access underlying value.
  T value;

  /// Allow implicit conversions of types when the underlying value type allows them.
  template <class U>
  operator weight_type<U>() const {
    return weight_type<U>{static_cast<U>(value)};
  }
};

/** Helper function to mark argument as weight.

  @param t argument to be forward to the histogram.
*/
template <class T>
auto weight(T&& t) noexcept {
  return weight_type<T>{std::forward<T>(t)};
}

} // namespace histogram
} // namespace boost

#endif

/* weight.hpp
RWFKRnCotGNfcVc2cwe1WZbZ2J3do7HN/w9j6lL2v2unI3GU8NVj6aUXfduj3TZL2yK/t266WPn/rIhEkCIadhQ8TMHYhJ6v/1HH7GFGef2Lu6jHYNxrUuEj6EilHiePducQGcgifZOJnOaIBicTOSDOaeUpIcx72GRJIbnbzrsbX03H+XWDaWcH487ICXbqOiJBHl/DA7QYXbW5HAcCpRQARhRR6BA5ihjrENmE3B1Xz45zh5xEcEqdIZaTlaQ=
*/