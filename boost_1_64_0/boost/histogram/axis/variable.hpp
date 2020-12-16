// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_VARIABLE_HPP
#define BOOST_HISTOGRAM_AXIS_VARIABLE_HPP

#include <algorithm>
#include <boost/assert.hpp>
#include <boost/core/nvp.hpp>
#include <boost/histogram/axis/interval_view.hpp>
#include <boost/histogram/axis/iterator.hpp>
#include <boost/histogram/axis/metadata_base.hpp>
#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/detail/convert_integer.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/limits.hpp>
#include <boost/histogram/detail/replace_type.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/throw_exception.hpp>
#include <cmath>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace boost {
namespace histogram {
namespace axis {

/**
  Axis for non-equidistant bins on the real line.

  Binning is a O(log(N)) operation. If speed matters and the problem domain
  allows it, prefer a regular axis, possibly with a transform.

  @tparam Value input value type, must be floating point.
  @tparam MetaData type to store meta data.
  @tparam Options see boost::histogram::axis::option (all values allowed).
  @tparam Allocator allocator to use for dynamic memory management.
 */
template <class Value, class MetaData, class Options, class Allocator>
class variable : public iterator_mixin<variable<Value, MetaData, Options, Allocator>>,
                 public metadata_base<MetaData> {
  // these must be private, so that they are not automatically inherited
  using value_type = Value;
  using metadata_type = typename metadata_base<MetaData>::metadata_type;
  using options_type =
      detail::replace_default<Options, decltype(option::underflow | option::overflow)>;
  using allocator_type = Allocator;
  using vector_type = std::vector<Value, allocator_type>;

  static_assert(
      std::is_floating_point<value_type>::value,
      "current version of variable axis requires floating point type; "
      "if you need a variable axis with an integral type, please submit an issue");

  static_assert(
      (!options_type::test(option::circular) && !options_type::test(option::growth)) ||
          (options_type::test(option::circular) ^ options_type::test(option::growth)),
      "circular and growth options are mutually exclusive");

public:
  constexpr variable() = default;
  explicit variable(allocator_type alloc) : vec_(alloc) {}

  /** Construct from iterator range of bin edges.
   *
   * \param begin begin of edge sequence.
   * \param end   end of edge sequence.
   * \param meta  description of the axis.
   * \param alloc allocator instance to use.
   */
  template <class It, class = detail::requires_iterator<It>>
  variable(It begin, It end, metadata_type meta = {}, allocator_type alloc = {})
      : metadata_base<MetaData>(std::move(meta)), vec_(std::move(alloc)) {
    if (std::distance(begin, end) < 2)
      BOOST_THROW_EXCEPTION(std::invalid_argument("bins > 0 required"));

    vec_.reserve(std::distance(begin, end));
    vec_.emplace_back(*begin++);
    bool strictly_ascending = true;
    while (begin != end) {
      if (*begin <= vec_.back()) strictly_ascending = false;
      vec_.emplace_back(*begin++);
    }
    if (!strictly_ascending)
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("input sequence must be strictly ascending"));
  }

  /** Construct variable axis from iterable range of bin edges.
   *
   * \param iterable iterable range of bin edges.
   * \param meta     description of the axis.
   * \param alloc    allocator instance to use.
   */
  template <class U, class = detail::requires_iterable<U>>
  variable(const U& iterable, metadata_type meta = {}, allocator_type alloc = {})
      : variable(std::begin(iterable), std::end(iterable), std::move(meta),
                 std::move(alloc)) {}

  /** Construct variable axis from initializer list of bin edges.
   *
   * @param list  `std::initializer_list` of bin edges.
   * @param meta  description of the axis.
   * @param alloc allocator instance to use.
   */
  template <class U>
  variable(std::initializer_list<U> list, metadata_type meta = {},
           allocator_type alloc = {})
      : variable(list.begin(), list.end(), std::move(meta), std::move(alloc)) {}

  /// Constructor used by algorithm::reduce to shrink and rebin (not for users).
  variable(const variable& src, index_type begin, index_type end, unsigned merge)
      : metadata_base<MetaData>(src), vec_(src.get_allocator()) {
    BOOST_ASSERT((end - begin) % merge == 0);
    if (options_type::test(option::circular) && !(begin == 0 && end == src.size()))
      BOOST_THROW_EXCEPTION(std::invalid_argument("cannot shrink circular axis"));
    vec_.reserve((end - begin) / merge);
    const auto beg = src.vec_.begin();
    for (index_type i = begin; i <= end; i += merge) vec_.emplace_back(*(beg + i));
  }

