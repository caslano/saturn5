// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_HISTOGRAM_HPP
#define BOOST_HISTOGRAM_HISTOGRAM_HPP

#include <boost/histogram/detail/accumulator_traits.hpp>
#include <boost/histogram/detail/argument_traits.hpp>
#include <boost/histogram/detail/at.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/common_type.hpp>
#include <boost/histogram/detail/fill.hpp>
#include <boost/histogram/detail/fill_n.hpp>
#include <boost/histogram/detail/mutex_base.hpp>
#include <boost/histogram/detail/non_member_container_access.hpp>
#include <boost/histogram/detail/span.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/histogram/sample.hpp>
#include <boost/histogram/storage_adaptor.hpp>
#include <boost/histogram/unsafe_access.hpp>
#include <boost/histogram/weight.hpp>
#include <boost/mp11/integral.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/tuple.hpp>
#include <boost/throw_exception.hpp>
#include <mutex>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace boost {
namespace histogram {

/** Central class of the histogram library.

  Histogram uses the call operator to insert data, like the
  [Boost.Accumulators](https://www.boost.org/doc/libs/develop/doc/html/accumulators.html).

  Use factory functions (see
  [make_histogram.hpp](histogram/reference.html#header.boost.histogram.make_histogram_hpp)
  and
  [make_profile.hpp](histogram/reference.html#header.boost.histogram.make_profile_hpp)) to
  conveniently create histograms rather than calling the ctors directly.

  Use the [indexed](boost/histogram/indexed.html) range generator to iterate over filled
  histograms, which is convenient and faster than hand-written loops for multi-dimensional
  histograms.

  @tparam Axes std::tuple of axis types OR std::vector of an axis type or axis::variant
  @tparam Storage class that implements the storage interface
 */
template <class Axes, class Storage>
class histogram : detail::mutex_base<Axes, Storage> {
  static_assert(std::is_same<std::decay_t<Storage>, Storage>::value,
                "Storage may not be a reference or const or volatile");
  static_assert(mp11::mp_size<Axes>::value > 0, "at least one axis required");

public:
  using axes_type = Axes;
  using storage_type = Storage;
  using value_type = typename storage_type::value_type;
  // typedefs for boost::range_iterator
  using iterator = typename storage_type::iterator;
  using const_iterator = typename storage_type::const_iterator;

private:
  using mutex_base = typename detail::mutex_base<axes_type, storage_type>;

public:
  histogram() = default;

  template <class A, class S>
  explicit histogram(histogram<A, S>&& rhs)
      : storage_(std::move(unsafe_access::storage(rhs)))
      , offset_(unsafe_access::offset(rhs)) {
    detail::axes_assign(axes_, std::move(unsafe_access::axes(rhs)));
    detail::throw_if_axes_is_too_large(axes_);
  }

  template <class A, class S>
  explicit histogram(const histogram<A, S>& rhs)
      : storage_(unsafe_access::storage(rhs)), offset_(unsafe_access::offset(rhs)) {
    detail::axes_assign(axes_, unsafe_access::axes(rhs));
    detail::throw_if_axes_is_too_large(axes_);
  }

  template <class A, class S>
  histogram& operator=(histogram<A, S>&& rhs) {
    detail::axes_assign(axes_, std::move(unsafe_access::axes(rhs)));
    detail::throw_if_axes_is_too_large(axes_);
    storage_ = std::move(unsafe_access::storage(rhs));
    offset_ = unsafe_access::offset(rhs);
    return *this;
  }

  template <class A, class S>
  histogram& operator=(const histogram<A, S>& rhs) {
    detail::axes_assign(axes_, unsafe_access::axes(rhs));
    detail::throw_if_axes_is_too_large(axes_);
    storage_ = unsafe_access::storage(rhs);
    offset_ = unsafe_access::offset(rhs);
    return *this;
  }

  template <class A, class = detail::requires_axes<A>>
  histogram(A&& a, Storage s)
      : axes_(std::forward<A>(a))
      , storage_(std::move(s))
      , offset_(detail::offset(axes_)) {
    detail::throw_if_axes_is_too_large(axes_);
    storage_.reset(detail::bincount(axes_));
  }

  explicit histogram(Axes axes) : histogram(axes, storage_type()) {}

  template <class... As, class = detail::requires_axes<std::tuple<std::decay_t<As>...>>>
  explicit histogram(As&&... as)
      : histogram(std::tuple<std::decay_t<As>...>(std::forward<As>(as)...),
                  storage_type()) {}

