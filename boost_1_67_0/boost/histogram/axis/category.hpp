// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_AXIS_CATEGORY_HPP
#define BOOST_HISTOGRAM_AXIS_CATEGORY_HPP

#include <algorithm>
#include <boost/core/nvp.hpp>
#include <boost/histogram/axis/iterator.hpp>
#include <boost/histogram/axis/metadata_base.hpp>
#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace boost {
namespace histogram {
namespace axis {

/**
  Maps at a set of unique values to bin indices.

  The axis maps a set of values to bins, following the order of arguments in the
  constructor. The optional overflow bin for this axis counts input values that
  are not part of the set. Binning has O(N) complexity, but with a very small
  factor. For small N (the typical use case) it beats other kinds of lookup.

  @tparam Value input value type, must be equal-comparable.
  @tparam MetaData type to store meta data.
  @tparam Options see boost::histogram::axis::option.
  @tparam Allocator allocator to use for dynamic memory management.

  The options `underflow` and `circular` are not allowed. The options `growth`
  and `overflow` are mutually exclusive.
*/
template <class Value, class MetaData, class Options, class Allocator>
class category : public iterator_mixin<category<Value, MetaData, Options, Allocator>>,
                 public metadata_base<MetaData> {
  // these must be private, so that they are not automatically inherited
  using value_type = Value;
  using metadata_type = typename metadata_base<MetaData>::metadata_type;
  using options_type = detail::replace_default<Options, option::overflow_t>;
  using allocator_type = Allocator;
  using vector_type = std::vector<value_type, allocator_type>;

  static_assert(!options_type::test(option::underflow),
                "category axis cannot have underflow");
  static_assert(!options_type::test(option::circular),
                "category axis cannot be circular");
  static_assert(!(options_type::test(option::growth) &&
                  options_type::test(option::overflow)),
                "growing category axis cannot have entries in overflow bin");

public:
  constexpr category() = default;
  explicit category(allocator_type alloc) : vec_(alloc) {}

  /** Construct from iterator range of unique values.
   *
   * \param begin     begin of category range of unique values.
   * \param end       end of category range of unique values.
   * \param meta      description of the axis.
   * \param alloc     allocator instance to use.
   */
  template <class It, class = detail::requires_iterator<It>>
  category(It begin, It end, metadata_type meta = {}, allocator_type alloc = {})
      : metadata_base<MetaData>(std::move(meta)), vec_(alloc) {
    if (std::distance(begin, end) < 0)
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("end must be reachable by incrementing begin"));
    vec_.reserve(std::distance(begin, end));
    while (begin != end) vec_.emplace_back(*begin++);
  }

  /** Construct axis from iterable sequence of unique values.
   *
   * \param iterable sequence of unique values.
   * \param meta     description of the axis.
   * \param alloc    allocator instance to use.
   */
  template <class C, class = detail::requires_iterable<C>>
  category(const C& iterable, metadata_type meta = {}, allocator_type alloc = {})
      : category(std::begin(iterable), std::end(iterable), std::move(meta),
                 std::move(alloc)) {}

  /** Construct axis from an initializer list of unique values.
   *
   * \param list   `std::initializer_list` of unique values.
   * \param meta   description of the axis.
   * \param alloc  allocator instance to use.
   */
  template <class U>
  category(std::initializer_list<U> list, metadata_type meta = {},
           allocator_type alloc = {})
      : category(list.begin(), list.end(), std::move(meta), std::move(alloc)) {}

  /// Constructor used by algorithm::reduce to shrink and rebin (not for users).
  category(const category& src, index_type begin, index_type end, unsigned merge)
      // LCOV_EXCL_START: gcc-8 is missing the delegated ctor for no reason
      : category(src.vec_.begin() + begin, src.vec_.begin() + end, src.metadata(),
                 src.get_allocator())
  // LCOV_EXCL_STOP
  {
    if (merge > 1)
      BOOST_THROW_EXCEPTION(std::invalid_argument("cannot merge bins for category axis"));
  }

  /// Return index for value argument.
  index_type index(const value_type& x) const noexcept {
    const auto beg = vec_.begin();
    const auto end = vec_.end();
    return static_cast<index_type>(std::distance(beg, std::find(beg, end, x)));
  }

  /// Returns index and shift (if axis has grown) for the passed argument.
  std::pair<index_type, index_type> update(const value_type& x) {
    const auto i = index(x);
    if (i < size()) return {i, 0};
    vec_.emplace_back(x);
    return {i, -1};
  }

  /// Return value for index argument.
  /// Throws `std::out_of_range` if the index is out of bounds.
  auto value(index_type idx) const
      -> std::conditional_t<std::is_scalar<value_type>::value, value_type,
                            const value_type&> {
    if (idx < 0 || idx >= size())
      BOOST_THROW_EXCEPTION(std::out_of_range("category index out of range"));
    return vec_[idx];
  }

  /// Return value for index argument; alias for value(...).
  decltype(auto) bin(index_type idx) const { return value(idx); }

  /// Returns the number of bins, without over- or underflow.
  index_type size() const noexcept { return static_cast<index_type>(vec_.size()); }

  /// Returns the options.
  static constexpr unsigned options() noexcept { return options_type::value; }

  /// Whether the axis is inclusive (see axis::traits::is_inclusive).
  static constexpr bool inclusive() noexcept {
    return options() & (option::overflow | option::growth);
  }

  /// Indicate that the axis is not ordered.
  static constexpr bool ordered() noexcept { return false; }

  template <class V, class M, class O, class A>
  bool operator==(const category<V, M, O, A>& o) const noexcept {
    const auto& a = vec_;
    const auto& b = o.vec_;
    return std::equal(a.begin(), a.end(), b.begin(), b.end()) &&
           metadata_base<MetaData>::operator==(o);
  }

  template <class V, class M, class O, class A>
  bool operator!=(const category<V, M, O, A>& o) const noexcept {
    return !operator==(o);
  }

  allocator_type get_allocator() const { return vec_.get_allocator(); }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    ar& make_nvp("seq", vec_);
    ar& make_nvp("meta", this->metadata());
  }

private:
  vector_type vec_;

  template <class V, class M, class O, class A>
  friend class category;
};

#if __cpp_deduction_guides >= 201606

template <class T>
category(std::initializer_list<T>)
    ->category<detail::replace_cstring<std::decay_t<T>>, null_type>;

template <class T, class M>
category(std::initializer_list<T>, M)
    ->category<detail::replace_cstring<std::decay_t<T>>,
               detail::replace_cstring<std::decay_t<M>>>;

#endif

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* category.hpp
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
*/