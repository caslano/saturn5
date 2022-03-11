// Copyright 2015-2016 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_INDEXED_HPP
#define BOOST_HISTOGRAM_INDEXED_HPP

#include <array>
#include <boost/config.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/iterator_adaptor.hpp>
#include <boost/histogram/detail/operators.hpp>
#include <boost/histogram/fwd.hpp>
#include <iterator>
#include <type_traits>
#include <utility>

namespace boost {
namespace histogram {

/** Coverage mode of the indexed range generator.

  Defines options for the iteration strategy.
*/
enum class coverage {
  inner, /*!< iterate over inner bins, exclude underflow and overflow */
  all,   /*!< iterate over all bins, including underflow and overflow */
};

/** Input iterator range over histogram bins with multi-dimensional index.

  The iterator returned by begin() can only be incremented. begin() may only be called
  once, calling it a second time returns the end() iterator. If several copies of the
  input iterators exist, the other copies become invalid if one of them is incremented.
*/
template <class Histogram>
class BOOST_ATTRIBUTE_NODISCARD indexed_range {
private:
  using histogram_type = Histogram;
  static constexpr std::size_t buffer_size =
      detail::buffer_size<typename std::remove_const_t<histogram_type>::axes_type>::value;

public:
  using value_iterator = std::conditional_t<std::is_const<histogram_type>::value,
                                            typename histogram_type::const_iterator,
                                            typename histogram_type::iterator>;
  using value_reference = typename std::iterator_traits<value_iterator>::reference;
  using value_type = typename std::iterator_traits<value_iterator>::value_type;

  class iterator;
  using range_iterator [[deprecated("use iterator instead")]] = iterator; ///< deprecated

  /** Lightweight view to access value and index of current cell.

    The methods provide access to the current cell indices and bins. It acts like a
    pointer to the cell value, and in a limited way also like a reference. To interoperate
    with the algorithms of the standard library, the accessor is implicitly convertible to
    a cell value. Assignments and comparisons are passed through to the cell. An accessor
    is coupled to its parent indexed_range::iterator. Moving the parent iterator
    forward also updates the linked accessor. Accessors are not copyable. They cannot be
    stored in containers, but indexed_range::iterator can be stored.
  */
  class BOOST_ATTRIBUTE_NODISCARD accessor : detail::mirrored<accessor, void> {
  public:
    /// Array-like view into the current multi-dimensional index.
    class index_view {
      using index_pointer = const typename iterator::index_data*;

    public:
      using const_reference = const axis::index_type&;
      using reference [[deprecated("use const_reference instead")]] =
          const_reference; ///< deprecated

      /// implementation detail
      class const_iterator
          : public detail::iterator_adaptor<const_iterator, index_pointer,
                                            const_reference> {
      public:
        const_reference operator*() const noexcept { return const_iterator::base()->idx; }

      private:
        explicit const_iterator(index_pointer i) noexcept
            : const_iterator::iterator_adaptor_(i) {}

        friend class index_view;
      };

      const_iterator begin() const noexcept { return const_iterator{begin_}; }
      const_iterator end() const noexcept { return const_iterator{end_}; }
      std::size_t size() const noexcept {
        return static_cast<std::size_t>(end_ - begin_);
      }
      const_reference operator[](unsigned d) const noexcept { return begin_[d].idx; }
      const_reference at(unsigned d) const { return begin_[d].idx; }

    private:
      /// implementation detail
      index_view(index_pointer b, index_pointer e) : begin_(b), end_(e) {}

      index_pointer begin_, end_;
      friend class accessor;
    };

    // assignment is pass-through
    accessor& operator=(const accessor& o) {
      get() = o.get();
      return *this;
    }

    // assignment is pass-through
    template <class T>
    accessor& operator=(const T& x) {
      get() = x;
      return *this;
    }

    /// Returns the cell reference.
    value_reference get() const noexcept { return *(iter_.iter_); }
    /// @copydoc get()
    value_reference operator*() const noexcept { return get(); }
    /// Access fields and methods of the cell object.
    value_iterator operator->() const noexcept { return iter_.iter_; }

