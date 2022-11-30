// Copyright 2018 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_WEIGHTED_MEAN_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_WEIGHTED_MEAN_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/detail/square.hpp>
#include <boost/histogram/fwd.hpp> // for weighted_mean<>
#include <boost/histogram/weight.hpp>
#include <cassert>
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

  /// Allow implicit conversion from other weighted_means.
  template <class T>
  weighted_mean(const weighted_mean<T>& o)
      : sum_of_weights_{o.sum_of_weights_}
      , sum_of_weights_squared_{o.sum_of_weights_squared_}
      , weighted_mean_{o.weighted_mean_}
      , sum_of_weighted_deltas_squared_{o.sum_of_weighted_deltas_squared_} {}

  /// Initialize to external sum of weights, sum of weights squared, mean, and variance.
  weighted_mean(const_reference wsum, const_reference wsum2, const_reference mean,
                const_reference variance)
      : sum_of_weights_(wsum)
      , sum_of_weights_squared_(wsum2)
      , weighted_mean_(mean)
      , sum_of_weighted_deltas_squared_(
            variance * (sum_of_weights_ - sum_of_weights_squared_ / sum_of_weights_)) {}

  /// Insert sample x.
  void operator()(const_reference x) { operator()(weight(1), x); }

  /// Insert sample x with weight w.
  void operator()(const weight_type<value_type>& w, const_reference x) {
    sum_of_weights_ += w.value;
    sum_of_weights_squared_ += w.value * w.value;
    const auto delta = x - weighted_mean_;
    weighted_mean_ += w.value * delta / sum_of_weights_;
    sum_of_weighted_deltas_squared_ += w.value * delta * (x - weighted_mean_);
  }

  /// Add another weighted_mean.
  weighted_mean& operator+=(const weighted_mean& rhs) {
    if (rhs.sum_of_weights_ == 0) return *this;

    // see mean.hpp for derivation of correct formula

    const auto n1 = sum_of_weights_;
    const auto mu1 = weighted_mean_;
    const auto n2 = rhs.sum_of_weights_;
    const auto mu2 = rhs.weighted_mean_;

    sum_of_weights_ += rhs.sum_of_weights_;
    sum_of_weights_squared_ += rhs.sum_of_weights_squared_;
    weighted_mean_ = (n1 * mu1 + n2 * mu2) / sum_of_weights_;

    sum_of_weighted_deltas_squared_ += rhs.sum_of_weighted_deltas_squared_;
    sum_of_weighted_deltas_squared_ += n1 * detail::square(weighted_mean_ - mu1);
    sum_of_weighted_deltas_squared_ += n2 * detail::square(weighted_mean_ - mu2);

    return *this;
  }

  /** Scale by value.

   This acts as if all samples were scaled by the value.
  */
  weighted_mean& operator*=(const_reference s) noexcept {
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

  /// Return sum of weights.
  const_reference sum_of_weights() const noexcept { return sum_of_weights_; }

  /// Return sum of weights squared (variance of weight distribution).
  const_reference sum_of_weights_squared() const noexcept {
    return sum_of_weights_squared_;
  }

  /** Return effective counts.

    This corresponds to the equivalent number of unweighted samples that would
    have the same variance as this sample. count() should be used to check whether
    value() and variance() are defined, see documentation of value() and variance().
    count() can be used to compute the variance of the mean by dividing variance()
    by count().
  */
  value_type count() const noexcept {
    // see https://en.wikipedia.org/wiki/Effective_sample_size#weighted_samples
    return detail::square(sum_of_weights_) / sum_of_weights_squared_;
  }

  /** Return mean value of accumulated weighted samples.

    The result is undefined, if count() == 0.
  */
  const_reference value() const noexcept { return weighted_mean_; }

  /** Return variance of accumulated weighted samples.

    The result is undefined, if count() == 0 or count() == 1.
  */
  value_type variance() const {
    // see https://en.wikipedia.org/wiki/Weighted_arithmetic_mean#Reliability_weights
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