  /// Number of axes (dimensions).
  constexpr unsigned rank() const noexcept { return detail::axes_rank(axes_); }

  /// Total number of bins (including underflow/overflow).
  std::size_t size() const noexcept { return storage_.size(); }

  /// Reset all bins to default initialized values.
  void reset() { storage_.reset(size()); }

  /// Get N-th axis using a compile-time number.
  /// This version is more efficient than the one accepting a run-time number.
  template <unsigned N = 0>
  decltype(auto) axis(std::integral_constant<unsigned, N> = {}) const {
    detail::axis_index_is_valid(axes_, N);
    return detail::axis_get<N>(axes_);
  }

  /// Get N-th axis with run-time number.
  /// Prefer the version that accepts a compile-time number, if you can use it.
  decltype(auto) axis(unsigned i) const {
    detail::axis_index_is_valid(axes_, i);
    return detail::axis_get(axes_, i);
  }

  /// Apply unary functor/function to each axis.
  template <class Unary>
  auto for_each_axis(Unary&& unary) const {
    return detail::for_each_axis(axes_, std::forward<Unary>(unary));
  }

  /** Fill histogram with values, an optional weight, and/or a sample.

    Returns iterator to located cell.

    Arguments are passed in order to the axis objects. Passing an argument type that is
    not convertible to the value type accepted by the axis or passing the wrong number
    of arguments causes a throw of `std::invalid_argument`.

    __Optional weight__

    An optional weight can be passed as the first or last argument
    with the [weight](boost/histogram/weight.html) helper function. Compilation fails if
    the storage elements do not support weights.

    __Samples__

    If the storage elements accept samples, pass them with the sample helper function
    in addition to the axis arguments, which can be the first or last argument. The
    [sample](boost/histogram/sample.html) helper function can pass one or more arguments
    to the storage element. If samples and weights are used together, they can be passed
    in any order at the beginning or end of the argument list.

    __Axis with multiple arguments__

    If the histogram contains an axis which accepts a `std::tuple` of arguments, the
    arguments for that axis need to be passed as a `std::tuple`, for example,
    `std::make_tuple(1.2, 2.3)`. If the histogram contains only this axis and no other,
    the arguments can be passed directly.
  */
  template <class T0, class... Ts,
            class = std::enable_if_t<(detail::is_tuple<T0>::value == false ||
                                      sizeof...(Ts) > 0)>>
  iterator operator()(const T0& arg0, const Ts&... args) {
    return operator()(std::forward_as_tuple(arg0, args...));
  }

  /// Fill histogram with values, an optional weight, and/or a sample from a `std::tuple`.
  template <class... Ts>
  iterator operator()(const std::tuple<Ts...>& args) {
    using arg_traits = detail::argument_traits<std::decay_t<Ts>...>;
    using acc_traits = detail::accumulator_traits<value_type>;
    constexpr bool weight_valid =
        arg_traits::wpos::value == -1 || acc_traits::weight_support;
    static_assert(weight_valid, "error: accumulator does not support weights");
    detail::sample_args_passed_vs_expected<typename arg_traits::sargs,
                                           typename acc_traits::args>();
    constexpr bool sample_valid =
        std::is_convertible<typename arg_traits::sargs, typename acc_traits::args>::value;
    std::lock_guard<typename mutex_base::type> guard{mutex_base::get()};
    return detail::fill(mp11::mp_bool<(weight_valid && sample_valid)>{}, arg_traits{},
                        offset_, storage_, axes_, args);
  }

  /** Fill histogram with several values at once.

    The argument must be an iterable with a size that matches the
    rank of the histogram. The element of an iterable may be 1) a value or 2) an iterable
    with contiguous storage over values or 3) a variant of 1) and 2). Sub-iterables must
    have the same length.

    Values are passed to the corresponding histogram axis in order. If a single value is
    passed together with an iterable of values, the single value is treated like an
    iterable with matching length of copies of this value.

    If the histogram has only one axis, an iterable of values may be passed directly.

    @param args iterable as explained in the long description.
  */
  template <class Iterable, class = detail::requires_iterable<Iterable>>
  void fill(const Iterable& args) {
    using acc_traits = detail::accumulator_traits<value_type>;
    constexpr unsigned n_sample_args_expected =
        std::tuple_size<typename acc_traits::args>::value;
    static_assert(n_sample_args_expected == 0,
                  "sample argument is missing but required by accumulator");
    std::lock_guard<typename mutex_base::type> guard{mutex_base::get()};
    detail::fill_n(mp11::mp_bool<(n_sample_args_expected == 0)>{}, offset_, storage_,
                   axes_, detail::make_span(args));
  }