    /// Access current index.
    /// @param d axis dimension.
    axis::index_type index(unsigned d = 0) const noexcept {
      return iter_.indices_[d].idx;
    }

    /// Access indices as an iterable range.
    index_view indices() const noexcept {
      BOOST_ASSERT(iter_.indices_.hist_);
      return {iter_.indices_.begin(), iter_.indices_.end()};
    }

    /// Access current bin.
    /// @tparam N axis dimension.
    template <unsigned N = 0>
    decltype(auto) bin(std::integral_constant<unsigned, N> = {}) const {
      BOOST_ASSERT(iter_.indices_.hist_);
      return iter_.indices_.hist_->axis(std::integral_constant<unsigned, N>())
          .bin(index(N));
    }

    /// Access current bin.
    /// @param d axis dimension.
    decltype(auto) bin(unsigned d) const {
      BOOST_ASSERT(iter_.indices_.hist_);
      return iter_.indices_.hist_->axis(d).bin(index(d));
    }

    /** Computes density in current cell.

      The density is computed as the cell value divided by the product of bin widths. Axes
      without bin widths, like axis::category, are treated as having unit bin with.
    */
    double density() const {
      BOOST_ASSERT(iter_.indices_.hist_);
      double x = 1;
      unsigned d = 0;
      iter_.indices_.hist_->for_each_axis([&](const auto& a) {
        const auto w = axis::traits::width_as<double>(a, this->index(d++));
        x *= w ? w : 1;
      });
      return get() / x;
    }

    // forward all comparison operators to the value
    bool operator<(const accessor& o) noexcept { return get() < o.get(); }
    bool operator>(const accessor& o) noexcept { return get() > o.get(); }
    bool operator==(const accessor& o) noexcept { return get() == o.get(); }
    bool operator!=(const accessor& o) noexcept { return get() != o.get(); }
    bool operator<=(const accessor& o) noexcept { return get() <= o.get(); }
    bool operator>=(const accessor& o) noexcept { return get() >= o.get(); }

    template <class U>
    bool operator<(const U& o) const noexcept {
      return get() < o;
    }

    template <class U>
    bool operator>(const U& o) const noexcept {
      return get() > o;
    }

    template <class U>
    bool operator==(const U& o) const noexcept {
      return get() == o;
    }

    template <class U>
    bool operator!=(const U& o) const noexcept {
      return get() != o;
    }

    template <class U>
    bool operator<=(const U& o) const noexcept {
      return get() <= o;
    }

    template <class U>
    bool operator>=(const U& o) const noexcept {
      return get() >= o;
    }

    operator value_type() const noexcept { return get(); }

  private:
    accessor(iterator& i) noexcept : iter_(i) {}

    accessor(const accessor&) = default; // only callable by indexed_range::iterator

    iterator& iter_;

    friend class iterator;
  };

  /// implementation detail
  class iterator {
  public:
    using value_type = typename indexed_range::value_type;
    using reference = accessor;

  private:
    struct pointer_proxy {
      reference* operator->() noexcept { return std::addressof(ref_); }
      reference ref_;
    };

  public:
    using pointer = pointer_proxy;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    reference operator*() noexcept { return *this; }
    pointer operator->() noexcept { return pointer_proxy{operator*()}; }

    iterator& operator++() {
      BOOST_ASSERT(iter_ < indices_.hist_->end());
      const auto cbeg = indices_.begin();
      auto c = cbeg;
      ++iter_;
      ++c->idx;
      if (c->idx < c->end) return *this;
      while (c->idx == c->end) {
        iter_ += c->end_skip;
        if (++c == indices_.end()) return *this;
        ++c->idx;
      }
      while (c-- != cbeg) {
        c->idx = c->begin;
        iter_ += c->begin_skip;
      }
      return *this;
    }

