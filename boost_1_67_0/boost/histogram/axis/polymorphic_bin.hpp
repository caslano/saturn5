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
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
*/