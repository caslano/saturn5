// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_WEIGHTED_MEAN_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_WEIGHTED_MEAN_HPP

#include <boost/assert.hpp>
#include <boost/core/nvp.hpp>
#include <boost/histogram/fwd.hpp> // for weighted_mean<>
#include <boost/histogram/weight.hpp>
#include <type_traits>

namespace boost {
namespace histogram {
namespace accumulators {

/**
  Calculates mean and variance of weighted sample.

  Uses West's incremental algorithm to improve numerical stability
  of mean and variance computation.
*/
template <class ValueType>
class weighted_mean {
public:
  using value_type = ValueType;
  using const_reference = const value_type&;

  weighted_mean() = default;

  /// Allow implicit conversion from other weighted_means
  template <class T>
  weighted_mean(const weighted_mean<T>& o)
      : sum_of_weights_{o.sum_of_weights_}
      , sum_of_weights_squared_{o.sum_of_weights_squared_}
      , weighted_mean_{o.weighted_mean_}
      , sum_of_weighted_deltas_squared_{o.sum_of_weighted_deltas_squared_} {}

  /// Initialize to external sum of weights, sum of weights squared, mean, and variance
  weighted_mean(const_reference wsum, const_reference wsum2, const_reference mean,
                const_reference variance)
      : sum_of_weights_(wsum)
      , sum_of_weights_squared_(wsum2)
      , weighted_mean_(mean)
      , sum_of_weighted_deltas_squared_(
            variance * (sum_of_weights_ - sum_of_weights_squared_ / sum_of_weights_)) {}

  /// Insert sample x
  void operator()(const_reference x) { operator()(weight(1), x); }

  /// Insert sample x with weight w
  void operator()(const weight_type<value_type>& w, const_reference x) {
    sum_of_weights_ += w.value;
    sum_of_weights_squared_ += w.value * w.value;
    const auto delta = x - weighted_mean_;
    weighted_mean_ += w.value * delta / sum_of_weights_;
    sum_of_weighted_deltas_squared_ += w.value * delta * (x - weighted_mean_);
  }

  /// Add another weighted_mean
  weighted_mean& operator+=(const weighted_mean& rhs) {
    if (sum_of_weights_ != 0 || rhs.sum_of_weights_ != 0) {
      const auto tmp =
          weighted_mean_ * sum_of_weights_ + rhs.weighted_mean_ * rhs.sum_of_weights_;
      sum_of_weights_ += rhs.sum_of_weights_;
      sum_of_weights_squared_ += rhs.sum_of_weights_squared_;
      weighted_mean_ = tmp / sum_of_weights_;
    }
    sum_of_weighted_deltas_squared_ += rhs.sum_of_weighted_deltas_squared_;
    return *this;
  }

  /** Scale by value

   This acts as if all samples were scaled by the value.
  */
  weighted_mean& operator*=(const_reference s) {
    weighted_mean_ *= s;
    sum_of_weighted_deltas_squared_ *= s * s;
    return *this;
  }

  bool operator==(const weighted_mean& rhs) const noexcept {
    return sum_of_weights_ == rhs.sum_of_weights_ &&
           sum_of_weights_squared_ == rhs.sum_of_weights_squared_ &&
           weighted_mean_ == rhs.weighted_mean_ &&
           sum_of_weighted_deltas_squared_ == rhs.sum_of_weighted_deltas_squared_;
  }

  bool operator!=(const weighted_mean& rhs) const noexcept { return !operator==(rhs); }

  /// Return sum of weights
  const_reference sum_of_weights() const noexcept { return sum_of_weights_; }

  /// Return sum of weights squared (variance of weight distribution)
  const_reference sum_of_weights_squared() const noexcept {
    return sum_of_weights_squared_;
  }

  /// Return mean of accumulated weighted samples
  const_reference value() const noexcept { return weighted_mean_; }