  /** Fill histogram with several values and weights at once.

    @param args iterable of values.
    @param weights single weight or an iterable of weights.
  */
  template <class Iterable, class T, class = detail::requires_iterable<Iterable>>
  void fill(const Iterable& args, const weight_type<T>& weights) {
    using acc_traits = detail::accumulator_traits<value_type>;
    constexpr bool weight_valid = acc_traits::weight_support;
    static_assert(weight_valid, "error: accumulator does not support weights");
    detail::sample_args_passed_vs_expected<std::tuple<>, typename acc_traits::args>();
    constexpr bool sample_valid =
        std::is_convertible<std::tuple<>, typename acc_traits::args>::value;
    std::lock_guard<typename mutex_base::type> guard{mutex_base::get()};
    detail::fill_n(mp11::mp_bool<(weight_valid && sample_valid)>{}, offset_, storage_,
                   axes_, detail::make_span(args),
                   weight(detail::to_ptr_size(weights.value)));
  }

  /** Fill histogram with several values and weights at once.

    @param weights single weight or an iterable of weights.
    @param args iterable of values.
  */
  template <class Iterable, class T, class = detail::requires_iterable<Iterable>>
  void fill(const weight_type<T>& weights, const Iterable& args) {
    fill(args, weights);
  }

  /** Fill histogram with several values and samples at once.

    @param args iterable of values.
    @param samples single sample or an iterable of samples.
  */
  template <class Iterable, class... Ts, class = detail::requires_iterable<Iterable>>
  void fill(const Iterable& args, const sample_type<std::tuple<Ts...>>& samples) {
    using acc_traits = detail::accumulator_traits<value_type>;
    using sample_args_passed =
        std::tuple<decltype(*detail::to_ptr_size(std::declval<Ts>()).first)...>;
    detail::sample_args_passed_vs_expected<sample_args_passed,
                                           typename acc_traits::args>();
    std::lock_guard<typename mutex_base::type> guard{mutex_base::get()};
    mp11::tuple_apply(
        [&](const auto&... sargs) {
          constexpr bool sample_valid =
              std::is_convertible<sample_args_passed, typename acc_traits::args>::value;
          detail::fill_n(mp11::mp_bool<(sample_valid)>{}, offset_, storage_, axes_,
                         detail::make_span(args), detail::to_ptr_size(sargs)...);
        },
        samples.value);
  }

  /** Fill histogram with several values and samples at once.

    @param samples single sample or an iterable of samples.
    @param args iterable of values.
  */
  template <class Iterable, class T, class = detail::requires_iterable<Iterable>>
  void fill(const sample_type<T>& samples, const Iterable& args) {
    fill(args, samples);
  }

  template <class Iterable, class T, class... Ts,
            class = detail::requires_iterable<Iterable>>
  void fill(const Iterable& args, const weight_type<T>& weights,
            const sample_type<std::tuple<Ts...>>& samples) {
    using acc_traits = detail::accumulator_traits<value_type>;
    using sample_args_passed =
        std::tuple<decltype(*detail::to_ptr_size(std::declval<Ts>()).first)...>;
    detail::sample_args_passed_vs_expected<sample_args_passed,
                                           typename acc_traits::args>();
    std::lock_guard<typename mutex_base::type> guard{mutex_base::get()};
    mp11::tuple_apply(
        [&](const auto&... sargs) {
          constexpr bool weight_valid = acc_traits::weight_support;
          static_assert(weight_valid, "error: accumulator does not support weights");
          constexpr bool sample_valid =
              std::is_convertible<sample_args_passed, typename acc_traits::args>::value;
          detail::fill_n(mp11::mp_bool<(weight_valid && sample_valid)>{}, offset_,
                         storage_, axes_, detail::make_span(args),
                         weight(detail::to_ptr_size(weights.value)),
                         detail::to_ptr_size(sargs)...);
        },
        samples.value);
  }

  template <class Iterable, class T, class U, class = detail::requires_iterable<Iterable>>
  void fill(const sample_type<T>& samples, const weight_type<U>& weights,
            const Iterable& args) {
    fill(args, weights, samples);
  }

