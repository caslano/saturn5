// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_REGULAR_HPP
#define BOOST_HISTOGRAM_AXIS_REGULAR_HPP

#include <boost/assert.hpp>
#include <boost/core/nvp.hpp>
#include <boost/histogram/axis/interval_view.hpp>
#include <boost/histogram/axis/iterator.hpp>
#include <boost/histogram/axis/metadata_base.hpp>
#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/detail/convert_integer.hpp>
#include <boost/histogram/detail/relaxed_equal.hpp>
#include <boost/histogram/detail/replace_type.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/throw_exception.hpp>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
using get_scale_type_helper = typename T::value_type;

template <class T>
using get_scale_type = mp11::mp_eval_or<T, detail::get_scale_type_helper, T>;

struct one_unit {};

template <class T>
T operator*(T&& t, const one_unit&) {
  return std::forward<T>(t);
}

template <class T>
T operator/(T&& t, const one_unit&) {
  return std::forward<T>(t);
}

template <class T>
using get_unit_type_helper = typename T::unit_type;

template <class T>
using get_unit_type = mp11::mp_eval_or<one_unit, detail::get_unit_type_helper, T>;

template <class T, class R = get_scale_type<T>>
R get_scale(const T& t) {
  return t / get_unit_type<T>();
}

} // namespace detail

namespace axis {

namespace transform {

/// Identity transform for equidistant bins.
struct id {
  /// Pass-through.
  template <class T>
  static T forward(T&& x) noexcept {
    return std::forward<T>(x);
  }

  /// Pass-through.
  template <class T>
  static T inverse(T&& x) noexcept {
    return std::forward<T>(x);
  }

  template <class Archive>
  void serialize(Archive&, unsigned /* version */) {}
};

/// Log transform for equidistant bins in log-space.
struct log {
  /// Returns log(x) of external value x.
  template <class T>
  static T forward(T x) {
    return std::log(x);
  }

  /// Returns exp(x) for internal value x.
  template <class T>
  static T inverse(T x) {
    return std::exp(x);
  }

  template <class Archive>
  void serialize(Archive&, unsigned /* version */) {}
};

/// Sqrt transform for equidistant bins in sqrt-space.
struct sqrt {
  /// Returns sqrt(x) of external value x.
  template <class T>
  static T forward(T x) {
    return std::sqrt(x);
  }

  /// Returns x^2 of internal value x.
  template <class T>
  static T inverse(T x) {
    return x * x;
  }

  template <class Archive>
  void serialize(Archive&, unsigned /* version */) {}
};

/// Pow transform for equidistant bins in pow-space.
struct pow {
  double power = 1; /**< power index */

  /// Make transform with index p.
  explicit pow(double p) : power(p) {}
  pow() = default;

  /// Returns pow(x, power) of external value x.
  template <class T>
  auto forward(T x) const {
    return std::pow(x, power);
  }

  /// Returns pow(x, 1/power) of external value x.
  template <class T>
  auto inverse(T x) const {
    return std::pow(x, 1.0 / power);
  }

  bool operator==(const pow& o) const noexcept { return power == o.power; }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("power", power);
  }
};

} // namespace transform

#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
// Type envelope to mark value as step size
template <class T>
struct step_type {
  T value;
};
#endif

/**
  Helper function to mark argument as step size.
 */
template <class T>
step_type<T> step(T t) {
  return step_type<T>{t};
}

/**
  Axis for equidistant intervals on the real line.

  The most common binning strategy. Very fast. Binning is a O(1) operation.

  @tparam Value input value type, must be floating point.
  @tparam Transform builtin or user-defined transform type.
  @tparam MetaData type to store meta data.
  @tparam Options see boost::histogram::axis::option (all values allowed).
 */
