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
DfZ5KBEhJSIuJT6FtVnM54YSk4oTUyZzQT8yQxAYiSYXvsspg7dBESSKI0xSP6/tnWCEvZK/8i8ICYkKit9FSEBLa58O8mqplMBhmW9I+M6J3gVa6R+Fft3GzXm92N/20mSk39CkabSHJmE+DWhUsn/oQmvb+gjRsQtjo/9hV1sSRQ7jOVlo9SBoRSJ+a6JlM+oThehlVWCPthctxXwgPnGy/EeNotG5P658rOY1XxtOcH/1
*/