  template <class Iterable, class T, class U, class = detail::requires_iterable<Iterable>>
  void fill(const weight_type<T>& weights, const sample_type<U>& samples,
            const Iterable& args) {
    fill(args, weights, samples);
  }

  template <class Iterable, class T, class U, class = detail::requires_iterable<Iterable>>
  void fill(const Iterable& args, const sample_type<T>& samples,
            const weight_type<U>& weights) {
    fill(args, weights, samples);
  }

  /** Access cell value at integral indices.

    You can pass indices as individual arguments, as a std::tuple of integers, or as an
    interable range of integers. Passing the wrong number of arguments causes a throw of
    std::invalid_argument. Passing an index which is out of bounds causes a throw of
    std::out_of_range.

    @param i index of first axis.
    @param is indices of second, third, ... axes.
    @returns reference to cell value.
  */
  template <class... Indices>
  decltype(auto) at(axis::index_type i, Indices... is) {
    return at(std::forward_as_tuple(i, is...));
  }

  /// Access cell value at integral indices (read-only).
  template <class... Indices>
  decltype(auto) at(axis::index_type i, Indices... is) const {
    return at(std::forward_as_tuple(i, is...));
  }

  /// Access cell value at integral indices stored in `std::tuple`.
  template <class... Indices>
  decltype(auto) at(const std::tuple<Indices...>& is) {
    if (rank() != sizeof...(Indices))
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("number of arguments != histogram rank"));
    const auto idx = detail::at(axes_, is);
    if (!is_valid(idx))
      BOOST_THROW_EXCEPTION(std::out_of_range("at least one index out of bounds"));
    BOOST_ASSERT(idx < storage_.size());
    return storage_[idx];
  }

  /// Access cell value at integral indices stored in `std::tuple` (read-only).
  template <class... Indices>
  decltype(auto) at(const std::tuple<Indices...>& is) const {
    if (rank() != sizeof...(Indices))
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("number of arguments != histogram rank"));
    const auto idx = detail::at(axes_, is);
    if (!is_valid(idx))
      BOOST_THROW_EXCEPTION(std::out_of_range("at least one index out of bounds"));
    BOOST_ASSERT(idx < storage_.size());
    return storage_[idx];
  }

  /// Access cell value at integral indices stored in iterable.
  template <class Iterable, class = detail::requires_iterable<Iterable>>
  decltype(auto) at(const Iterable& is) {
    if (rank() != detail::axes_rank(is))
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("number of arguments != histogram rank"));
    const auto idx = detail::at(axes_, is);
    if (!is_valid(idx))
      BOOST_THROW_EXCEPTION(std::out_of_range("at least one index out of bounds"));
    BOOST_ASSERT(idx < storage_.size());
    return storage_[idx];
  }

  /// Access cell value at integral indices stored in iterable (read-only).
  template <class Iterable, class = detail::requires_iterable<Iterable>>
  decltype(auto) at(const Iterable& is) const {
    if (rank() != detail::axes_rank(is))
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("number of arguments != histogram rank"));
    const auto idx = detail::at(axes_, is);
    if (!is_valid(idx))
      BOOST_THROW_EXCEPTION(std::out_of_range("at least one index out of bounds"));
    BOOST_ASSERT(idx < storage_.size());
    return storage_[idx];
  }

  /// Access value at index (number for rank = 1, else `std::tuple` or iterable).
  template <class Indices>
  decltype(auto) operator[](const Indices& is) {
    return at(is);
  }

  /// Access value at index (read-only).
  template <class Indices>
  decltype(auto) operator[](const Indices& is) const {
    return at(is);
  }

  /// Equality operator, tests equality for all axes and the storage.
  template <class A, class S>
  bool operator==(const histogram<A, S>& rhs) const noexcept {
    // testing offset is redundant, but offers fast return if it fails
    return offset_ == unsafe_access::offset(rhs) &&
           detail::axes_equal(axes_, unsafe_access::axes(rhs)) &&
           storage_ == unsafe_access::storage(rhs);
  }

  /// Negation of the equality operator.
  template <class A, class S>
  bool operator!=(const histogram<A, S>& rhs) const noexcept {
    return !operator==(rhs);
  }

  /** Add values of another histogram.

    This operator is only available if the value_type supports operator+=.
  */
  template <class A, class S>
#ifdef BOOST_HISTOGRAM_DOXYGEN_INVOKED
  histogram&
