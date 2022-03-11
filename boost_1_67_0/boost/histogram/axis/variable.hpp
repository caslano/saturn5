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
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
*/