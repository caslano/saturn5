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
#include <boost/histogram/detail/relaxed_equal.hpp>
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

/** Axis for an interval of integer values with unit steps.

   Binning is a O(1) operation. This axis bins faster than a regular axis.

   @tparam Value     input value type. Must be integer or floating point.
   @tparam MetaData  type to store meta data.
   @tparam Options   see boost::histogram::axis::option.
 */
template <class Value, class MetaData, class Options>
class integer : public iterator_mixin<integer<Value, MetaData, Options>>,
                public metadata_base_t<MetaData> {
  // these must be private, so that they are not automatically inherited
  using value_type = Value;
  using metadata_base = metadata_base_t<MetaData>;
  using metadata_type = typename metadata_base::metadata_type;
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

     @param start    first integer of covered range.
     @param stop     one past last integer of covered range.
     @param meta     description of the axis (optional).
     @param options  see boost::histogram::axis::option (optional).
   */
  integer(value_type start, value_type stop, metadata_type meta = {},
          options_type options = {})
      : metadata_base(std::move(meta))
      , size_(static_cast<index_type>(stop - start))
      , min_(start) {
    (void)options;
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
    return index_impl(options_type::test(axis::option::circular),
                      std::is_floating_point<value_type>{},
                      static_cast<double>(x - min_));
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
    // If axis has underflow and overflow, it is inclusive.
    // If axis is growing or circular:
    // - it is inclusive if value_type is int.
    // - it is not inclusive if value_type is float, because of nan and inf.
    constexpr bool full_flow =
        options() & option::underflow && options() & option::overflow;
    return full_flow || (std::is_integral<value_type>::value &&
                         (options() & (option::growth | option::circular)));
  }

  template <class V, class M, class O>
  bool operator==(const integer<V, M, O>& o) const noexcept {
    return size() == o.size() && min_ == o.min_ &&
           detail::relaxed_equal{}(this->metadata(), o.metadata());
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
  // axis not circular
  template <class B>
  index_type index_impl(std::false_type, B, double z) const noexcept {
    if (z < size()) return z >= 0 ? static_cast<index_type>(z) : -1;
    return size();
  }

  // value_type is integer, axis circular
  index_type index_impl(std::true_type, std::false_type, double z) const noexcept {
    return static_cast<index_type>(z - std::floor(z / size()) * size());
  }

  // value_type is floating point, must handle +/-infinite or nan, axis circular
  index_type index_impl(std::true_type, std::true_type, double z) const noexcept {
    if (std::isfinite(z)) return index_impl(std::true_type{}, std::false_type{}, z);
    return z < size() ? -1 : size();
  }

  index_type size_{0};
  value_type min_{0};

  template <class V, class M, class O>
  friend class integer;
};

#if __cpp_deduction_guides >= 201606

template <class T>
integer(T, T) -> integer<detail::convert_integer<T, index_type>, null_type>;

template <class T, class M>
integer(T, T, M)
    -> integer<detail::convert_integer<T, index_type>,
               detail::replace_type<std::decay_t<M>, const char*, std::string>>;

template <class T, class M, unsigned B>
integer(T, T, M, const option::bitset<B>&)
    -> integer<detail::convert_integer<T, index_type>,
               detail::replace_type<std::decay_t<M>, const char*, std::string>,
               option::bitset<B>>;

#endif

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* integer.hpp
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
*/