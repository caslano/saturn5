// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_COUNT_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_COUNT_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/detail/atomic_number.hpp>
#include <boost/histogram/fwd.hpp> // for count<>
#include <type_traits>             // for std::common_type

namespace boost {
namespace histogram {
namespace accumulators {

/**
  Wraps a C++ arithmetic type with optionally thread-safe increments and adds.

  This adaptor optionally uses atomic operations to make concurrent increments and
  additions thread-safe for the stored arithmetic value, which can be integral or
  floating point. For small histograms, the performance will still be poor because of
  False Sharing, see https://en.wikipedia.org/wiki/False_sharing for details.

  Warning: Assignment is not thread-safe in this implementation, so don't assign
  concurrently.

  This wrapper class can be used as a base class by users to add arbitrary metadata to
  each bin of a histogram.

  When weighted samples are accumulated and high precision is required, use
  `accumulators::sum` instead (at the cost of lower performance). If a local variance
  estimate for the weight distribution should be computed as well (generally needed for a
  detailed statistical analysis), use `accumulators::weighted_sum`.

  @tparam T C++ builtin arithmetic type (integer or floating point).
  @tparam ThreadSafe Set to true to make increments and adds thread-safe.
*/
template <class ValueType, bool ThreadSafe>
class count {
  using internal_type =
      std::conditional_t<ThreadSafe, detail::atomic_number<ValueType>, ValueType>;

public:
  using value_type = ValueType;
  using const_reference = const value_type&;

  count() noexcept = default;

  /// Initialize count to value and allow implicit conversion
  count(const_reference value) noexcept : value_{value} {}

  /// Allow implicit conversion from other count
  template <class T, bool B>
  count(const count<T, B>& c) noexcept : count{c.value()} {}

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
  value_type value() const noexcept { return value_; }

  // conversion to value_type must be explicit
  explicit operator value_type() const noexcept { return value_; }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    auto v = value();
    ar& make_nvp("value", v);
    value_ = v;
  }

  static constexpr bool thread_safe() noexcept { return ThreadSafe; }

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

  friend bool operator==(const_reference x, const count& rhs) noexcept {
    return x == rhs.value_;
  }

  friend bool operator!=(const_reference x, const count& rhs) noexcept {
    return x != rhs.value_;
  }

  friend bool operator<(const_reference x, const count& rhs) noexcept {
    return x < rhs.value_;
  }

  friend bool operator>(const_reference x, const count& rhs) noexcept {
    return x > rhs.value_;
  }

  friend bool operator<=(const_reference x, const count& rhs) noexcept {
    return x <= rhs.value_;
  }
  friend bool operator>=(const_reference x, const count& rhs) noexcept {
    return x >= rhs.value_;
  }

  // end: extra operators

private:
  internal_type value_{};
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
namespace std {
template <class T, class U, bool B1, bool B2>
struct common_type<boost::histogram::accumulators::count<T, B1>,
                   boost::histogram::accumulators::count<U, B2>> {
  using type = boost::histogram::accumulators::count<common_type_t<T, U>, (B1 || B2)>;
};
} // namespace std
#endif

#endif

/* count.hpp
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
*/