// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_FILL_N_HPP
#define BOOST_HISTOGRAM_DETAIL_FILL_N_HPP

#include <algorithm>
#include <boost/assert.hpp>
#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/fill.hpp>
#include <boost/histogram/detail/linearize.hpp>
#include <boost/histogram/detail/non_member_container_access.hpp>
#include <boost/histogram/detail/optional_index.hpp>
#include <boost/histogram/detail/span.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/variant2/variant.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/bind.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <type_traits>
#include <utility>

namespace boost {
namespace histogram {
namespace detail {

namespace dtl = boost::histogram::detail;

template <class Axes, class T>
using is_convertible_to_any_value_type =
    mp11::mp_any_of_q<value_types<Axes>, mp11::mp_bind_front<std::is_convertible, T>>;

template <class... Ts>
void fold(Ts&&...) noexcept {} // helper to enable operator folding

template <class T>
auto to_ptr_size(const T& x) {
  return static_if<std::is_scalar<T>>(
      [](const auto& x) { return std::make_pair(&x, static_cast<std::size_t>(0)); },
      [](const auto& x) { return std::make_pair(dtl::data(x), dtl::size(x)); }, x);
}

template <class F, class V>
decltype(auto) maybe_visit(F&& f, V&& v) {
  return static_if<is_variant<std::decay_t<V>>>(
      [](auto&& f, auto&& v) {
        return variant2::visit(std::forward<F>(f), std::forward<V>(v));
      },
      [](auto&& f, auto&& v) { return std::forward<F>(f)(std::forward<V>(v)); },
      std::forward<F>(f), std::forward<V>(v));
}

template <class Index, class Axis, class IsGrowing>
struct index_visitor {
  using index_type = Index;
  using pointer = index_type*;
  using value_type = axis::traits::value_type<Axis>;
  using Opt = axis::traits::get_options<Axis>;

  Axis& axis_;
  const std::size_t stride_, start_, size_; // start and size of value collection
  const pointer begin_;
  axis::index_type* shift_;

  index_visitor(Axis& a, std::size_t& str, const std::size_t& sta, const std::size_t& si,
                const pointer it, axis::index_type* shift)
      : axis_(a), stride_(str), start_(sta), size_(si), begin_(it), shift_(shift) {}

  template <class T>
  void call_2(std::true_type, pointer it, const T& x) const {
    // must use this code for all axes if one of them is growing
    axis::index_type shift;
    linearize_growth(*it, shift, stride_, axis_,
                     try_cast<value_type, std::invalid_argument>(x));
    if (shift > 0) { // shift previous indices, because axis zero-point has changed
      while (it != begin_) *--it += static_cast<std::size_t>(shift) * stride_;
      *shift_ += shift;
    }
  }

  template <class T>
  void call_2(std::false_type, pointer it, const T& x) const {
    // no axis is growing
    linearize(*it, stride_, axis_, try_cast<value_type, std::invalid_argument>(x));
  }

  template <class T>
  void call_1(std::false_type, const T& iterable) const {
    // T is iterable; fill N values
    const auto* tp = dtl::data(iterable) + start_;
    for (auto it = begin_; it != begin_ + size_; ++it) call_2(IsGrowing{}, it, *tp++);
  }

  template <class T>
  void call_1(std::true_type, const T& value) const {
    // T is compatible value; fill single value N times
    index_type idx{*begin_};
    call_2(IsGrowing{}, &idx, value);
    if (is_valid(idx)) {
      const auto delta =
          static_cast<std::intptr_t>(idx) - static_cast<std::intptr_t>(*begin_);
      for (auto&& i : make_span(begin_, size_)) i += delta;
    } else
      std::fill(begin_, begin_ + size_, invalid_index);
  }

