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
quYHnLI+INPHimaFCTVe3tYrP+Uqrr3+r9TeRi7kqP1X42lLycNXve8GMlSgikbNXa9Yj9SsZiJV9J5SaR49vPvmJyW6S3TbGMdP5eFzA4g9XzI5WxPBQU8xTT/MkNT/++0ADBktGiEapjMVApMqD1ANJ5Ld73BIFelzL7d2wesApRzwoyZ6eObsL90Y4uCjl4hbIkchrUoUniAavsG6EdjBsLrtBhQJ++TK+z2+HVp5WvHRFXF6I2SUbL/EoFHr7I9IikOENW19p8eJKqJl0oBAqvGZ6ELvmyC44Q1BzI1cVwVVFR0uO2dREbyZio/0Hi1goMl/RUMcQ2uUgJ5SPvnCLqRxYHaFUmCzKrS6ji1/AroaPYOCjZLIdrgdlSy177BhYD/Ka5Qgm5824E0cI4WQFrKuBpBWgv//UssXYIt6YYLgeJnfLpLPqkcsyY4lbwK7lJqi7OHwGAyhtlDAatvDCEtAANOLN4c6gIiRhhHB+HD6BJTOI0GhRw7qvKAX3G0d5RGJ37wkzmZc+lMlFMCK7/QUrxb9JUOoRrjjvod8E288ivWkz5h7Mw==
*/