#else
  std::enable_if_t<
      detail::has_operator_radd<value_type, typename histogram<A, S>::value_type>::value,
      histogram&>
#endif
  operator+=(const histogram<A, S>& rhs) {
    if (!detail::axes_equal(axes_, unsafe_access::axes(rhs)))
      BOOST_THROW_EXCEPTION(std::invalid_argument("axes of histograms differ"));
    auto rit = unsafe_access::storage(rhs).begin();
    for (auto&& x : storage_) x += *rit++;
    return *this;
  }

  /** Subtract values of another histogram.

    This operator is only available if the value_type supports operator-=.
  */
  template <class A, class S>
#ifdef BOOST_HISTOGRAM_DOXYGEN_INVOKED
  histogram&
#else
  std::enable_if_t<
      detail::has_operator_rsub<value_type, typename histogram<A, S>::value_type>::value,
      histogram&>
#endif
  operator-=(const histogram<A, S>& rhs) {
    if (!detail::axes_equal(axes_, unsafe_access::axes(rhs)))
      BOOST_THROW_EXCEPTION(std::invalid_argument("axes of histograms differ"));
    auto rit = unsafe_access::storage(rhs).begin();
    for (auto&& x : storage_) x -= *rit++;
    return *this;
  }

  /** Multiply by values of another histogram.

    This operator is only available if the value_type supports operator*=.
  */
  template <class A, class S>
#ifdef BOOST_HISTOGRAM_DOXYGEN_INVOKED
  histogram&
#else
  std::enable_if_t<
      detail::has_operator_rmul<value_type, typename histogram<A, S>::value_type>::value,
      histogram&>
#endif
  operator*=(const histogram<A, S>& rhs) {
    if (!detail::axes_equal(axes_, unsafe_access::axes(rhs)))
      BOOST_THROW_EXCEPTION(std::invalid_argument("axes of histograms differ"));
    auto rit = unsafe_access::storage(rhs).begin();
    for (auto&& x : storage_) x *= *rit++;
    return *this;
  }

  /** Divide by values of another histogram.

    This operator is only available if the value_type supports operator/=.
  */
  template <class A, class S>
#ifdef BOOST_HISTOGRAM_DOXYGEN_INVOKED
  histogram&
#else
  std::enable_if_t<
      detail::has_operator_rdiv<value_type, typename histogram<A, S>::value_type>::value,
      histogram&>
#endif
  operator/=(const histogram<A, S>& rhs) {
    if (!detail::axes_equal(axes_, unsafe_access::axes(rhs)))
      BOOST_THROW_EXCEPTION(std::invalid_argument("axes of histograms differ"));
    auto rit = unsafe_access::storage(rhs).begin();
    for (auto&& x : storage_) x /= *rit++;
    return *this;
  }

  /** Multiply all values with a scalar.

    This operator is only available if the value_type supports operator*=.
  */
#ifdef BOOST_HISTOGRAM_DOXYGEN_INVOKED
  histogram&
#else
  template <class V = value_type>
  std::enable_if_t<(detail::has_operator_rmul<V, double>::value), histogram&>
#endif
  operator*=(const double x) {
    // use special storage implementation of scaling if available,
    // else fallback to scaling item by item
    detail::static_if<detail::has_operator_rmul<storage_type, double>>(
        [x](auto& s) { s *= x; },
        [x](auto& s) {
          for (auto&& si : s) si *= x;
        },
        storage_);
    return *this;
  }

  /** Divide all values by a scalar.

    This operator is only available if operator*= is available.
  */
#ifdef BOOST_HISTOGRAM_DOXYGEN_INVOKED
  histogram&
#else
  template <class H = histogram>
  std::enable_if_t<(detail::has_operator_rmul<H, double>::value), histogram&>
#endif
  operator/=(const double x) {
    return operator*=(1.0 / x);
  }

  /// Return value iterator to the beginning of the histogram.
  iterator begin() noexcept { return storage_.begin(); }

  /// Return value iterator to the end in the histogram.
  iterator end() noexcept { return storage_.end(); }

  /// Return value iterator to the beginning of the histogram (read-only).
  const_iterator begin() const noexcept { return storage_.begin(); }

  /// Return value iterator to the end in the histogram (read-only).
  const_iterator end() const noexcept { return storage_.end(); }

  /// Return value iterator to the beginning of the histogram (read-only).
  const_iterator cbegin() const noexcept { return begin(); }

  /// Return value iterator to the end in the histogram (read-only).
  const_iterator cend() const noexcept { return end(); }

  template <class Archive>
  void serialize(Archive& ar, unsigned /* version */) {
    detail::axes_serialize(ar, axes_);
    ar& make_nvp("storage", storage_);
    if (Archive::is_loading::value) {
      offset_ = detail::offset(axes_);
      detail::throw_if_axes_is_too_large(axes_);
    }
  }

