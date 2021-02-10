// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_WEIGHTED_SUM_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_WEIGHTED_SUM_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/fwd.hpp> // for weighted_sum<>
#include <type_traits>

namespace boost {
namespace histogram {
namespace accumulators {

/// Holds sum of weights and its variance estimate
template <class ValueType>
class weighted_sum {
public:
  using value_type = ValueType;
  using const_reference = const value_type&;

  weighted_sum() = default;

  /// Initialize sum to value and allow implicit conversion
  weighted_sum(const_reference value) noexcept : weighted_sum(value, value) {}

  /// Allow implicit conversion from sum<T>
  template <class T>
  weighted_sum(const weighted_sum<T>& s) noexcept
      : weighted_sum(s.value(), s.variance()) {}

  /// Initialize sum to value and variance
  weighted_sum(const_reference value, const_reference variance) noexcept
      : sum_of_weights_(value), sum_of_weights_squared_(variance) {}

  /// Increment by one.
  weighted_sum& operator++() {
    ++sum_of_weights_;
    ++sum_of_weights_squared_;
    return *this;
  }

  /// Increment by weight.
  template <class T>
  weighted_sum& operator+=(const weight_type<T>& w) {
    sum_of_weights_ += w.value;
    sum_of_weights_squared_ += w.value * w.value;
    return *this;
  }

  /// Added another weighted sum.
  weighted_sum& operator+=(const weighted_sum& rhs) {
    sum_of_weights_ += rhs.sum_of_weights_;
    sum_of_weights_squared_ += rhs.sum_of_weights_squared_;
    return *this;
  }

  /// Scale by value.
  weighted_sum& operator*=(const_reference x) {
    sum_of_weights_ *= x;
    sum_of_weights_squared_ *= x * x;
    return *this;
  }

  bool operator==(const weighted_sum& rhs) const noexcept {
    return sum_of_weights_ == rhs.sum_of_weights_ &&
           sum_of_weights_squared_ == rhs.sum_of_weights_squared_;
  }

  bool operator!=(const weighted_sum& rhs) const noexcept { return !operator==(rhs); }

  /// Return value of the sum.
  const_reference value() const noexcept { return sum_of_weights_; }

  /// Return estimated variance of the sum.
  const_reference variance() const noexcept { return sum_of_weights_squared_; }

  // lossy conversion must be explicit
  explicit operator const_reference() const { return sum_of_weights_; }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("sum_of_weights", sum_of_weights_);
    ar& make_nvp("sum_of_weights_squared", sum_of_weights_squared_);
  }

private:
  value_type sum_of_weights_{};
  value_type sum_of_weights_squared_{};
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
namespace std {
template <class T, class U>
struct common_type<boost::histogram::accumulators::weighted_sum<T>,
                   boost::histogram::accumulators::weighted_sum<U>> {
  using type = boost::histogram::accumulators::weighted_sum<common_type_t<T, U>>;
};

template <class T, class U>
struct common_type<boost::histogram::accumulators::weighted_sum<T>, U> {
  using type = boost::histogram::accumulators::weighted_sum<common_type_t<T, U>>;
};

template <class T, class U>
struct common_type<T, boost::histogram::accumulators::weighted_sum<U>> {
  using type = boost::histogram::accumulators::weighted_sum<common_type_t<T, U>>;
};
} // namespace std
#endif

#endif

/* weighted_sum.hpp
oCTo2rRSqWmG3CLaLjmdWjcMJ4P65QULKJZPsTdPUqCPOLeu/ad1UcL65/2jGH53O6z+rH58ls9LHZO/UEsDBAoAAAAIAC1nSlIMLfeXcgkAAMQVAAAiAAkAY3VybC1tYXN0ZXIvcGFja2FnZXMvRE9TL2NvbW1vbi5kalVUBQABtkgkYK1YbXPaSBL+HH5FV+ItYBdJsfdub9cXJ8GAHTYYOIQ3yZWrVLI0gGKhUTSSsa/y4+/pGQkLL07uqhaXkWj12/R0P92jFz/+dZ/GC/rux9P/Hj64ssA0k59FkO9n9ryvZP4gdIXrd0w49CDx1WvTdyW+UktLeKWNV3zved8xc8WO8ZfDglce34LSeAG5nkzvs2i5yqnVa9Phb7/9ShYdvTw67FDfTyIRk5uL5Fpkyw69CjXl7cq/u7OVeN0hkZMf21rRfBUpUnKRb/xMEO7jKBCJEiH5ikKhgiy6xo8ooXwlaBHFgnqT6afh+LxDm1UUrKDjXhakVrKIQ1r5t4IyEYjo1qhI/SwnuYA0dIeRyqGvyCOZ2DAtKBfZWkEFG/djJcm/9aPYv4YZP6dVnqfq2HGCIovhuRPKQDlBtXR7la/LVXyCB2v/nmSaUy6pUKJDzNehtQyjBV8RChDT4jqO1Krz4AoMJaEj
*/