    iterator operator++(int) {
      auto prev = *this;
      operator++();
      return prev;
    }

    bool operator==(const iterator& x) const noexcept { return iter_ == x.iter_; }
    bool operator!=(const iterator& x) const noexcept { return !operator==(x); }

    // make iterator ready for C++17 sentinels
    bool operator==(const value_iterator& x) const noexcept { return iter_ == x; }
    bool operator!=(const value_iterator& x) const noexcept { return !operator==(x); }

    // useful for iterator debugging
    std::size_t offset() const noexcept { return iter_ - indices_.hist_->begin(); }

  private:
    iterator(value_iterator i, histogram_type& h) : iter_(i), indices_(&h) {}

    value_iterator iter_;

    struct index_data {
      axis::index_type idx, begin, end;
      std::size_t begin_skip, end_skip;
    };

    struct indices_t : private std::array<index_data, buffer_size> {
      using base_type = std::array<index_data, buffer_size>;
      using pointer = index_data*;
      using const_pointer = const index_data*;

      indices_t(histogram_type* h) noexcept : hist_{h} {}

      using base_type::operator[];
      unsigned size() const noexcept { return hist_->rank(); }
      pointer begin() noexcept { return base_type::data(); }
      const_pointer begin() const noexcept { return base_type::data(); }
      pointer end() noexcept { return begin() + size(); }
      const_pointer end() const noexcept { return begin() + size(); }

      histogram_type* hist_;
    } indices_;

    friend class indexed_range;
  };

  indexed_range(histogram_type& hist, coverage cov)
      : begin_(hist.begin(), hist), end_(hist.end(), hist) {
    begin_.indices_.hist_->for_each_axis([ca = begin_.indices_.begin(), cov,
                                          stride = std::size_t{1},
                                          this](const auto& a) mutable {
      using opt = axis::traits::get_options<std::decay_t<decltype(a)>>;
      constexpr axis::index_type under = opt::test(axis::option::underflow);
      constexpr axis::index_type over = opt::test(axis::option::overflow);
      const auto size = a.size();

      // -1 if underflow and cover all, else 0
      ca->begin = cov == coverage::all ? -under : 0;
      // size + 1 if overflow and cover all, else size
      ca->end = cov == coverage::all ? size + over : size;
      ca->idx = ca->begin;

      // if axis has *flow and coverage::all OR axis has no *flow:
      //   begin + under == 0, size + over - end == 0
      // if axis has *flow and coverage::inner:
      //   begin + under == 1, size + over - end == 1
      ca->begin_skip = static_cast<std::size_t>(ca->begin + under) * stride;
      ca->end_skip = static_cast<std::size_t>(size + over - ca->end) * stride;
      begin_.iter_ += ca->begin_skip;

      stride *= size + under + over;
      ++ca;
    });
  }

  iterator begin() noexcept { return begin_; }
  iterator end() noexcept { return end_; }

private:
  iterator begin_, end_;
};

/** Generates an indexed range of <a
  href="https://en.cppreference.com/w/cpp/named_req/ForwardIterator">forward iterators</a>
  over the histogram cells.

  Use this in a range-based for loop:

  ```
  for (auto&& x : indexed(hist)) { ... }
  ```

  This generates an optimized loop which is nearly always faster than a hand-written loop
  over the histogram cells. The iterators dereference to an indexed_range::accessor, which
  has methods to query the current indices and bins and acts like a pointer to the cell
  value. The returned iterators are forward iterators. They can be stored in a container,
  but may not be used after the life-time of the histogram ends.

  @returns indexed_range

  @param hist Reference to the histogram.
  @param cov  Iterate over all or only inner bins (optional, default: inner).
 */
template <class Histogram>
auto indexed(Histogram&& hist, coverage cov = coverage::inner) {
  return indexed_range<std::remove_reference_t<Histogram>>{std::forward<Histogram>(hist),
                                                           cov};
}

} // namespace histogram
} // namespace boost

#endif

/* indexed.hpp
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
*/