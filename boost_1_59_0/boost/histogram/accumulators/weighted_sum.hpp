// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_WEIGHTED_SUM_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_WEIGHTED_SUM_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/detail/square.hpp>
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
  weighted_sum& operator+=(const weight_type<value_type>& w) {
    sum_of_weights_ += w.value;
    sum_of_weights_squared_ += detail::square(w.value);
    return *this;
  }

  /// Added another weighted sum.
  weighted_sum& operator+=(const weighted_sum& rhs) {
    sum_of_weights_ += rhs.sum_of_weights_;
    sum_of_weights_squared_ += rhs.sum_of_weights_squared_;
    return *this;
  }

  /// Divide by another weighted sum.
  weighted_sum& operator/=(const weighted_sum& rhs) {
    const auto v = sum_of_weights_;
    const auto w = sum_of_weights_squared_;
    const auto rv = rhs.sum_of_weights_;
    const auto rw = rhs.sum_of_weights_squared_;
    sum_of_weights_ /= rv;
    // error propagation for independent a, b:
    // c = a / b: var(c) = (var(a)/a^2 + var(b)/b^2) c^2
    using detail::square;
    sum_of_weights_squared_ = (w / square(v) + rw / square(rv)) * square(sum_of_weights_);
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
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
*/