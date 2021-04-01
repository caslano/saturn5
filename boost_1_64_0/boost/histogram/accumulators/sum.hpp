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
4988sFl5xZz+5ngX0/Ckn92ioqFS/pSOhj2diWJvDu+wVCYd55E861WknLFuKxgIh9W+PYNsdpIJrr4tLhnmsgKiizpVlEZ62CPE0pg/8Fg+TAJ8lCoFFizVhLm+IcNWSF0RwyG+z5Dn7MMb3kI/csjRk7otee4RhDF5AguC+Q7EPS5/jc83nSlbBXPVfI9/BANZrEMpjSq8/E/SGsXhjuQRIWOcJUpgfOu9VCXEpGtGoNByFlx6IQOqlrjRuJ74zopP1A7EmzCwudV7oR5i3BtTnW4xoSLWPqdvXxdCu+iEzHPl32ZvzPZR1fMZX0mLj7+3ZX64cKpc7u1dOuFc2CtfPokWps0Go24Hvcal3m3xudidMp4pFtBkZEXeRKou6nEv2YiIU4Gt6VbrR5/oJAwhPlGLme5y7BAQXO9Y8CiqPOZRWI/fHYmJCJqF8jQMeOMPmrnlWDo6313m+wwWdcKfM9VVMO6eOf0+EiKPElj5RtMt2lbzGcHZJJYN2Ahmb/8Aomy/NRz+9NZQc095I9RKjQ8G8zg7BJTcSTDMtlb6wRdQJfzv4sa6cg==
*/