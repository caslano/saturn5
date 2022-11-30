// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_POLYMORPHIC_BIN_HPP
#define BOOST_HISTOGRAM_AXIS_POLYMORPHIC_BIN_HPP

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
    return equal_impl(rhs, 0);
  }

  template <class BinType>
  bool operator!=(const BinType& rhs) const noexcept {
    return !operator==(rhs);
  }

  /// Return true if bin is discrete.
  bool is_discrete() const noexcept { return lower_or_value_ == upper_; }

private:
  bool equal_impl(const polymorphic_bin& rhs, int) const noexcept {
    return lower_or_value_ == rhs.lower_or_value_ && upper_ == rhs.upper_;
  }

  template <class BinType>
  auto equal_impl(const BinType& rhs, decltype(rhs.lower(), 0)) const noexcept {
    return lower() == rhs.lower() && upper() == rhs.upper();
  }

  template <class BinType>
  bool equal_impl(const BinType& rhs, float) const noexcept {
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