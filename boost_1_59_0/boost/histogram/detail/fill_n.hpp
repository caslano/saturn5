// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_FILL_N_HPP
#define BOOST_HISTOGRAM_DETAIL_FILL_N_HPP

#include <algorithm>
#include <boost/histogram/axis/option.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/fill.hpp>
#include <boost/histogram/detail/linearize.hpp>
#include <boost/histogram/detail/nonmember_container_access.hpp>
#include <boost/histogram/detail/optional_index.hpp>
#include <boost/histogram/detail/span.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/bind.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/throw_exception.hpp>
#include <boost/variant2/variant.hpp>
#include <cassert>
#include <initializer_list>
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

    // Optimization: We call call_2 only once and then add the index shift onto the
    // whole array of indices, because it is always the same. This also works if the
    // axis grows during this operation. There are no shifts to apply if the zero-point
    // changes.
    const auto before = *begin_;
    call_2(IsGrowing{}, begin_, value);
    if (is_valid(*begin_)) {
      // since index can be std::size_t or optional_index, must do conversion here
      const auto delta =
          static_cast<std::intptr_t>(*begin_) - static_cast<std::intptr_t>(before);
      for (auto it = begin_ + 1; it != begin_ + size_; ++it) *it += delta;
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

  // TODO this seems to always take the path for growing axes, even if Axes is vector
  // of variant and types actually held are not growing axes?
  // index offset must be zero for growing axes
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
    assert(idx < s.size());
    fill_storage_element(s[idx], *p.first...);
  }
  // operator folding emulation
  (void)std::initializer_list<int>{(p.second ? (++p.first, 0) : 0)...};
}

template <class S, class Index, class T, class... Ts>
void fill_n_storage(S& s, const Index idx, weight_type<T>&& w, Ts&&... ps) noexcept {
  if (is_valid(idx)) {
    assert(idx < s.size());
    fill_storage_element(s[idx], weight(*w.value.first), *ps.first...);
  }
  if (w.value.second) ++w.value.first;
  // operator folding emulation
  (void)std::initializer_list<int>{(ps.second ? (++ps.first, 0) : 0)...};
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
    // Optimization: benchmark shows that this makes filling dynamic 1D histogram faster
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
  assert(axes_rank(axes) == values.size());
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