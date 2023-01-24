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
5WfUowrZrS4AKq+trq6Vk7jNRO5WoDbwmJJ2wPy4kLZlJaxh9ksI5FZozTDn5OkJrRPyGVxB4xfWqAaFG4wC/gD3zBMsjYAG/jNUJ2CZ6o/GjOQvDaY8VFPQjmaRcWHqKa+u74ouWJEoTqznnJkG4AXknSnvdc3R55ZuiTvbPXp13Ow4gCO0XrsUzMSPSmAMz9IyYQKZpyIRJa5Z3AT2rsPtikbfPygG8d3wNbjfDfv6dOxCnmsPR4+vvxty7KMr9sk9uxkxdCmjJfoqFtFFmibp+CaLgmV55ELM0DeKELVL8jBftfUSzGq0fh7hWTbd1f4ZG1lTjsSKU92/2FAas2Q3TXfC7jplzf5GoCmsB5jfv1ot4Hh9dKjQKnC9oGxr73gzNjbJKmDgfXepu3Q7V17JKrT30bVo8zrehHY1ckQFM7cs81Qf99vTzFXn7feODRpMWE5Z74t6nqsjaHKXjexG7lLcAXT3nkedalO4DPUfA3WBb3b2PsmCC+n4dp7xYAwSdNvPCfgFL7KsBLbTU0ZfVj+IpGqAKqJPj7sQ+RdAjRuiQwbgif6DYohFPxXBTFKBZjH/sYqT8vHA5jctpm2j2LwD7hUu3JMp16HxKa9820RPcZaZ89yzvJlR2T05mycJJen7WiNVXR8tEpe4Gdcnf64DLddWLctqL90KyWjzUl1/VlzVE9DOD+4/14AfLUMzLcT1+awhhY6f
*/