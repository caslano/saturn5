// Copyright 2015-2016 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_INDEXED_HPP
#define BOOST_HISTOGRAM_INDEXED_HPP

#include <array>
#include <boost/config.hpp> // BOOST_ATTRIBUTE_NODISCARD
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/iterator_adaptor.hpp>
#include <boost/histogram/detail/operators.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/histogram/unsafe_access.hpp>
#include <iterator>
#include <type_traits>
#include <utility> // std::get

namespace boost {
namespace histogram {

namespace detail {
using std::get;

template <std::size_t I, class T>
auto get(T&& t) -> decltype(t[0]) {
  return t[I];
}
} // namespace detail

/** Coverage mode of the indexed range generator.

  Defines options for the iteration strategy.
*/
enum class coverage {
  inner, /*!< iterate over inner bins, exclude underflow and overflow */
  all,   /*!< iterate over all bins, including underflow and overflow */
};

/** Input iterator range over histogram bins with multi-dimensional index.

  The iterator returned by begin() can only be incremented. If several copies of the
  input iterators exist, the other copies become invalid if one of them is incremented.
*/
template <class Histogram>
class BOOST_ATTRIBUTE_NODISCARD indexed_range {
private:
  using histogram_type = Histogram;
  static constexpr unsigned buffer_size =
      detail::buffer_size<typename std::decay_t<histogram_type>::axes_type>::value;

public:
  /// implementation detail
  using value_iterator = std::conditional_t<std::is_const<histogram_type>::value,
                                            typename histogram_type::const_iterator,
                                            typename histogram_type::iterator>;
  /// implementation detail
  using value_reference = typename std::iterator_traits<value_iterator>::reference;
  /// implementation detail
  using value_type = typename std::iterator_traits<value_iterator>::value_type;

  class iterator;
  using range_iterator [[deprecated("use iterator instead; "
                                    "range_iterator will be removed in boost-1.80")]] =
      iterator; ///< deprecated

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
      using reference [[deprecated("use const_reference instead; "
                                   "reference will be removed in boost-1.80")]] =
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
      assert(iter_.indices_.hist_);
      return {iter_.indices_.begin(), iter_.indices_.end()};
    }

    /// Access current bin.
    /// @tparam N axis dimension.
    template <unsigned N = 0>
    decltype(auto) bin(std::integral_constant<unsigned, N> = {}) const {
      assert(iter_.indices_.hist_);
      return iter_.indices_.hist_->axis(std::integral_constant<unsigned, N>())
          .bin(index(N));
    }

    /// Access current bin.
    /// @param d axis dimension.
    decltype(auto) bin(unsigned d) const {
      assert(iter_.indices_.hist_);
      return iter_.indices_.hist_->axis(d).bin(index(d));
    }

    /** Computes density in current cell.

      The density is computed as the cell value divided by the product of bin widths. Axes
      without bin widths, like axis::category, are treated as having unit bin with.
    */
    double density() const {
      assert(iter_.indices_.hist_);
      double x = 1;
      unsigned d = 0;
      iter_.indices_.hist_->for_each_axis([&](const auto& a) {
        const auto w = axis::traits::width_as<double>(a, this->index(d++));
        x *= w != 0 ? w : 1;
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
      assert(iter_ < indices_.hist_->end());
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
      : indexed_range(hist, make_range(hist, cov)) {}

  template <class Iterable, class = detail::requires_iterable<Iterable>>
  indexed_range(histogram_type& hist, Iterable&& range)
      : begin_(hist.begin(), hist), end_(hist.end(), hist) {
    auto r_begin = std::begin(range);
    assert(std::distance(r_begin, std::end(range)) == static_cast<int>(hist.rank()));

    begin_.indices_.hist_->for_each_axis([ca = begin_.indices_.begin(), r_begin,
                                          stride = std::size_t{1},
                                          this](const auto& a) mutable {
      const auto size = a.size();

      using opt = axis::traits::get_options<std::decay_t<decltype(a)>>;
      constexpr axis::index_type start = opt::test(axis::option::underflow) ? -1 : 0;
      const auto stop = size + (opt::test(axis::option::overflow) ? 1 : 0);

      ca->begin = std::max(start, detail::get<0>(*r_begin));
      ca->end = std::min(stop, detail::get<1>(*r_begin));
      assert(ca->begin <= ca->end);
      ca->idx = ca->begin;

      ca->begin_skip = static_cast<std::size_t>(ca->begin - start) * stride;
      ca->end_skip = static_cast<std::size_t>(stop - ca->end) * stride;
      begin_.iter_ += ca->begin_skip;

      stride *= stop - start;

      ++ca;
      ++r_begin;
    });
  }

  iterator begin() noexcept { return begin_; }
  iterator end() noexcept { return end_; }

private:
  auto make_range(histogram_type& hist, coverage cov) {
    using range_item = std::array<axis::index_type, 2>;
    auto b = detail::make_stack_buffer<range_item>(unsafe_access::axes(hist));
    hist.for_each_axis([cov, it = std::begin(b)](const auto& a) mutable {
      (*it)[0] = 0;
      (*it)[1] = a.size();
      if (cov == coverage::all) {
        (*it)[0] -= 1;
        (*it)[1] += 1;
      } else
        assert(cov == coverage::inner);
      ++it;
    });
    return b;
  }

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

/** Generates and indexed range <a
  href="https://en.cppreference.com/w/cpp/named_req/ForwardIterator">forward iterators</a>
  over a rectangular region of histogram cells.

  Use this in a range-based for loop. Example:
  ```
  auto hist = make_histogram(axis::integer<>(0, 4), axis::integer<>(2, 6));
  axis::index_type range[2] = {{1, 3}, {0, 2}};
  for (auto&& x : indexed(hist, range)) { ... }
  ```
  This skips the first and last index of the first axis, and the last two indices of the
  second.

  @returns indexed_range

  @param hist  Reference to the histogram.
  @param range Iterable over items with two axis::index_type values, which mark the
               begin and end index of each axis. The length of the iterable must be
               equal to the rank of the histogram. The begin index must be smaller than
               the end index. Index ranges wider than the actual range are reduced to
               the actual range including underflow and overflow indices.
*/
template <class Histogram, class Iterable, class = detail::requires_iterable<Iterable>>
auto indexed(Histogram&& hist, Iterable&& range) {
  return indexed_range<std::remove_reference_t<Histogram>>{std::forward<Histogram>(hist),
                                                           std::forward<Iterable>(range)};
}

} // namespace histogram
} // namespace boost

#endif

/* indexed.hpp
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
*/