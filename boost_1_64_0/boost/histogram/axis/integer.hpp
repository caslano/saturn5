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
WZzCb5H6+gOnz/4N0o/PQ/qhSaUvoPTXjkX6rMT0+2n/s63bv+It1X77ftvf5fBvf1r7nxlI7Y/uSKI9T1P6mlxqf1LpV1H6D/pT+5NKz/WZWYX0n+7dcXB8dXumNb4efkfia2fKfvG14qNDp5ePqH5zB1H79ybdnuB4an9S6e+n9L5yav+eZNL7Kf2vKf2qPUngq97+bSt8TVH01WzdL76W/PnQ8RUbX59sS6Y9sfH1eFLpY+Prqm3JtN/Wuv3Fb6j2W/bb/pWdf47x9ckXybQnNr4eTyp9bHxdlVT62Pga/UUS+Bqb0hpflZslvm6K7tgfvorfP3R6iY2vxyNJt4fH11VJpY+Nr9FJpY+Nr15tpfdZ9B/pauhruIgiMwuQowtTZF7TgdNPpfSzeiH9x1/sk55S7O9r2CnnznzkvK91zv2XJzHmPhy5Zn+RTP14RJ5F6cuTSs8jcjq3v53tKaWcR5+KnO9E2tmeAYSFOyLJ1I9HWM/x1P6k0vMI+9ZL7U8qPddnfim1P9K+9r9EOQu81P7Pk28/j5gFJ1L7P0+6frurqP1Jpb+f259L7U8qPY+Yq3pS+5NKv0ynx2ZOMulj42ttYzLpY+Mr1Ni+/oiNr1GNyfdHbHz1SKp+sfEVWZ9M+tj4Wru+fe2Jja/F69vZHh5f5yZVv9j46pFU+tj4iqxLJn1sfK1d1772x8bX4nXJtz82vs5Nvn48vnoklT42viLPJpM+Nr7WJpU+Nr5CrdO3um8Bs/uoF+Xsvua7/c7uc/+U9Oy+L/zmjRL+2P3DH9IhaWlrX/iPqPrv2rlf+Ddtbkf9o6enH09XHWCZof2NUYBLHI+9aqPsBPY31h3P+/E35hVdt5Gu+YUUc5cocJQvx9j4eyg70nCSr6P46iOt7GhS3g98Pq8ow0kuvOXrr1dcsXsH33x19d+5F0PNyTiIXDOU/f9HdsTpx8ugkyQjgUpSVlRWeWDtAHssBE6FBXAhEhTjPZ92CvB14puNb54Xje8jlrMXlga+Ji7Qy3eGbEi5z4+GHC8bEtrT8gSZkgtAgqe2t6V2COaICORjpvpfjjxW5harG0075Rl23pfNfoq4SKhpebKHe5Z0AfSnfvw9ZUo6z/tW5HHe0Y48gYx11w22OFvup5z339qenEesI6kTJpKOOvIDE77M3nIK1fmldkEZtG63i6Bgr+FkQIGFVsPwXHH6k3TsjzWwxQglI6WwkbmWTAVj5zlb3rGgOPtv2lNc6bpRJ6vinrWYxTWvMot73hIrzp9QXOSXa0qpLHk9V/e4q234gNf6fc9nfYuqr5t3BJcXGK3KGq/L8k/S5dxs5XJ4f8E8q4prRL/PcFzzoTaObHnLAmhngNkHB8IWthFvMDTp8o5WzDvErW8qyqwL7WFHo1CRvcUSu52vjAwMog2NJV+rkV/bE/c5035G/lc0oB9CSmxiXMTRTmxi/K1/TV6Jv6NXLH6aguhAydcolAcIH7288XVwjO1xQfniKgr6Ji6oVMxEEBrqpxG+QW2HXMZy5NCm0JdF64u21kUl2gll10oT31Le8BHToqYi/mRpKldAI4wO/7ioPLxUusTEqDna0pCIzSqRSqbEyKyC6eNJbuH6o952nmCs11X0HcYjvfQvDKJlA/nCeEeafZ1u/BmpIltg0ylr8/Zesza371XlDOcL3NGvG/CG5DzWjdc1eLeY9Row8mY8kpCykFKKKop6Kx5ZiCrhqLMQBUhj0YahLvq3AV+KoZcy+kemOSOZiZfw7bZgYC0rdkej4j0EHhd1kHnHDEfdTlCCqHgI6XAm+3Ayow5kBmvTLYFUMov0H8dU4hUvbDabthE5inbqC1JbnlKkZAY=
*/