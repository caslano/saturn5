// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_POLYMORPHIC_BIN_HPP
#define BOOST_HISTOGRAM_AXIS_POLYMORPHIC_BIN_HPP

#include <boost/histogram/detail/detect.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace axis {

/**
  Holds the bin data of an axis::variant.

  The interface is a superset of the axis::interval_view
  class. In addition, the object is implicitly convertible to the value type,
  returning the equivalent of a call to lower(). For discrete axes, lower() ==
  upper(), and width() returns zero.

  This is not a view like axis::interval_view for two reasons.
  - Sequential calls to lower() and upper() would have to each loop through
    the variant types. This is likely to be slower than filling all the data in
    one loop.
  - polymorphic_bin may be created from a temporary instance of axis::variant,
    like in the call histogram::axis(0). Storing a reference to the axis would
    result in a dangling reference. Rather than specialing the code to handle
    this, it seems easier to just use a value instead of a view.
*/
template <class RealType>
class polymorphic_bin {
  using value_type = RealType;

public:
  polymorphic_bin(value_type lower, value_type upper)
      : lower_or_value_(lower), upper_(upper) {}

  /// Implicitly convert to bin value (for axis with discrete values).
  operator const value_type&() const noexcept { return lower_or_value_; }

  /// Return lower edge of bin.
  value_type lower() const noexcept { return lower_or_value_; }
  /// Return upper edge of bin.
  value_type upper() const noexcept { return upper_; }
  /// Return center of bin.
  value_type center() const noexcept { return 0.5 * (lower() + upper()); }
  /// Return width of bin.
  value_type width() const noexcept { return upper() - lower(); }

  template <class BinType>
  bool operator==(const BinType& rhs) const noexcept {
    return equal_impl(detail::has_method_lower<BinType>(), rhs);
  }

  template <class BinType>
  bool operator!=(const BinType& rhs) const noexcept {
    return !operator==(rhs);
  }

  /// Return true if bin is discrete.
  bool is_discrete() const noexcept { return lower_or_value_ == upper_; }

private:
  bool equal_impl(std::true_type, const polymorphic_bin& rhs) const noexcept {
    return lower_or_value_ == rhs.lower_or_value_ && upper_ == rhs.upper_;
  }

  template <class BinType>
  bool equal_impl(std::true_type, const BinType& rhs) const noexcept {
    return lower() == rhs.lower() && upper() == rhs.upper();
  }

  template <class BinType>
  bool equal_impl(std::false_type, const BinType& rhs) const noexcept {
    return is_discrete() && static_cast<value_type>(*this) == rhs;
  }

  const value_type lower_or_value_, upper_;
};

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* polymorphic_bin.hpp
Cc25zvfQhN3hOhqPRBCHUsQT8pAZEZkKMTdjvR0HaW7l+NRI7eW4k9pZKN/l/+HkcfeVFAMKCoH9ZNSb4pq6iki56eNgfyrvdI0J2pF6FkJVLz5XIkdbqbmxefLibcNpZrG6mjnwXIp1QSZiOuDNWIY4dxLzSFO6dcc6+TdCyyEPMv5KvQUBY5SWxVSfGC3KZZZZ0gSjFfNz61jHA4c+knAxcalmG828z1QGpyPV3szzz4fKS+MtJqXaNYTXhbLu8//1fTnOMAC+VaINz3iqEGYX9++LzkhGeEwEAAZ3LKpDpApm6uEnA11+7w3P2Zu1eDGrO4WVGplEWzykSuewXgN7GMhXIT9AMhKUzrDtO8JXdp5C5jivmczVXjW9sVwlbD7+12YsUg10urhUZPYikpKT1hGfaxCMz/VmOtFJfC5DMXFuW6mQ1vA2QhdTH3MC1jfRo6mt5XO1wRKsK30JjOXf+t7trdsULyiME/4fBa96UMZDMmud0bIaWhx82VujZhpAAvyHn0JK0noWSGBTcG2Ib8j4gkvRpDG7PLIyqsVK/Zi/asKuUhYsYA==
*/