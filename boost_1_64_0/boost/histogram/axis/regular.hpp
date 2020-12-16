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
3N3AiidCOpXTbEmN2JotadM3lFlTLGXhCpunqrksxRJ6rlGk13epL7fSk7O+PIV+s8Oj7PXlNrpVMtRICTLqB1vxhASDU0JNCGlsya4/x1Y/3l4/uAMCKCI1PDi9MZK9GIyCGl0/Po0E0kA3kcWCml2Zbr+XhrZ3FZMviw+8qCOJ16w/JTNBSyDFmkbS1M9qO3EoH3X/8XLp7CirlUEQREf4Ltbu/OanEv7HNXkoaSZzbcc4yIybdXcRM8dmcSZrObORuP8Ox9Cmyciy//KL7aT/uDbBHwSvl+SGPBtoskEnP8h1k+knwqXcKDqfJd0iny1tgPTjGPq1Hg1u/dBAi9yqeebQOJopnq7LrbpYkfysL/W4yONzhqSxNlNdM0OluvUrHhhaN1cdrogbCB2VQijiaKUGYr9F653VOBJOizdavYYCoNyA2+hsU+hzic+vU/uWtNZD5BmG0xabuBok5+kZZM4jR4PyVIoZ5YHr2CsDSeVekX6xVruT/npDKkmf7g3DEUnSwFxuStiTSYjouGF4egpVOQ0PNJyAasJr+PLMok242fTGxvoMHiRxQwSj47utGB89tgb/6sQg4SETN1IwTDA8MMs4g03k4B0bP/Xj0zlNR5Umg36z0b8oC4NpcCd/dx+W4Y/N0eYfAcJBsJmzS/tuOZR++AEEuYrdRClTmpOteiVMdoHxS+FKXgpLl4xnTtDWLJOMviZWDY3VTYuV86SecySNLEB3HslL4vNjHXQaoy6T3HyppbxcEhUsN5HvYt+IPqeqcSm8EoJi5L7dHcG91kA3tXDsZ5HLxtOwbOzP14vT0pIXt8HmbHGui91Dfj3JXEZOhS6Gk2BYTp4K5dGQXS4Py1fkveQmXkZSuhKZLku6W2wGkJwJ5jq3ByK94qzLY41MY09zw5g/2Zpaekf/lxxKK/4XkvwvpxX/y9Ffl3DvZj6InthaXRnHAQ8bAw44wZbIATP8zAH775gMrckkk9jmGkvV/u9Cae3eBNYIWmrHDdrK/mEp6itv0EpQFIv3vzsQt77A3Qa3njwneW6ty482UPnWfcufdMDyPx7dRvkfXN6e8vk+Dj7yBZUrXK/tvtI8st5ABnc2rEWtA1kWa3NVqpb6R0L2hJDZF0JpCgTNxo+dnZo7NeLN1vgxC6T2Bgfy709fH62X57NzqfVeXuhoHOiXLH7x7G8bTHwJFSFvAvE/nPO4TWmPB1wpd22gjCVNbLg0pTFqQ1PZl7IH+jjrQF8Wv5aJEXgNpmbJWJco4Vh48uf7BUKp/sO90rtNT0QAQ9aBkcPBPFhPnCmDkDuU6sjvsFx0dU5xdCGOVOYMpmZP/plU82Z/cSV5ofc7WcnMNvGLvkwPNXIuTBehIxIks/Bgu5TLGlKRt236zGX9P4RzWuQUYA/ALf5xPb0JsXkmUF7tIN1kY9SecEPIdyFGeqXPrhC97TbCrL1KIfoDvFpPgcUCMFtqCSzUeXOQ91vEsama+Q+BFZBoZItLxR2UeaB8qxQ3xL1NFHV4I2yUyYAC4ecAnXU6v1WprGPxhj0z6ylSdMz9GTqIxqa+fBoXv4v3zk80SvKIr2qkATLcgGcbW+RGeMDXW9x8hV4ANXl5J2g30NuQSj7c9PEesXq+vuPB7js6cpjYXC3FkkBv37HxsColLI9o4BbaWRdGEBrm2cVdcknSkNZuZbzavwuVpQfXY870gypcvKt1DNcrs427kj2ifJHZ3iJdx8tRx/vnm+31dROdVaWGO8XbU+gGkazw+Vm0SvGVqEyR3FFierUu8eFqvY7p5RsgU0xjsKPmq6b3qmGIBD/UnHQ7PeK6hWZ9J+n6zgHgXdWx/vF194icS00HXb4=
*/