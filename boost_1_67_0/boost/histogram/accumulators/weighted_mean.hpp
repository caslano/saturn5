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
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
*/