  /// Return variance of accumulated weighted samples
  value_type variance() const {
    return sum_of_weighted_deltas_squared_ /
           (sum_of_weights_ - sum_of_weights_squared_ / sum_of_weights_);
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("sum_of_weights", sum_of_weights_);
    ar& make_nvp("sum_of_weights_squared", sum_of_weights_squared_);
    ar& make_nvp("weighted_mean", weighted_mean_);
    ar& make_nvp("sum_of_weighted_deltas_squared", sum_of_weighted_deltas_squared_);
  }

private:
  value_type sum_of_weights_{};
  value_type sum_of_weights_squared_{};
  value_type weighted_mean_{};
  value_type sum_of_weighted_deltas_squared_{};
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
namespace std {
template <class T, class U>
/// Specialization for boost::histogram::accumulators::weighted_mean.
struct common_type<boost::histogram::accumulators::weighted_mean<T>,
                   boost::histogram::accumulators::weighted_mean<U>> {
  using type = boost::histogram::accumulators::weighted_mean<common_type_t<T, U>>;
};
} // namespace std
#endif

#endif

/* weighted_mean.hpp
Y+tfMY0nD5KWq8t1dVADkGc6wLI/7XFQZVZesKEuuyZ5agn7JUccpi2MzbNZ4YyHHFWVZJMjLrwyMl3UCvukOopJiMwA6mTf9YGPzZWJDZZRU79SYyknb5pl4u9FPNS8jyqtltexeyuWN7IO07aFNvkhXfUjdHqqPGeQBesbSMgQQ6ZyseavutV5SCFnRt5+LtE8AtozH7kxcsa1P5LaB+pdVM4+FMrE4vM1TI80EcShOMskgDe9g/t5HnG/HCgsEqIw6lcLJEZ5xDokS4fXSlS6pqcjOI0ZQMStlnGfYdX973wkPZ89L44fsUfzI+ZYfmTdTR3wI/YO+ZGtU4kfwT/R/EjL/wI/4vZ4pZPlh/oTXfCIFpA0D4SuXflU79QaYmU3bE8jwm4krgNtZXMi/8VusX8AIyV63c0tlgw0TjowvHo7nwOLrsSTa2E36YnFM1OpLRLphtdbISVCWpnX6kHK/PkRI6e1ifNlUrn6DWOHLBPbr2y1SbEunF+BdFRp9bCbCMwtWb7OAjlEU/x8jChDW2VIzUVqrgtNXAdVkHqrUWM5hrpgMq8DrYHr+3xQJXkoA0VL0uqyrI7qh6VPFW2VEjhlcdxGd5LDGaEFkPpo8IH5Upbb7oNxBGRqLqe2yhloUlb0gCzV6odHZlxeUhCx8kjg1FmfCkyy+ocGTn3sW0ioVAS0Cpw653NtKkiYUJQAqempsG/qpgLLhCKLL4/RCpXayB0WKAV+WjE3ibqGjqV2+6KkdjujZa7IXKKAL2jUimgOn+fcv0Hut/XcW+Jy59uyimz4F/Ksw/i7GIObi78XvoCP5GfumItJlPZK3dEphuStOiRPMyRz9uFAon1QdzCF34GV5gazyz05h55IZTetEy3as/dNPXmKxOqBZy3ajpff5ZSck3kLoIR6o2Jhc3o4W2wdL4/QR5svCC9XxC8iQYu23EZlNx7EljdZgxZtYHLDIuZaFuncyysY8wB0Jwt/E05/tvGzbHyK0pjPfBh+BUpSutXHnr9IEptv40gpzyWQQLjvTw6vUoRrKXdZ/Y7BGENkiAXRge0jRJPR+qQomeTCBW1kklpdmxqaFsfJy7cWx4aHDI0NWxfEhrsvi5N/j4kKx+oLmAbyaUebruj2kp9Pe/Dl12+cCVxEmG7IAel5AJghBaMi40qEa1vDKRTe1RpWENZ/fo0ZhYzGLjxdNFUdjgf0x4l/oAuxa6bQmHzQIeUjBTuHvwKL+kptjlMb85EN4Y6JzZhWYjMsmtikRRMbh05sEiWxwabUCYF70/xw+PzzS9um1vWzwv2Lri98WcsQmqkLje2tn0oRePIIeKzmZvR3Yku5eQHvlbyE4iox9gOejbqsIrsfE2BQ+p5L7/w3gz/WvvlEEd4PYJ81HuFMl+cCfz/vALWFTqPdcB61iUenRtn4FqUEtncjc7YiO2y3+nmHck64eoT1Spm0JShmCQQywMxNK7LBlk3uIn28I2VmcRUrHJFO0Wl8L2esN1tPLJSJfLsl3SMCX8NWPlb2Zwr350IpKef+fBrD4fY/oH8q2+P0VR+x2J3ikXKe5wdVXrWs7w5MWsY5equ7KMfteg6KRM/fcHu9akkVumcXI0pbXQWNI0TkW8h2GGKoEfObVFjniOY8wxwgxbuCS7vFq2MjnoJQgGoXfzGy+ZpkFWIOCLmeWCzPfJ/KOKudj/qAxY6+Gyb1bH7xo5yONSOqSUF+JSb/jR3mN/TbO2dGn8/ttI8SIqYjoGyhkbH/Awx0KAmQwYPvSNeHvqaXSx97DyCYtl3aIYzWu+0dTgabavZGQh0xWmZIQYYerEqy45Dz7dny8RDYOXXBdgrEOkE/MDfIkMLgY3U=
*/