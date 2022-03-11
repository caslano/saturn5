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
  sum(const sum<T>& s) noexcept : sum(s.large(), s.small()) {}

  /// Initialize sum explicitly with large and small parts
  sum(const_reference large, const_reference small) noexcept
      : large_(large), small_(small) {}

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
    l -= large_;
    l += s;
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
  const_reference large() const noexcept { return large_; }

  /// Return small part of the sum.
  const_reference small() const noexcept { return small_; }

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