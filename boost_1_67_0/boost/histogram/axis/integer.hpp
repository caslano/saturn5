// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_INTEGER_HPP
#define BOOST_HISTOGRAM_AXIS_INTEGER_HPP

#include <boost/core/nvp.hpp>
#include <boost/histogram/axis/iterator.hpp>
#include <boost/histogram/axis/metadata_base.hpp>
#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/detail/convert_integer.hpp>
#include <boost/histogram/detail/limits.hpp>
#include <boost/histogram/detail/replace_type.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/throw_exception.hpp>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace boost {
namespace histogram {
namespace axis {

/**
  Axis for an interval of integer values with unit steps.

  Binning is a O(1) operation. This axis bins faster than a regular axis.

  @tparam Value input value type. Must be integer or floating point.
  @tparam MetaData type to store meta data.
  @tparam Options see boost::histogram::axis::option (all values allowed).
 */
template <class Value, class MetaData, class Options>
class integer : public iterator_mixin<integer<Value, MetaData, Options>>,
                public metadata_base<MetaData> {
  // these must be private, so that they are not automatically inherited
  using value_type = Value;
  using metadata_type = typename metadata_base<MetaData>::metadata_type;
  using options_type =
      detail::replace_default<Options, decltype(option::underflow | option::overflow)>;

  static_assert(std::is_integral<value_type>::value ||
                    std::is_floating_point<value_type>::value,
                "integer axis requires floating point or integral type");

  static_assert(!options_type::test(option::circular | option::growth) ||
                    (options_type::test(option::circular) ^
                     options_type::test(option::growth)),
                "circular and growth options are mutually exclusive");

  static_assert(std::is_floating_point<value_type>::value ||
                    (!options_type::test(option::circular) &&
                     !options_type::test(option::growth)) ||
                    (!options_type::test(option::overflow) &&
                     !options_type::test(option::underflow)),
                "circular or growing integer axis with integral type "
                "cannot have entries in underflow or overflow bins");

  using local_index_type = std::conditional_t<std::is_integral<value_type>::value,
                                              index_type, real_index_type>;

public:
  constexpr integer() = default;

  /** Construct over semi-open integer interval [start, stop).
   *
   * \param start    first integer of covered range.
   * \param stop     one past last integer of covered range.
   * \param meta     description of the axis.
   */
  integer(value_type start, value_type stop, metadata_type meta = {})
      : metadata_base<MetaData>(std::move(meta))
      , size_(static_cast<index_type>(stop - start))
      , min_(start) {
    if (!(stop >= start))
      BOOST_THROW_EXCEPTION(std::invalid_argument("stop >= start required"));
  }

  /// Constructor used by algorithm::reduce to shrink and rebin.
  integer(const integer& src, index_type begin, index_type end, unsigned merge)
      : integer(src.value(begin), src.value(end), src.metadata()) {
    if (merge > 1)
      BOOST_THROW_EXCEPTION(std::invalid_argument("cannot merge bins for integer axis"));
    if (options_type::test(option::circular) && !(begin == 0 && end == src.size()))
      BOOST_THROW_EXCEPTION(std::invalid_argument("cannot shrink circular axis"));
  }

  /// Return index for value argument.
  index_type index(value_type x) const noexcept {
    return detail::static_if<std::is_floating_point<value_type>>(
        [this](const auto z) -> index_type {
          // need to handle NaN, cannot simply cast to int and call int-implementation
          if (options_type::test(option::circular)) {
            if (std::isfinite(z))
              return static_cast<index_type>(std::floor(z) -
                                             std::floor(z / this->size()) * this->size());
          } else if (z < this->size())
            return z >= 0 ? static_cast<index_type>(z) : -1;
          return this->size();
        },
        [this](const auto z) -> index_type {
          if (options_type::test(option::circular))
            return static_cast<index_type>(z - std::floor(float(z) / this->size()) *
                                                   this->size());
          if (z < this->size()) return z >= 0 ? z : -1;
          return this->size();
        },
        x - min_);
  }

  /// Returns index and shift (if axis has grown) for the passed argument.
  auto update(value_type x) noexcept {
    auto impl = [this](long x) -> std::pair<index_type, index_type> {
      const auto i = x - min_;
      if (i >= 0) {
        const auto k = static_cast<axis::index_type>(i);
        if (k < size()) return {k, 0};
        const auto n = k - size() + 1;
        size_ += n;
        return {k, -n};
      }
      const auto k = static_cast<axis::index_type>(
          detail::static_if<std::is_floating_point<value_type>>(
              [](auto x) { return std::floor(x); }, [](auto x) { return x; }, i));
      min_ += k;
      size_ -= k;
      return {0, -k};
    };

    return detail::static_if<std::is_floating_point<value_type>>(
        [this, impl](auto x) -> std::pair<index_type, index_type> {
          if (std::isfinite(x)) return impl(static_cast<long>(std::floor(x)));
          return {x < 0 ? -1 : this->size(), 0};
        },
        impl, x);
  }

  /// Return value for index argument.
  value_type value(local_index_type i) const noexcept {
    if (!options_type::test(option::circular) &&
        std::is_floating_point<value_type>::value) {
      if (i < 0) return detail::lowest<value_type>();
      if (i > size()) return detail::highest<value_type>();
    }
    return min_ + i;
  }

  /// Return bin for index argument.
  decltype(auto) bin(index_type idx) const noexcept {
    return detail::static_if<std::is_floating_point<value_type>>(
        [this](auto idx) { return interval_view<integer>(*this, idx); },
        [this](auto idx) { return this->value(idx); }, idx);
  }

  /// Returns the number of bins, without over- or underflow.
  index_type size() const noexcept { return size_; }

  /// Returns the options.
  static constexpr unsigned options() noexcept { return options_type::value; }

  /// Whether the axis is inclusive (see axis::traits::is_inclusive).
  static constexpr bool inclusive() noexcept {
    return (options() & option::underflow || options() & option::overflow) ||
           (std::is_integral<value_type>::value &&
            (options() & (option::growth | option::circular)));
  }

  template <class V, class M, class O>
  bool operator==(const integer<V, M, O>& o) const noexcept {
    return size() == o.size() && min_ == o.min_ && metadata_base<MetaData>::operator==(o);
  }

  template <class V, class M, class O>
  bool operator!=(const integer<V, M, O>& o) const noexcept {
    return !operator==(o);
  }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("size", size_);
    ar& make_nvp("meta", this->metadata());
    ar& make_nvp("min", min_);
  }

private:
  index_type size_{0};
  value_type min_{0};

  template <class V, class M, class O>
  friend class integer;
};

#if __cpp_deduction_guides >= 201606

template <class T>
integer(T, T)->integer<detail::convert_integer<T, index_type>, null_type>;

template <class T, class M>
integer(T, T, M)
    ->integer<detail::convert_integer<T, index_type>,
              detail::replace_type<std::decay_t<M>, const char*, std::string>>;

#endif

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* integer.hpp
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
*/