  /// Return index for value argument.
  index_type index(value_type x) const noexcept {
    if (options_type::test(option::circular)) {
      const auto a = vec_[0];
      const auto b = vec_[size()];
      x -= std::floor((x - a) / (b - a)) * (b - a);
    }
    return static_cast<index_type>(std::upper_bound(vec_.begin(), vec_.end(), x) -
                                   vec_.begin() - 1);
  }

  std::pair<index_type, index_type> update(value_type x) noexcept {
    const auto i = index(x);
    if (std::isfinite(x)) {
      if (0 <= i) {
        if (i < size()) return std::make_pair(i, 0);
        const auto d = value(size()) - value(size() - 0.5);
        x = std::nextafter(x, (std::numeric_limits<value_type>::max)());
        x = (std::max)(x, vec_.back() + d);
        vec_.push_back(x);
        return {i, -1};
      }
      const auto d = value(0.5) - value(0);
      x = (std::min)(x, value(0) - d);
      vec_.insert(vec_.begin(), x);
      return {0, -i};
    }
    return {x < 0 ? -1 : size(), 0};
  }

  /// Return value for fractional index argument.
  value_type value(real_index_type i) const noexcept {
    if (options_type::test(option::circular)) {
      auto shift = std::floor(i / size());
      i -= shift * size();
      double z;
      const auto k = static_cast<index_type>(std::modf(i, &z));
      const auto a = vec_[0];
      const auto b = vec_[size()];
      return (1.0 - z) * vec_[k] + z * vec_[k + 1] + shift * (b - a);
    }
    if (i < 0) return detail::lowest<value_type>();
    if (i == size()) return vec_.back();
    if (i > size()) return detail::highest<value_type>();
    const auto k = static_cast<index_type>(i); // precond: i >= 0
    const real_index_type z = i - k;
    return (1.0 - z) * vec_[k] + z * vec_[k + 1];
  }

  /// Return bin for index argument.
  auto bin(index_type idx) const noexcept { return interval_view<variable>(*this, idx); }

  /// Returns the number of bins, without over- or underflow.
  index_type size() const noexcept { return static_cast<index_type>(vec_.size()) - 1; }

  /// Returns the options.
  static constexpr unsigned options() noexcept { return options_type::value; }

  template <class V, class M, class O, class A>
  bool operator==(const variable<V, M, O, A>& o) const noexcept {
    const auto& a = vec_;
    const auto& b = o.vec_;
    return std::equal(a.begin(), a.end(), b.begin(), b.end()) &&
           metadata_base<MetaData>::operator==(o);
  }

  template <class V, class M, class O, class A>
  bool operator!=(const variable<V, M, O, A>& o) const noexcept {
    return !operator==(o);
  }

  /// Return allocator instance.
  auto get_allocator() const { return vec_.get_allocator(); }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("seq", vec_);
    ar& make_nvp("meta", this->metadata());
  }

private:
  vector_type vec_;

  template <class V, class M, class O, class A>
  friend class variable;
};

#if __cpp_deduction_guides >= 201606

template <class T>
variable(std::initializer_list<T>)
    ->variable<detail::convert_integer<T, double>, null_type>;

template <class T, class M>
variable(std::initializer_list<T>, M)
    ->variable<detail::convert_integer<T, double>,
               detail::replace_type<std::decay_t<M>, const char*, std::string>>;

template <class Iterable, class = detail::requires_iterable<Iterable>>
variable(Iterable)
    ->variable<
        detail::convert_integer<
            std::decay_t<decltype(*std::begin(std::declval<Iterable&>()))>, double>,
        null_type>;

template <class Iterable, class M>
variable(Iterable, M)
    ->variable<
        detail::convert_integer<
            std::decay_t<decltype(*std::begin(std::declval<Iterable&>()))>, double>,
        detail::replace_type<std::decay_t<M>, const char*, std::string>>;

