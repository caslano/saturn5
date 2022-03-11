// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ACCUMULATORS_MEAN_HPP
#define BOOST_HISTOGRAM_ACCUMULATORS_MEAN_HPP

#include <boost/assert.hpp>
#include <boost/core/nvp.hpp>
#include <boost/histogram/fwd.hpp> // for mean<>
#include <boost/throw_exception.hpp>
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

  /// Allow implicit conversion from mean<T>
  template <class T>
  mean(const mean<T>& o) noexcept
      : sum_{o.sum_}, mean_{o.mean_}, sum_of_deltas_squared_{o.sum_of_deltas_squared_} {}

  /// Initialize to external count, mean, and variance
  mean(const_reference n, const_reference mean, const_reference variance) noexcept
      : sum_(n), mean_(mean), sum_of_deltas_squared_(variance * (n - 1)) {}

  /// Insert sample x
  void operator()(const_reference x) noexcept {
    sum_ += static_cast<value_type>(1);
    const auto delta = x - mean_;
    mean_ += delta / sum_;
    sum_of_deltas_squared_ += delta * (x - mean_);
  }

  /// Insert sample x with weight w
  void operator()(const weight_type<value_type>& w, const_reference x) noexcept {
    sum_ += w.value;
    const auto delta = x - mean_;
    mean_ += w.value * delta / sum_;
    sum_of_deltas_squared_ += w.value * delta * (x - mean_);
  }

  /// Add another mean accumulator
  mean& operator+=(const mean& rhs) noexcept {
    if (sum_ != 0 || rhs.sum_ != 0) {
      const auto tmp = mean_ * sum_ + rhs.mean_ * rhs.sum_;
      sum_ += rhs.sum_;
      mean_ = tmp / sum_;
    }
    sum_of_deltas_squared_ += rhs.sum_of_deltas_squared_;
    return *this;
  }

  /** Scale by value

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

  /// Return how many samples were accumulated
  const_reference count() const noexcept { return sum_; }

  /// Return mean value of accumulated samples
  const_reference value() const noexcept { return mean_; }

  /// Return variance of accumulated samples
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