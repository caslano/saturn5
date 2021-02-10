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
WmW9aFNgNYtbDXQjqu03eeGwvCJUuZC5hZ6/ovFKHNgqM2TrEu54puzymkah+J7vHFRgMOcoy0d0tehOvQR1S3SBV9YtkN1B0fQPV3z3v+L6B3PXQNw6+gfXRsI/C41lGiwLZ6G5BSF7OMmtNTe4Jitilezy/bBMqKmCG4a1ZHrK7G9l5iSQwVlKrWtXiW0aQ67Ol3JgT5wmu76hY0u1druFehtdufb9YsUuu6WWtDJeQPY1bzsBWmQd6gbX/dSA68Kz/GoWve7VbvqWa2tPIG8qXHOZD+9mlokyy+RpcHZdo4dCUZfnUGAFkPjEpUx+jJd0yffQqvrG5mF4aToFNbD85j6NQ9ZnkoUD5oUtIKqECiq8DUyh2ELip6hfByUTamtpqqJMc6vbx1TrCLUD1I37X113LcTDCsANGNhlC+9OWbS94dNvsFqPnQfAs4zBcyjqKlbewrLYSoYwnIkflunmhx2mKMQqnwP42A6JXNOIMgcuqlpvU3nNvbVx69ypHBseNUtZd2k0QWxCu0KvJL4X31/Vb6BD8Uz1N6eFotcfGBNEEdV7H1RWNAyuGV6mSv8BV/KmTWHq67vAnDFdbM5DBC0blrbDEq3i3QhWV1/bQYfWV+5kunLH7fBDq5AUPI3g3emy48167nSW
*/