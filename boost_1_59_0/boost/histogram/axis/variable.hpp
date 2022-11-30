// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_VARIABLE_HPP
#define BOOST_HISTOGRAM_AXIS_VARIABLE_HPP

#include <algorithm>
#include <boost/core/nvp.hpp>
#include <boost/histogram/axis/interval_view.hpp>
#include <boost/histogram/axis/iterator.hpp>
#include <boost/histogram/axis/metadata_base.hpp>
#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/detail/convert_integer.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/limits.hpp>
#include <boost/histogram/detail/relaxed_equal.hpp>
#include <boost/histogram/detail/replace_type.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/throw_exception.hpp>
#include <cassert>
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

/** Axis for non-equidistant bins on the real line.

  Binning is a O(log(N)) operation. If speed matters and the problem domain
  allows it, prefer a regular axis, possibly with a transform.

  If the axis has an overflow bin (the default), a value on the upper edge of the last
  bin is put in the overflow bin. The axis range represents a semi-open interval.

  If the overflow bin is deactivated, then a value on the upper edge of the last bin is
  still counted towards the last bin. The axis range represents a closed interval. This
  is the desired behavior for random numbers drawn from a bounded interval, which is
  usually closed.

  @tparam Value     input value type, must be floating point.
  @tparam MetaData  type to store meta data.
  @tparam Options   see boost::histogram::axis::option.
  @tparam Allocator allocator to use for dynamic memory management.
*/
template <class Value, class MetaData, class Options, class Allocator>
class variable : public iterator_mixin<variable<Value, MetaData, Options, Allocator>>,
                 public metadata_base_t<MetaData> {
  // these must be private, so that they are not automatically inherited
  using value_type = Value;
  using metadata_base = metadata_base_t<MetaData>;
  using metadata_type = typename metadata_base::metadata_type;
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

     @param begin   begin of edge sequence.
     @param end     end of edge sequence.
     @param meta    description of the axis (optional).
     @param options see boost::histogram::axis::option (optional).
     @param alloc   allocator instance to use (optional).
   */
  template <class It, class = detail::requires_iterator<It>>
  variable(It begin, It end, metadata_type meta = {}, options_type options = {},
           allocator_type alloc = {})
      : metadata_base(std::move(meta)), vec_(std::move(alloc)) {
    (void)options;

    if (std::distance(begin, end) < 2)
      BOOST_THROW_EXCEPTION(std::invalid_argument("bins > 0 required"));

    vec_.reserve(std::distance(begin, end));
    vec_.emplace_back(*begin++);
    bool strictly_ascending = true;
    for (; begin != end; ++begin) {
      strictly_ascending &= vec_.back() < *begin;
      vec_.emplace_back(*begin);
    }
    if (!strictly_ascending)
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("input sequence must be strictly ascending"));
  }

  // kept for backward compatibility
  template <class It, class = detail::requires_iterator<It>>
  variable(It begin, It end, metadata_type meta, allocator_type alloc)
      : variable(begin, end, std::move(meta), {}, std::move(alloc)) {}

  /** Construct variable axis from iterable range of bin edges.

     @param iterable iterable range of bin edges.
     @param meta     description of the axis (optional).
     @param options  see boost::histogram::axis::option (optional).
     @param alloc    allocator instance to use (optional).
   */
  template <class U, class = detail::requires_iterable<U>>
  variable(const U& iterable, metadata_type meta = {}, options_type options = {},
           allocator_type alloc = {})
      : variable(std::begin(iterable), std::end(iterable), std::move(meta), options,
                 std::move(alloc)) {}

  // kept for backward compatibility
  template <class U, class = detail::requires_iterable<U>>
  variable(const U& iterable, metadata_type meta, allocator_type alloc)
      : variable(std::begin(iterable), std::end(iterable), std::move(meta), {},
                 std::move(alloc)) {}

  /** Construct variable axis from initializer list of bin edges.

     @param list     `std::initializer_list` of bin edges.
     @param meta     description of the axis (optional).
     @param options  see boost::histogram::axis::option (optional).
     @param alloc    allocator instance to use (optional).
   */
  template <class U>
  variable(std::initializer_list<U> list, metadata_type meta = {},
           options_type options = {}, allocator_type alloc = {})
      : variable(list.begin(), list.end(), std::move(meta), options, std::move(alloc)) {}

  // kept for backward compatibility
  template <class U>
  variable(std::initializer_list<U> list, metadata_type meta, allocator_type alloc)
      : variable(list.begin(), list.end(), std::move(meta), {}, std::move(alloc)) {}

  /// Constructor used by algorithm::reduce to shrink and rebin (not for users).
  variable(const variable& src, index_type begin, index_type end, unsigned merge)
      : metadata_base(src), vec_(src.get_allocator()) {
    assert((end - begin) % merge == 0);
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
    // upper edge of last bin is inclusive if overflow bin is not present
    if (!options_type::test(option::overflow) && x == vec_.back()) return size() - 1;
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
    // check z == 0 needed to avoid returning nan when vec_[k + 1] is infinity
    return (1.0 - z) * vec_[k] + (z == 0 ? 0 : z * vec_[k + 1]);
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
           detail::relaxed_equal{}(this->metadata(), o.metadata());
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
    -> variable<detail::convert_integer<T, double>, null_type>;

template <class T, class M>
variable(std::initializer_list<T>, M)
    -> variable<detail::convert_integer<T, double>,
                detail::replace_type<std::decay_t<M>, const char*, std::string>>;

template <class T, class M, unsigned B>
variable(std::initializer_list<T>, M, const option::bitset<B>&)
    -> variable<detail::convert_integer<T, double>,
                detail::replace_type<std::decay_t<M>, const char*, std::string>,
                option::bitset<B>>;

template <class Iterable, class = detail::requires_iterable<Iterable>>
variable(Iterable) -> variable<
    detail::convert_integer<
        std::decay_t<decltype(*std::begin(std::declval<Iterable&>()))>, double>,
    null_type>;

template <class Iterable, class M>
variable(Iterable, M) -> variable<
    detail::convert_integer<
        std::decay_t<decltype(*std::begin(std::declval<Iterable&>()))>, double>,
    detail::replace_type<std::decay_t<M>, const char*, std::string>>;

template <class Iterable, class M, unsigned B>
variable(Iterable, M, const option::bitset<B>&) -> variable<
    detail::convert_integer<
        std::decay_t<decltype(*std::begin(std::declval<Iterable&>()))>, double>,
    detail::replace_type<std::decay_t<M>, const char*, std::string>, option::bitset<B>>;

#endif

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* variable.hpp
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
*/