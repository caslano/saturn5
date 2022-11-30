// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_SUM_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_SUM_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/fwd.hpp> // for sum<>
#include <cmath>                   // std::abs
#include <type_traits>             // std::is_floating_point, std::common_type

namespace boost {
namespace histogram {
namespace accumulators {

/**
  Uses Neumaier algorithm to compute accurate sums of floats.

  The algorithm is an improved Kahan algorithm
  (https://en.wikipedia.org/wiki/Kahan_summation_algorithm). The algorithm uses memory for
  two numbers and is three to five times slower compared to using a single number to
  accumulate a sum, but the relative error of the sum is at the level of the machine
  precision, independent of the number of samples.

  A. Neumaier, Zeitschrift fuer Angewandte Mathematik und Mechanik 54 (1974) 39-51.
*/
template <class ValueType>
class sum {
  static_assert(std::is_floating_point<ValueType>::value,
                "ValueType must be a floating point type");

public:
  using value_type = ValueType;
  using const_reference = const value_type&;

  sum() = default;

  /// Initialize sum to value and allow implicit conversion
  sum(const_reference value) noexcept : sum(value, 0) {}

  /// Allow implicit conversion from sum<T>
  template <class T>
  sum(const sum<T>& s) noexcept : sum(s.large_part(), s.small_part()) {}

  /// Initialize sum explicitly with large and small parts
  sum(const_reference large_part, const_reference small_part) noexcept
      : large_(large_part), small_(small_part) {}

  /// Increment sum by one
  sum& operator++() noexcept { return operator+=(1); }

  /// Increment sum by value
  sum& operator+=(const_reference value) noexcept {
    // prevent compiler optimization from destroying the algorithm
    // when -ffast-math is enabled
    volatile value_type l;
    value_type s;
    if (std::abs(large_) >= std::abs(value)) {
      l = large_;
      s = value;
    } else {
      l = value;
      s = large_;
    }
    large_ += value;
    l = l - large_;
    l = l + s;
    small_ += l;
    return *this;
  }

  /// Add another sum
  sum& operator+=(const sum& s) noexcept {
    operator+=(s.large_);
    small_ += s.small_;
    return *this;
  }

  /// Scale by value
  sum& operator*=(const_reference value) noexcept {
    large_ *= value;
    small_ *= value;
    return *this;
  }

  bool operator==(const sum& rhs) const noexcept {
    return large_ + small_ == rhs.large_ + rhs.small_;
  }

  bool operator!=(const sum& rhs) const noexcept { return !operator==(rhs); }

  /// Return value of the sum.
  value_type value() const noexcept { return large_ + small_; }

  /// Return large part of the sum.
  const_reference large_part() const noexcept { return large_; }

  /// Return small part of the sum.
  const_reference small_part() const noexcept { return small_; }

  // lossy conversion to value type must be explicit
  explicit operator value_type() const noexcept { return value(); }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("large", large_);
    ar& make_nvp("small", small_);
  }

  // begin: extra operators to make sum behave like a regular number

  sum& operator*=(const sum& rhs) noexcept {
    const auto scale = static_cast<value_type>(rhs);
    large_ *= scale;
    small_ *= scale;
    return *this;
  }

  sum operator*(const sum& rhs) const noexcept {
    sum s = *this;
    s *= rhs;
    return s;
  }

  sum& operator/=(const sum& rhs) noexcept {
    const auto scale = 1.0 / static_cast<value_type>(rhs);
    large_ *= scale;
    small_ *= scale;
    return *this;
  }

  sum operator/(const sum& rhs) const noexcept {
    sum s = *this;
    s /= rhs;
    return s;
  }

  bool operator<(const sum& rhs) const noexcept {
    return operator value_type() < rhs.operator value_type();
  }

  bool operator>(const sum& rhs) const noexcept {
    return operator value_type() > rhs.operator value_type();
  }

  bool operator<=(const sum& rhs) const noexcept {
    return operator value_type() <= rhs.operator value_type();
  }

  bool operator>=(const sum& rhs) const noexcept {
    return operator value_type() >= rhs.operator value_type();
  }

  // end: extra operators

  // windows.h illegially uses `#define small char` which breaks this now deprecated API
#if !defined(small)

  /// Return large part of the sum.
  [[deprecated("use large_part() instead; "
               "large() will be removed in boost-1.80")]] const_reference
  large() const noexcept {
    return large_;
  }

  /// Return small part of the sum.
  [[deprecated("use small_part() instead; "
               "small() will be removed in boost-1.80")]] const_reference
  small() const noexcept {
    return small_;
  }

#endif

private:
  value_type large_{};
  value_type small_{};
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
namespace std {
template <class T, class U>
struct common_type<boost::histogram::accumulators::sum<T>,
                   boost::histogram::accumulators::sum<U>> {
  using type = boost::histogram::accumulators::sum<common_type_t<T, U>>;
};
} // namespace std
#endif

#endif

/* sum.hpp
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
*/