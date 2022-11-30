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
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/relaxed_equal.hpp>
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

/** Maps at a set of unique values to bin indices.

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
                 public metadata_base_t<MetaData> {
  // these must be private, so that they are not automatically inherited
  using value_type = Value;
  using metadata_base = metadata_base_t<MetaData>;
  using metadata_type = typename metadata_base::metadata_type;
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

     @param begin    begin of category range of unique values.
     @param end      end of category range of unique values.
     @param meta     description of the axis (optional).
     @param options  see boost::histogram::axis::option (optional).
     @param alloc    allocator instance to use (optional).
   */
  template <class It, class = detail::requires_iterator<It>>
  category(It begin, It end, metadata_type meta = {}, options_type options = {},
           allocator_type alloc = {})
      : metadata_base(std::move(meta)), vec_(alloc) {
    (void)options;
    if (std::distance(begin, end) < 0)
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("end must be reachable by incrementing begin"));
    vec_.reserve(std::distance(begin, end));
    while (begin != end) vec_.emplace_back(*begin++);
  }

  // kept for backward compatibility
  template <class It, class = detail::requires_iterator<It>>
  category(It begin, It end, metadata_type meta, allocator_type alloc)
      : category(begin, end, std::move(meta), {}, std::move(alloc)) {}

  /** Construct axis from iterable sequence of unique values.

     @param iterable sequence of unique values.
     @param meta     description of the axis.
     @param options  see boost::histogram::axis::option (optional).
     @param alloc    allocator instance to use.
   */
  template <class C, class = detail::requires_iterable<C>>
  category(const C& iterable, metadata_type meta = {}, options_type options = {},
           allocator_type alloc = {})
      : category(std::begin(iterable), std::end(iterable), std::move(meta), options,
                 std::move(alloc)) {}

  // kept for backward compatibility
  template <class C, class = detail::requires_iterable<C>>
  category(const C& iterable, metadata_type meta, allocator_type alloc)
      : category(std::begin(iterable), std::end(iterable), std::move(meta), {},
                 std::move(alloc)) {}

  /** Construct axis from an initializer list of unique values.

     @param list     `std::initializer_list` of unique values.
     @param meta     description of the axis.
     @param options  see boost::histogram::axis::option (optional).
     @param alloc    allocator instance to use.
   */
  template <class U>
  category(std::initializer_list<U> list, metadata_type meta = {},
           options_type options = {}, allocator_type alloc = {})
      : category(list.begin(), list.end(), std::move(meta), options, std::move(alloc)) {}

  // kept for backward compatibility
  template <class U>
  category(std::initializer_list<U> list, metadata_type meta, allocator_type alloc)
      : category(list.begin(), list.end(), std::move(meta), {}, std::move(alloc)) {}

  /// Constructor used by algorithm::reduce to shrink and rebin (not for users).
  category(const category& src, index_type begin, index_type end, unsigned merge)
      // LCOV_EXCL_START: gcc-8 is missing the delegated ctor for no reason
      : category(src.vec_.begin() + begin, src.vec_.begin() + end, src.metadata(), {},
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
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), detail::relaxed_equal{}) &&
           detail::relaxed_equal{}(this->metadata(), o.metadata());
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
    -> category<detail::replace_cstring<std::decay_t<T>>, null_type>;

template <class T, class M>
category(std::initializer_list<T>, M)
    -> category<detail::replace_cstring<std::decay_t<T>>,
                detail::replace_cstring<std::decay_t<M>>>;

template <class T, class M, unsigned B>
category(std::initializer_list<T>, M, const option::bitset<B>&)
    -> category<detail::replace_cstring<std::decay_t<T>>,
                detail::replace_cstring<std::decay_t<M>>, option::bitset<B>>;

#endif

} // namespace axis
} // namespace histogram
} // namespace boost

#endif

/* category.hpp
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
*/