  template <class T>
  void operator()(const T& iterable_or_value) const {
    call_1(mp11::mp_bool<(std::is_convertible<T, value_type>::value ||
                          !is_iterable<T>::value)>{},
           iterable_or_value);
  }
};

template <class Index, class S, class Axes, class T>
void fill_n_indices(Index* indices, const std::size_t start, const std::size_t size,
                    const std::size_t offset, S& storage, Axes& axes, const T* viter) {
  axis::index_type extents[buffer_size<Axes>::value];
  axis::index_type shifts[buffer_size<Axes>::value];
  for_each_axis(axes, [eit = extents, sit = shifts](const auto& a) mutable {
    *sit++ = 0;
    *eit++ = axis::traits::extent(a);
  }); // LCOV_EXCL_LINE: gcc-8 is missing this line for no reason

  // offset must be zero for growing axes
  using IsGrowing = has_growing_axis<Axes>;
  std::fill(indices, indices + size, IsGrowing::value ? 0 : offset);
  for_each_axis(axes, [&, stride = static_cast<std::size_t>(1),
                       pshift = shifts](auto& axis) mutable {
    using Axis = std::decay_t<decltype(axis)>;
    maybe_visit(
        index_visitor<Index, Axis, IsGrowing>{axis, stride, start, size, indices, pshift},
        *viter++);
    stride *= static_cast<std::size_t>(axis::traits::extent(axis));
    ++pshift;
  });

  bool update_needed = false;
  for_each_axis(axes, [&update_needed, eit = extents](const auto& a) mutable {
    update_needed |= *eit++ != axis::traits::extent(a);
  });
  if (update_needed) {
    storage_grower<Axes> g(axes);
    g.from_extents(extents);
    g.apply(storage, shifts);
  }
}

template <class S, class Index, class... Ts>
void fill_n_storage(S& s, const Index idx, Ts&&... p) noexcept {
  if (is_valid(idx)) {
    BOOST_ASSERT(idx < s.size());
    fill_storage_element(s[idx], *p.first...);
  }
  fold((p.second ? ++p.first : 0)...);
}

template <class S, class Index, class T, class... Ts>
void fill_n_storage(S& s, const Index idx, weight_type<T>&& w, Ts&&... ps) noexcept {
  if (is_valid(idx)) {
    BOOST_ASSERT(idx < s.size());
    fill_storage_element(s[idx], weight(*w.value.first), *ps.first...);
  }
  if (w.value.second) ++w.value.first;
  fold((ps.second ? ++ps.first : 0)...);
}

// general Nd treatment
template <class Index, class S, class A, class T, class... Ts>
void fill_n_nd(const std::size_t offset, S& storage, A& axes, const std::size_t vsize,
               const T* values, Ts&&... ts) {
  constexpr std::size_t buffer_size = 1ul << 14;
  Index indices[buffer_size];

  /*
    Parallelization options.

    A) Run the whole fill2 method in parallel, each thread fills its own buffer of
    indices, synchronization (atomics) are needed to synchronize the incrementing of
    the storage cells. This leads to a lot of congestion for small histograms.

    B) Run only fill_n_indices in parallel, subsections of the indices buffer
    can be filled by different threads. The final loop that fills the storage runs
    in the main thread, this requires no synchronization for the storage, cells do
    not need to support atomic operations.

    C) Like B), then sort the indices in the main thread and fill the
    storage in parallel, where each thread uses a disjunct set of indices. This
    should create less congestion and requires no synchronization for the storage.

    Note on C): Let's say we have an axis with 5 bins (with *flow to simplify).
    Then after filling 10 values, converting to indices and sorting, the index
    buffer may look like this: 0 0 0 1 2 2 2 4 4 5. Let's use two threads to fill
    the storage. Still in the main thread, we compute an iterator to the middle of
    the index buffer and move it to the right until the pointee changes. Now we have
    two ranges which contain disjunct sets of indices. We pass these ranges to the
    threads which then fill the storage. Since the threads by construction do not
    compete to increment the same cell, no further synchronization is required.

    In all cases, growing axes cannot be parallelized.
  */

  for (std::size_t start = 0; start < vsize; start += buffer_size) {
    const std::size_t n = std::min(buffer_size, vsize - start);
    // fill buffer of indices...
    fill_n_indices(indices, start, n, offset, storage, axes, values);
    // ...and fill corresponding storage cells
    for (auto&& idx : make_span(indices, n))
      fill_n_storage(storage, idx, std::forward<Ts>(ts)...);
  }
}

template <class S, class... As, class T, class... Us>
void fill_n_1(const std::size_t offset, S& storage, std::tuple<As...>& axes,
              const std::size_t vsize, const T* values, Us&&... us) {
  using index_type =
      mp11::mp_if<has_non_inclusive_axis<std::tuple<As...>>, optional_index, std::size_t>;
  fill_n_nd<index_type>(offset, storage, axes, vsize, values, std::forward<Us>(us)...);
}

template <class S, class A, class T, class... Us>
void fill_n_1(const std::size_t offset, S& storage, A& axes, const std::size_t vsize,
              const T* values, Us&&... us) {
  bool all_inclusive = true;
  for_each_axis(axes,
                [&](const auto& ax) { all_inclusive &= axis::traits::inclusive(ax); });
  if (axes_rank(axes) == 1) {
    axis::visit(
        [&](auto& ax) {
          std::tuple<decltype(ax)> axes{ax};
          fill_n_1(offset, storage, axes, vsize, values, std::forward<Us>(us)...);
        },
        axes[0]);
  } else {
    if (all_inclusive)
      fill_n_nd<std::size_t>(offset, storage, axes, vsize, values,
                             std::forward<Us>(us)...);
    else
      fill_n_nd<optional_index>(offset, storage, axes, vsize, values,
                                std::forward<Us>(us)...);
  }
}

template <class A, class T, std::size_t N>
std::size_t get_total_size(const A& axes, const dtl::span<const T, N>& values) {
  // supported cases (T = value type; CT = containter of T; V<T, CT, ...> = variant):
  // - span<CT, N>: for any histogram, N == rank
  // - span<V<T, CT>, N>: for any histogram, N == rank
  BOOST_ASSERT(axes_rank(axes) == values.size());
  constexpr auto unset = static_cast<std::size_t>(-1);
  std::size_t size = unset;
  for_each_axis(axes, [&size, vit = values.begin()](const auto& ax) mutable {
    using AV = axis::traits::value_type<std::decay_t<decltype(ax)>>;
    maybe_visit(
        [&size](const auto& v) {
          // v is either convertible to value or a sequence of values
          using V = std::remove_const_t<std::remove_reference_t<decltype(v)>>;
          static_if_c<(std::is_convertible<decltype(v), AV>::value ||
                       !is_iterable<V>::value)>(
              [](const auto&) {},
              [&size](const auto& v) {
                const auto n = dtl::size(v);
                // must repeat this here for msvc :(
                constexpr auto unset = static_cast<std::size_t>(-1);
                if (size == unset)
                  size = dtl::size(v);
                else if (size != n)
                  BOOST_THROW_EXCEPTION(
                      std::invalid_argument("spans must have compatible lengths"));
              },
              v);
        },
        *vit++);
  });
  // if all arguments are not iterables, return size of 1
  return size == unset ? 1 : size;
}

inline void fill_n_check_extra_args(std::size_t) noexcept {}

template <class T, class... Ts>
void fill_n_check_extra_args(std::size_t size, T&& x, Ts&&... ts) {
  // sequences must have same lengths, but sequences of length 0 are broadcast
  if (x.second != 0 && x.second != size)
    BOOST_THROW_EXCEPTION(std::invalid_argument("spans must have compatible lengths"));
  fill_n_check_extra_args(size, std::forward<Ts>(ts)...);
}

template <class T, class... Ts>
void fill_n_check_extra_args(std::size_t size, weight_type<T>&& w, Ts&&... ts) {
  fill_n_check_extra_args(size, w.value, std::forward<Ts>(ts)...);
}

template <class S, class A, class T, std::size_t N, class... Us>
void fill_n(std::true_type, const std::size_t offset, S& storage, A& axes,
            const dtl::span<const T, N> values, Us&&... us) {
  // supported cases (T = value type; CT = containter of T; V<T, CT, ...> = variant):
  // - span<T, N>: only valid for 1D histogram, N > 1 allowed
  // - span<CT, N>: for any histogram, N == rank
  // - span<V<T, CT>, N>: for any histogram, N == rank
  static_if<is_convertible_to_any_value_type<A, T>>(
      [&](const auto& values, auto&&... us) {
        // T matches one of the axis value types, must be 1D special case
        if (axes_rank(axes) != 1)
          BOOST_THROW_EXCEPTION(
              std::invalid_argument("number of arguments must match histogram rank"));
        fill_n_check_extra_args(values.size(), std::forward<Us>(us)...);
        fill_n_1(offset, storage, axes, values.size(), &values, std::forward<Us>(us)...);
      },
      [&](const auto& values, auto&&... us) {
        // generic ND case
        if (axes_rank(axes) != values.size())
          BOOST_THROW_EXCEPTION(
              std::invalid_argument("number of arguments must match histogram rank"));
        const auto vsize = get_total_size(axes, values);
        fill_n_check_extra_args(vsize, std::forward<Us>(us)...);
        fill_n_1(offset, storage, axes, vsize, values.data(), std::forward<Us>(us)...);
      },
      values, std::forward<Us>(us)...);
}

// empty implementation for bad arguments to stop compiler from showing internals
template <class... Ts>
void fill_n(std::false_type, Ts...) {}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif // BOOST_HISTOGRAM_DETAIL_FILL_N_HPP

/* fill_n.hpp
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
*/