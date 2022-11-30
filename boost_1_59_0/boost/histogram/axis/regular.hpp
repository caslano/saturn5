// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_REGULAR_HPP
#define BOOST_HISTOGRAM_AXIS_REGULAR_HPP

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
#include <cassert>
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

/** Axis for equidistant intervals on the real line.

   The most common binning strategy. Very fast. Binning is a O(1) operation.

   If the axis has an overflow bin (the default), a value on the upper edge of the last
   bin is put in the overflow bin. The axis range represents a semi-open interval.

   If the overflow bin is deactivated, then a value on the upper edge of the last bin is
   still counted towards the last bin. The axis range represents a closed interval. This
   is the desired behavior for random numbers drawn from a bounded interval, which is
   usually closed.

   @tparam Value input value type, must be floating point.
   @tparam Transform builtin or user-defined transform type.
   @tparam MetaData type to store meta data.
   @tparam Options see boost::histogram::axis::option.
 */
template <class Value, class Transform, class MetaData, class Options>
class regular : public iterator_mixin<regular<Value, Transform, MetaData, Options>>,
                protected detail::replace_default<Transform, transform::id>,
                public metadata_base_t<MetaData> {
  // these must be private, so that they are not automatically inherited
  using value_type = Value;
  using transform_type = detail::replace_default<Transform, transform::id>;
  using metadata_base = metadata_base_t<MetaData>;
  using metadata_type = typename metadata_base::metadata_type;
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

     @param trans    transform instance to use.
     @param n        number of bins.
     @param start    low edge of first bin.
     @param stop     high edge of last bin.
     @param meta     description of the axis (optional).
     @param options  see boost::histogram::axis::option (optional).
   */
  regular(transform_type trans, unsigned n, value_type start, value_type stop,
          metadata_type meta = {}, options_type options = {})
      : transform_type(std::move(trans))
      , metadata_base(std::move(meta))
      , size_(static_cast<index_type>(n))
      , min_(this->forward(detail::get_scale(start)))
      , delta_(this->forward(detail::get_scale(stop)) - min_) {
    (void)options;
    if (size() == 0) BOOST_THROW_EXCEPTION(std::invalid_argument("bins > 0 required"));
    if (!std::isfinite(min_) || !std::isfinite(delta_))
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("forward transform of start or stop invalid"));
    if (delta_ == 0)
      BOOST_THROW_EXCEPTION(std::invalid_argument("range of axis is zero"));
  }

  /** Construct n bins over real range [start, stop).

     @param n        number of bins.
     @param start    low edge of first bin.
     @param stop     high edge of last bin.
     @param meta     description of the axis (optional).
     @param options  see boost::histogram::axis::option (optional).
   */
  regular(unsigned n, value_type start, value_type stop, metadata_type meta = {},
          options_type options = {})
      : regular({}, n, start, stop, std::move(meta), options) {}

  /** Construct bins with the given step size over real transformed range
     [start, stop).

     @param trans    transform instance to use.
     @param step     width of a single bin.
     @param start    low edge of first bin.
     @param stop     upper limit of high edge of last bin (see below).
     @param meta     description of the axis (optional).
     @param options  see boost::histogram::axis::option (optional).

     The axis computes the number of bins as n = abs(stop - start) / step,
     rounded down. This means that stop is an upper limit to the actual value
     (start + n * step).
   */
  template <class T>
  regular(transform_type trans, step_type<T> step, value_type start, value_type stop,
          metadata_type meta = {}, options_type options = {})
      : regular(trans, static_cast<index_type>(std::abs(stop - start) / step.value),
                start,
                start + static_cast<index_type>(std::abs(stop - start) / step.value) *
                            step.value,
                std::move(meta), options) {}

  /** Construct bins with the given step size over real range [start, stop).

     @param step     width of a single bin.
     @param start    low edge of first bin.
     @param stop     upper limit of high edge of last bin (see below).
     @param meta     description of the axis (optional).
     @param options  see boost::histogram::axis::option (optional).

     The axis computes the number of bins as n = abs(stop - start) / step,
     rounded down. This means that stop is an upper limit to the actual value
     (start + n * step).
   */
  template <class T>
  regular(step_type<T> step, value_type start, value_type stop, metadata_type meta = {},
          options_type options = {})
      : regular({}, step, start, stop, std::move(meta), options) {}

  /// Constructor used by algorithm::reduce to shrink and rebin (not for users).
  regular(const regular& src, index_type begin, index_type end, unsigned merge)
      : regular(src.transform(), (end - begin) / merge, src.value(begin), src.value(end),
                src.metadata()) {
    assert((end - begin) % merge == 0);
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
      // upper edge of last bin is inclusive if overflow bin is not present
      if (!options_type::test(option::overflow) && z == 1) return size() - 1;
    }
    return size(); // also returned if x is NaN
  }

  /// Returns index and shift (if axis has grown) for the passed argument.
  std::pair<index_type, index_type> update(value_type x) noexcept {
    assert(options_type::test(option::growth));
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
    return detail::relaxed_equal{}(transform(), o.transform()) && size() == o.size() &&
           min_ == o.min_ && delta_ == o.delta_ &&
           detail::relaxed_equal{}(this->metadata(), o.metadata());
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
    -> regular<detail::convert_integer<T, double>, transform::id, null_type>;

template <class T, class M>
regular(unsigned, T, T, M) -> regular<detail::convert_integer<T, double>, transform::id,
                                      detail::replace_cstring<std::decay_t<M>>>;

template <class T, class M, unsigned B>
regular(unsigned, T, T, M, const option::bitset<B>&)
    -> regular<detail::convert_integer<T, double>, transform::id,
               detail::replace_cstring<std::decay_t<M>>, option::bitset<B>>;

template <class Tr, class T, class = detail::requires_transform<Tr, T>>
regular(Tr, unsigned, T, T) -> regular<detail::convert_integer<T, double>, Tr, null_type>;

template <class Tr, class T, class M>
regular(Tr, unsigned, T, T, M) -> regular<detail::convert_integer<T, double>, Tr,
                                          detail::replace_cstring<std::decay_t<M>>>;

template <class Tr, class T, class M, unsigned B>
regular(Tr, unsigned, T, T, M, const option::bitset<B>&)
    -> regular<detail::convert_integer<T, double>, Tr,
               detail::replace_cstring<std::decay_t<M>>, option::bitset<B>>;

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