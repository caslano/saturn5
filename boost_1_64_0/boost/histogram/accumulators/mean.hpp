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
IWWlgY9t/uJQsc0VmdsRYZQKFiuItNQHx9ELeR/tsfKVbX6xIBfQCRXawNwZ2N5js8Rsj6yDysNHAhV8igvyNOeWezy0lKeJd1fwdhlVwS4tslwyInqQJ7UvZ71szWT/TzVR8GdaPZHoXKDJpmGI+gTks/MCewatlmy+fMwrpTlmpbyuOz21YLmE0vK1BEJvyz6tQCJ4AeiaAVvAxd0CHOcnIyy72K0xIeiH1bVYI2t4jdyJdZAVvwiGG4tgmLEIMnkZjeBlxFtKhlxGGbp396B1Bo2H1sdhuT54baBFWhJ4xoUa91cjwJwP1kcSrYlFwSuUhRSBCZiwiSYgk2ZlhL44hsqoL3xO2vrLW39rvL+8meRrxngDabHuEpp2lZU9cfoxHKVVB6V3svBNCp4WYd8PLm2KnX0/sL5uuSTnthP1Dp9F+iwcE7lcvpiXFvtRNJlZ5seoACjn0D/dWYS1kx4p2sZCrVk2gj7032wLgdlGZDgbtqJgdnbRGQD393XWhIBKqJWznbjoIK13VIZ6HFhrXBnKU/1cWzbwgt0pIsNsW5Av7VAD1BxRbBKgofOOKhv7+ELe0+g+TkuOh7BzmnOIRXzoPXNdeJDlRJ2AjcdthHGH2KfCuSBtBqgkWdAT5YSBQeqS7kEyoD/NsrwZfZb7A2XBre2qu1BJziFcFsnjrROdzjqaVUc5tHM0Iul/BhuF5aNCsGFw4LjJWsPKl5reec0r3uF0ghUVhWSCvsAdMsToDFVaSof+bCmLyI/cTJ9GR0lKX0iGqzm1xlzfd5uca61O+xA3Bsx15wbl7LaE65oG5ezaePA23eNxzkltHbr20BEyyZkGGKzDQyVNGFKJZuNH0mdqRwn+mGTMJ+DNc0Bz3EgQJ7bNWGLhcUCmYhv1DzHaMr1/6I08AaIWAGdUaC4A81HoFulvgm7jrjdvSqAHlIrDNVfwTdz3qFQG1X1neBzVlsuOB1BNHbUAdCUwaIACyz/lss5BFph8sx8lwoVChXArB1mlQBAJcyPkc92t/9tu+jr9MfTTwzUryGhG+BFXAj07V/Mt7ERjIw8cStNx/fHWcK+Jd/d3Lmo09UaQ3m87vzz3fXmEen+jQZKeDRaeLXPjVMou2qk9bSE/I1SIn7Jy+QKslkjODtgn5zF4JpH4YC2qqvWfyvrAUbUSCRvPneVt5Br8Vudaol7MCybSeXkL1RbexRecTE1HjVy0uy7aaTWx2PR408cmUxGLicq8JhUh1LIcAAgWtlTXrl8Y7jUXgUlXgoH2p8ls9I2CqLM1a7NF4/wjQ4pfIQ7O3yK82IVhWvY3AHihlIcsdTyt9F0aVK4gDwofNheHlELKLPKRE+W1F1ylVH3Yfzz4laOyboxjQHicnAuMR05IIre9q6kPQaf8KIqWhOwFjj9OORdoGe4bEmi5xJcaaFng67klBQxN0Lx0Syr+XYrneJutjebhVHjcnHCvzahfcwQ38iwkBrbiX7Q91dVBa7/APxGQJhBIf4Avl4E1d3JvHVU1PHk5J5aOXz4iNG+Ez7nxHO3IK21FSwMTV5r8Rwl+Ku0RXeaiYJErCvB3yxHDET85nbhTc2xSymqqelC+Arw1cURLbNhQZuEGuHDo6rfp5PCVszl/FQ3fBBDfWahjqIGg0Tke4hxfkmz8y/jEry84rFVMfqt84dI7SE2jU+/V3uu9DjF0JdGsFJSIW398pFlWGbP+sOR4CWo7gwtFqNS8yTyF1pXXlLWjsXC/jfUvoSlml8dr44kJFr4tsZFeolx/lTaA1kT45UmkD/EPxnwCbd5GSUIUT/QqkgVGISstIEf1EybCMAFu9/eMXLbQ1bsi09Nlo5weDX1Sxoo=
*/