template <class Value, class Transform, class MetaData, class Options>
class regular : public iterator_mixin<regular<Value, Transform, MetaData, Options>>,
                protected detail::replace_default<Transform, transform::id>,
                public metadata_base<MetaData> {
  // these must be private, so that they are not automatically inherited
  using value_type = Value;
  using transform_type = detail::replace_default<Transform, transform::id>;
  using metadata_type = typename metadata_base<MetaData>::metadata_type;
  using options_type =
      detail::replace_default<Options, decltype(option::underflow | option::overflow)>;

  static_assert(std::is_nothrow_move_constructible<transform_type>::value,
                "transform must be no-throw move constructible");
  static_assert(std::is_nothrow_move_assignable<transform_type>::value,
                "transform must be no-throw move assignable");

  using unit_type = detail::get_unit_type<value_type>;
  using internal_value_type = detail::get_scale_type<value_type>;

  static_assert(std::is_floating_point<internal_value_type>::value,
                "regular axis requires floating point type");

  static_assert(
      (!options_type::test(option::circular) && !options_type::test(option::growth)) ||
          (options_type::test(option::circular) ^ options_type::test(option::growth)),
      "circular and growth options are mutually exclusive");

public:
  constexpr regular() = default;

  /** Construct n bins over real transformed range [start, stop).
   *
   * @param trans    transform instance to use.
   * @param n        number of bins.
   * @param start    low edge of first bin.
   * @param stop     high edge of last bin.
   * @param meta     description of the axis (optional).
   */
  regular(transform_type trans, unsigned n, value_type start, value_type stop,
          metadata_type meta = {})
      : transform_type(std::move(trans))
      , metadata_base<MetaData>(std::move(meta))
      , size_(static_cast<index_type>(n))
      , min_(this->forward(detail::get_scale(start)))
      , delta_(this->forward(detail::get_scale(stop)) - min_) {
    if (size() == 0) BOOST_THROW_EXCEPTION(std::invalid_argument("bins > 0 required"));
    if (!std::isfinite(min_) || !std::isfinite(delta_))
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("forward transform of start or stop invalid"));
    if (delta_ == 0)
      BOOST_THROW_EXCEPTION(std::invalid_argument("range of axis is zero"));
  }

  /** Construct n bins over real range [start, stop).
   *
   * @param n        number of bins.
   * @param start    low edge of first bin.
   * @param stop     high edge of last bin.
   * @param meta     description of the axis (optional).
   */
  regular(unsigned n, value_type start, value_type stop, metadata_type meta = {})
      : regular({}, n, start, stop, std::move(meta)) {}

  /** Construct bins with the given step size over real transformed range
   * [start, stop).
   *
   * @param trans   transform instance to use.
   * @param step    width of a single bin.
   * @param start   low edge of first bin.
   * @param stop    upper limit of high edge of last bin (see below).
   * @param meta    description of the axis (optional).
   *
   * The axis computes the number of bins as n = abs(stop - start) / step,
   * rounded down. This means that stop is an upper limit to the actual value
   * (start + n * step).
   */
  template <class T>
  regular(transform_type trans, step_type<T> step, value_type start, value_type stop,
          metadata_type meta = {})
      : regular(trans, static_cast<index_type>(std::abs(stop - start) / step.value),
                start,
                start + static_cast<index_type>(std::abs(stop - start) / step.value) *
                            step.value,
                std::move(meta)) {}

  /** Construct bins with the given step size over real range [start, stop).
   *
   * @param step    width of a single bin.
   * @param start   low edge of first bin.
   * @param stop    upper limit of high edge of last bin (see below).
   * @param meta    description of the axis (optional).
   *
   * The axis computes the number of bins as n = abs(stop - start) / step,
   * rounded down. This means that stop is an upper limit to the actual value
   * (start + n * step).
   */
  template <class T>
  regular(step_type<T> step, value_type start, value_type stop, metadata_type meta = {})
      : regular({}, step, start, stop, std::move(meta)) {}

  /// Constructor used by algorithm::reduce to shrink and rebin (not for users).
  regular(const regular& src, index_type begin, index_type end, unsigned merge)
      : regular(src.transform(), (end - begin) / merge, src.value(begin), src.value(end),
                src.metadata()) {
    BOOST_ASSERT((end - begin) % merge == 0);
    if (options_type::test(option::circular) && !(begin == 0 && end == src.size()))
      BOOST_THROW_EXCEPTION(std::invalid_argument("cannot shrink circular axis"));
  }

  /// Return instance of the transform type.
  const transform_type& transform() const noexcept { return *this; }

  /// Return index for value argument.
  index_type index(value_type x) const noexcept {
    // Runs in hot loop, please measure impact of changes
    auto z = (this->forward(x / unit_type{}) - min_) / delta_;
    if (options_type::test(option::circular)) {
      if (std::isfinite(z)) {
        z -= std::floor(z);
        return static_cast<index_type>(z * size());
      }
    } else {
      if (z < 1) {
        if (z >= 0)
          return static_cast<index_type>(z * size());
        else
          return -1;
      }
    }
    return size(); // also returned if x is NaN
  }

  /// Returns index and shift (if axis has grown) for the passed argument.
  std::pair<index_type, index_type> update(value_type x) noexcept {
    BOOST_ASSERT(options_type::test(option::growth));
    const auto z = (this->forward(x / unit_type{}) - min_) / delta_;
    if (z < 1) { // don't use i here!
      if (z >= 0) {
        const auto i = static_cast<axis::index_type>(z * size());
        return {i, 0};
      }
      if (z != -std::numeric_limits<internal_value_type>::infinity()) {
        const auto stop = min_ + delta_;
        const auto i = static_cast<axis::index_type>(std::floor(z * size()));
        min_ += i * (delta_ / size());
        delta_ = stop - min_;
        size_ -= i;
        return {0, -i};
      }
      // z is -infinity
      return {-1, 0};
    }
    // z either beyond range, infinite, or NaN
    if (z < std::numeric_limits<internal_value_type>::infinity()) {
      const auto i = static_cast<axis::index_type>(z * size());
      const auto n = i - size() + 1;
      delta_ /= size();
      delta_ *= size() + n;
      size_ += n;
      return {i, -n};
    }
    // z either infinite or NaN
    return {size(), 0};
  }

  /// Return value for fractional index argument.
  value_type value(real_index_type i) const noexcept {
    auto z = i / size();
    if (!options_type::test(option::circular) && z < 0.0)
      z = -std::numeric_limits<internal_value_type>::infinity() * delta_;
    else if (options_type::test(option::circular) || z <= 1.0)
      z = (1.0 - z) * min_ + z * (min_ + delta_);
    else {
      z = std::numeric_limits<internal_value_type>::infinity() * delta_;
    }
    return static_cast<value_type>(this->inverse(z) * unit_type());
  }

  /// Return bin for index argument.
  decltype(auto) bin(index_type idx) const noexcept {
    return interval_view<regular>(*this, idx);
  }

  /// Returns the number of bins, without over- or underflow.
  index_type size() const noexcept { return size_; }

  /// Returns the options.
  static constexpr unsigned options() noexcept { return options_type::value; }

  template <class V, class T, class M, class O>
  bool operator==(const regular<V, T, M, O>& o) const noexcept {
    return detail::relaxed_equal(transform(), o.transform()) && size() == o.size() &&
           min_ == o.min_ && delta_ == o.delta_ && metadata_base<MetaData>::operator==(o);
  }
  template <class V, class T, class M, class O>
  bool operator!=(const regular<V, T, M, O>& o) const noexcept {
    return !operator==(o);
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("transform", static_cast<transform_type&>(*this));
    ar& make_nvp("size", size_);
    ar& make_nvp("meta", this->metadata());
    ar& make_nvp("min", min_);
    ar& make_nvp("delta", delta_);
  }

