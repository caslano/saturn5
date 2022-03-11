// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_NUMBER_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_NUMBER_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/fwd.hpp> // for count<>
#include <type_traits>             // for std::common_type

namespace boost {
namespace histogram {
namespace accumulators {

/**
  Uses a C++ builtin arithmetic type to accumulate a count.

  This wrapper class may be used as a base class by users who want to add custom metadata
  to each bin of a histogram. Otherwise, arithmetic types should be used directly as
  accumulators in storages for simplicity. In other words, prefer `dense_storage<double>`
  over `dense_storage<count<double>>`, both are functionally equivalent.

  When weighted data is accumulated and high precision is required, use
  `accumulators::sum` instead. If a local variance estimate for the weight distribution
  should be computed as well (generally needed for a detailed statistical analysis), use
  `accumulators::weighted_sum`.
*/
template <class ValueType>
class count {
public:
  using value_type = ValueType;
  using const_reference = const value_type&;

  count() = default;

  /// Initialize count to value and allow implicit conversion
  count(const_reference value) noexcept : value_(value) {}

  /// Allow implicit conversion from other count
  template <class T>
  count(const count<T>& c) noexcept : count(c.value()) {}

  /// Increment count by one
  count& operator++() noexcept {
    ++value_;
    return *this;
  }

  /// Increment count by value
  count& operator+=(const_reference value) noexcept {
    value_ += value;
    return *this;
  }

  /// Add another count
  count& operator+=(const count& s) noexcept {
    value_ += s.value_;
    return *this;
  }

  /// Scale by value
  count& operator*=(const_reference value) noexcept {
    value_ *= value;
    return *this;
  }

  bool operator==(const count& rhs) const noexcept { return value_ == rhs.value_; }

  bool operator!=(const count& rhs) const noexcept { return !operator==(rhs); }

  /// Return count
  const_reference value() const noexcept { return value_; }

  // conversion to value_type must be explicit
  explicit operator value_type() const noexcept { return value_; }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("value", value_);
  }

  // begin: extra operators to make count behave like a regular number

  count& operator*=(const count& rhs) noexcept {
    value_ *= rhs.value_;
    return *this;
  }

  count operator*(const count& rhs) const noexcept {
    count x = *this;
    x *= rhs;
    return x;
  }

  count& operator/=(const count& rhs) noexcept {
    value_ /= rhs.value_;
    return *this;
  }

  count operator/(const count& rhs) const noexcept {
    count x = *this;
    x /= rhs;
    return x;
  }

  bool operator<(const count& rhs) const noexcept { return value_ < rhs.value_; }

  bool operator>(const count& rhs) const noexcept { return value_ > rhs.value_; }

  bool operator<=(const count& rhs) const noexcept { return value_ <= rhs.value_; }

  bool operator>=(const count& rhs) const noexcept { return value_ >= rhs.value_; }

  // end: extra operators

private:
  value_type value_{};
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
namespace std {
template <class T, class U>
struct common_type<boost::histogram::accumulators::count<T>,
                   boost::histogram::accumulators::count<U>> {
  using type = boost::histogram::accumulators::count<common_type_t<T, U>>;
};
} // namespace std
#endif

#endif

/* count.hpp
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
*/