private:
  axes_type axes_;
  storage_type storage_;
  std::size_t offset_ = 0;

  friend struct unsafe_access;
};

/**
  Pairwise add cells of two histograms and return histogram with the sum.

  The returned histogram type is the most efficient and safest one constructible from the
  inputs, if they are not the same type. If one histogram has a tuple axis, the result has
  a tuple axis. The chosen storage is the one with the larger dynamic range.
*/
template <class A1, class S1, class A2, class S2>
auto operator+(const histogram<A1, S1>& a, const histogram<A2, S2>& b) {
  auto r = histogram<detail::common_axes<A1, A2>, detail::common_storage<S1, S2>>(a);
  return r += b;
}

/** Pairwise multiply cells of two histograms and return histogram with the product.

  For notes on the returned histogram type, see operator+.
*/
template <class A1, class S1, class A2, class S2>
auto operator*(const histogram<A1, S1>& a, const histogram<A2, S2>& b) {
  auto r = histogram<detail::common_axes<A1, A2>, detail::common_storage<S1, S2>>(a);
  return r *= b;
}

/** Pairwise subtract cells of two histograms and return histogram with the difference.

  For notes on the returned histogram type, see operator+.
*/
template <class A1, class S1, class A2, class S2>
auto operator-(const histogram<A1, S1>& a, const histogram<A2, S2>& b) {
  auto r = histogram<detail::common_axes<A1, A2>, detail::common_storage<S1, S2>>(a);
  return r -= b;
}

/** Pairwise divide cells of two histograms and return histogram with the quotient.

  For notes on the returned histogram type, see operator+.
*/
template <class A1, class S1, class A2, class S2>
auto operator/(const histogram<A1, S1>& a, const histogram<A2, S2>& b) {
  auto r = histogram<detail::common_axes<A1, A2>, detail::common_storage<S1, S2>>(a);
  return r /= b;
}

/** Multiply all cells of the histogram by a number and return a new histogram.

  If the original histogram has integer cells, the result has double cells.
*/
template <class A, class S>
auto operator*(const histogram<A, S>& h, double x) {
  auto r = histogram<A, detail::common_storage<S, dense_storage<double>>>(h);
  return r *= x;
}

/** Multiply all cells of the histogram by a number and return a new histogram.

  If the original histogram has integer cells, the result has double cells.
*/
template <class A, class S>
auto operator*(double x, const histogram<A, S>& h) {
  return h * x;
}

/** Divide all cells of the histogram by a number and return a new histogram.

  If the original histogram has integer cells, the result has double cells.
*/
template <class A, class S>
auto operator/(const histogram<A, S>& h, double x) {
  return h * (1.0 / x);
}

#if __cpp_deduction_guides >= 201606

template <class... Axes, class = detail::requires_axes<std::tuple<std::decay_t<Axes>...>>>
histogram(Axes...)->histogram<std::tuple<std::decay_t<Axes>...>>;

template <class... Axes, class S, class = detail::requires_storage_or_adaptible<S>>
histogram(std::tuple<Axes...>, S)
    ->histogram<std::tuple<Axes...>, std::conditional_t<detail::is_adaptible<S>::value,
                                                        storage_adaptor<S>, S>>;

template <class Iterable, class = detail::requires_iterable<Iterable>,
          class = detail::requires_any_axis<typename Iterable::value_type>>
histogram(Iterable)->histogram<std::vector<typename Iterable::value_type>>;

template <class Iterable, class S, class = detail::requires_iterable<Iterable>,
          class = detail::requires_any_axis<typename Iterable::value_type>,
          class = detail::requires_storage_or_adaptible<S>>
histogram(Iterable, S)
    ->histogram<
        std::vector<typename Iterable::value_type>,
        std::conditional_t<detail::is_adaptible<S>::value, storage_adaptor<S>, S>>;

#endif

} // namespace histogram
} // namespace boost

#endif

/* histogram.hpp
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
*/