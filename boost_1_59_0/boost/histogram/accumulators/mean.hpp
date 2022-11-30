// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_MEAN_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_MEAN_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/detail/square.hpp>
#include <boost/histogram/fwd.hpp> // for mean<>
#include <boost/throw_exception.hpp>
#include <cassert>
#include <stdexcept>
#include <type_traits>

namespace boost {
namespace histogram {
namespace accumulators {

/** Calculates mean and variance of sample.

  Uses Welfords's incremental algorithm to improve the numerical
  stability of mean and variance computation.
*/
template <class ValueType>
class mean {
public:
  using value_type = ValueType;
  using const_reference = const value_type&;

  mean() = default;

  /// Allow implicit conversion from mean<T>.
  template <class T>
  mean(const mean<T>& o) noexcept
      : sum_{o.sum_}, mean_{o.mean_}, sum_of_deltas_squared_{o.sum_of_deltas_squared_} {}

  /// Initialize to external count, mean, and variance.
  mean(const_reference n, const_reference mean, const_reference variance) noexcept
      : sum_(n), mean_(mean), sum_of_deltas_squared_(variance * (n - 1)) {}

  /// Insert sample x.
  void operator()(const_reference x) noexcept {
    sum_ += static_cast<value_type>(1);
    const auto delta = x - mean_;
    mean_ += delta / sum_;
    sum_of_deltas_squared_ += delta * (x - mean_);
  }

  /// Insert sample x with weight w.
  void operator()(const weight_type<value_type>& w, const_reference x) noexcept {
    sum_ += w.value;
    const auto delta = x - mean_;
    mean_ += w.value * delta / sum_;
    sum_of_deltas_squared_ += w.value * delta * (x - mean_);
  }

  /// Add another mean accumulator.
  mean& operator+=(const mean& rhs) noexcept {
    if (rhs.sum_ == 0) return *this;

    /*
      sum_of_deltas_squared
        = sum_i (x_i - mu)^2
        = sum_i (x_i - mu)^2 + sum_k (x_k - mu)^2
        = sum_i (x_i - mu1 + (mu1 - mu))^2 + sum_k (x_k - mu2 + (mu2 - mu))^2

      first part:
      sum_i (x_i - mu1 + (mu1 - mu))^2
        = sum_i (x_i - mu1)^2 + n1 (mu1 - mu))^2 + 2 (mu1 - mu) sum_i (x_i - mu1)
        = sum_i (x_i - mu1)^2 + n1 (mu1 - mu))^2
      since sum_i (x_i - mu1) = n1 mu1 - n1 mu1 = 0

      Putting it together:
      sum_of_deltas_squared
        = sum_of_deltas_squared_1 + n1 (mu1 - mu))^2
        + sum_of_deltas_squared_2 + n2 (mu2 - mu))^2
    */

    const auto n1 = sum_;
    const auto mu1 = mean_;
    const auto n2 = rhs.sum_;
    const auto mu2 = rhs.mean_;

    sum_ += rhs.sum_;
    mean_ = (n1 * mu1 + n2 * mu2) / sum_;
    sum_of_deltas_squared_ += rhs.sum_of_deltas_squared_;
    sum_of_deltas_squared_ += n1 * detail::square(mean_ - mu1);
    sum_of_deltas_squared_ += n2 * detail::square(mean_ - mu2);

    return *this;
  }

  /** Scale by value.

   This acts as if all samples were scaled by the value.
  */
  mean& operator*=(const_reference s) noexcept {
    mean_ *= s;
    sum_of_deltas_squared_ *= s * s;
    return *this;
  }

  bool operator==(const mean& rhs) const noexcept {
    return sum_ == rhs.sum_ && mean_ == rhs.mean_ &&
           sum_of_deltas_squared_ == rhs.sum_of_deltas_squared_;
  }

  bool operator!=(const mean& rhs) const noexcept { return !operator==(rhs); }

  /** Return how many samples were accumulated.

    count() should be used to check whether value() and variance() are defined,
    see documentation of value() and variance(). count() can be used to compute
    the variance of the mean by dividing variance() by count().
  */
  const_reference count() const noexcept { return sum_; }

  /** Return mean value of accumulated samples.

    The result is undefined, if `count() < 1`.
  */
  const_reference value() const noexcept { return mean_; }

  /** Return variance of accumulated samples.

    The result is undefined, if `count() < 2`.
  */
  value_type variance() const noexcept { return sum_of_deltas_squared_ / (sum_ - 1); }

  template <class Archive>
  void serialize(Archive& ar, unsigned version) {
    if (version == 0) {
      // read only
      std::size_t sum;
      ar& make_nvp("sum", sum);
      sum_ = static_cast<value_type>(sum);
    } else {
      ar& make_nvp("sum", sum_);
    }
    ar& make_nvp("mean", mean_);
    ar& make_nvp("sum_of_deltas_squared", sum_of_deltas_squared_);
  }

private:
  value_type sum_{};
  value_type mean_{};
  value_type sum_of_deltas_squared_{};
};

} // namespace accumulators
} // namespace histogram
} // namespace boost

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED

namespace boost {
namespace serialization {

template <class T>
struct version;

// version 1 for boost::histogram::accumulators::mean<T>
template <class T>
struct version<boost::histogram::accumulators::mean<T>> : std::integral_constant<int, 1> {
};

} // namespace serialization
} // namespace boost

namespace std {
template <class T, class U>
/// Specialization for boost::histogram::accumulators::mean.
struct common_type<boost::histogram::accumulators::mean<T>,
                   boost::histogram::accumulators::mean<U>> {
  using type = boost::histogram::accumulators::mean<common_type_t<T, U>>;
};
} // namespace std

#endif

#endif

/* mean.hpp
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
*/