private:
  index_type size_{0};
  internal_value_type min_{0}, delta_{1};

  template <class V, class T, class M, class O>
  friend class regular;
};

#if __cpp_deduction_guides >= 201606

template <class T>
regular(unsigned, T, T)
    ->regular<detail::convert_integer<T, double>, transform::id, null_type>;

template <class T, class M>
regular(unsigned, T, T, M)
    ->regular<detail::convert_integer<T, double>, transform::id,
              detail::replace_cstring<std::decay_t<M>>>;

template <class Tr, class T, class = detail::requires_transform<Tr, T>>
regular(Tr, unsigned, T, T)->regular<detail::convert_integer<T, double>, Tr, null_type>;

template <class Tr, class T, class M>
regular(Tr, unsigned, T, T, M)
    ->regular<detail::convert_integer<T, double>, Tr,
              detail::replace_cstring<std::decay_t<M>>>;

#endif

/// Regular axis with circular option already set.
template <class Value = double, class MetaData = use_default, class Options = use_default>
#ifndef BOOST_HISTOGRAM_DOXYGEN_INVOKED
using circular = regular<Value, transform::id, MetaData,
                         decltype(detail::replace_default<Options, option::overflow_t>{} |
                                  option::circular)>;
#else
class circular;
#endif

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* regular.hpp
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
*/