#endif

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* variable.hpp
cn1RFoWg7jVUs6pzgKlJpexrHau6xyXOqNzDZPqxNkqfkZD+ZDP9VbH078O0S2E1i7FqH2vqmBs5jjF7pMbs+KAZfSeiFUIU16He9KABl8Shwm8oNEwHGn3dwNKOu8a8Wcp/JCynavqb48gt3h4lx9HWSKGxfpgF/mlPQb4QCkeSom3E5s7FRQtVzCRw1d6lg/TB32J4ykZmlWsXelMVvG1BwmkZpsoh1ZIq1Zk880BLHxl+SDzjv/kDdOqFwlsXaTfEqfKmYheLmV/1A/VIt9CgoDKmEud+hVp933IHeOua3IR5wRs4XFxZKycG/6nr1KwgSz1D3HGBJoGjwCMo5MIRcQydzZSk88gkZ6SW3sgf/x5dkPi+5crE954XJL7/dXji+7pW+W9ulf/DqYnv/isS37vPT3iX8spCrNTZEtHuYmmD+CxL3nGOSvLVPJgL5PTwTTbsD5J1hs8Hdvv+dEXYJGAwxmkAelnhxkIj73mKHL88Wr2L1cn+w+Ts9ekwffN1N9/lEupFDPVXEqpvDgd6RIcJ6oTkIQkyur12nv9IBPbq9YmYVqlUXiewNQbKY63XDFQiRVbCI4bMNmfycWypbvpNE1dfzXsGWagcZIRNgBIyoUxnKE9fpKDsmRUHxWf1EBf0joq757BAjAxqLJ9lLDfhXMxw/IBjXKcDWb3/1ThO7hF3xoMGhvOAYS+PmKuGMoaNm+IyOsVqZGQLovYdOE0Kv6fOIvyCxb5WoRS0eb5jNVrnoSEPTVO7o1YP11rWgtrP5sfQHpnnxgvFN4uVG3NAOVFCmcNQLtJQ1lbFQXH7TuZEXhEZxpc6FSKKXOv/5fLYKd7jfKfG16eHhDTBK2YlgNIzI+2I3jCO0xCH9xUrmpwN9uM7Q0JKJUho86sXco8AVl48LFRErlHD9iJMgvbJjH6GVqqg9SZogyQ0v4K22IT29ph4aDhsCU/LJIhk2poarPglzWpKQyFSPixT/sxdm9THK8LjVZcf5TvCKJUovhQoXvML00GAzwYnIpOLdzDXFV3R6tDIdGnKkt6todzp7+TrLbPOi2SL5gqObyjPYm33MfFAL5RAveKEczT1N4FBJN9otf95KU/txPc74fIPex4t8iP9w/g/Cv/s7M8a5s1lSlxB204y/LIal6Eaf7lAtQ0dA681yHZAt0+j4O/yKkmLuF53YQd2Qeo7jSFSSYyWCzySWza3qw+lfeajM+R5FXYpkxO/T1gU1QYsfHdwnqgj7G6BRI6NaHj0tbE0OFW8/EvunWl8a0mZCPr0FaB0sWT9H5GMbn941Eb373C9PWIB5GbfDN2IYqQtE5dQ2KUkxmP+5Sj4+0EYKVZCu87DEqDM9iWwEHr+lu/20rHnPp83wKc6rS3DFVHbK6FGhPd5ATP0Jp8/bD8R/VIowQBmqciYaZ5FFd8O5wOA2+hnjLzotO4Nx5J0VJHMq+H5eU+KvAbqHykclI2gz1Pk3SufpMijgu+lUMNqj3WshpuJ0Cuhdy9Zb8UHfktDP8Bz6Ysh4Im9l5KpV1G0H5YwtceHIC4jopj8hYY2jLjlu5q8yqX2vvXW8v67a75EbAll49QFtX3wXkZbiewvHunDZ1tvGYEsQylLeRRZIjoL78hPc4vAlaas2w8VZNpyixNqzNDeCFUTSI5bdEYELaxUZAbfxIp9y9fm6wx8GSrLPqjTmNrzdUGZsYJes0qXLtLv+tpYxB+tBE4G18Yg/h7BI/oDWs3jtH8eauwHNxS0r+6opGs9vVSAyFrTwRICMdC8g2g4hQ9PQj7r0LyJfTZSlRsQWrQJPXA0GftgPUQEAEvRpfbu9fZ+5f1fAT4nymPi4Mh/Nszi6R4SqQQ=
*/