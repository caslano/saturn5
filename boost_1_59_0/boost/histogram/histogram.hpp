// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_HISTOGRAM_HPP
#define BOOST_HISTOGRAM_HISTOGRAM_HPP

#include <boost/histogram/detail/accumulator_traits.hpp>
#include <boost/histogram/detail/argument_traits.hpp>
#include <boost/histogram/detail/axes.hpp>
#include <boost/histogram/detail/common_type.hpp>
#include <boost/histogram/detail/fill.hpp>
#include <boost/histogram/detail/fill_n.hpp>
#include <boost/histogram/detail/index_translator.hpp>
#include <boost/histogram/detail/mutex_base.hpp>
#include <boost/histogram/detail/nonmember_container_access.hpp>
#include <boost/histogram/detail/span.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/histogram/indexed.hpp>
#include <boost/histogram/multi_index.hpp>
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
  using multi_index_type = multi_index<detail::relaxed_tuple_size_t<axes_type>::value>;

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
    assert(N < rank());
    return detail::axis_get<N>(axes_);
  }

  /// Get N-th axis with run-time number.
  /// Prefer the version that accepts a compile-time number, if you can use it.
  decltype(auto) axis(unsigned i) const {
    assert(i < rank());
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
    mp11::tuple_apply( // LCOV_EXCL_LINE: gcc-11 is missing this line for no reason
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
    mp11::tuple_apply( // LCOV_EXCL_LINE: gcc-11 is missing this line for no reason
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
  template <class... Is>
  decltype(auto) at(axis::index_type i, Is... is) {
    return at(multi_index_type{i, static_cast<axis::index_type>(is)...});
  }

  /// Access cell value at integral indices (read-only).
  template <class... Is>
  decltype(auto) at(axis::index_type i, Is... is) const {
    return at(multi_index_type{i, static_cast<axis::index_type>(is)...});
  }

  /// Access cell value at integral indices stored in iterable.
  decltype(auto) at(const multi_index_type& is) {
    if (rank() != is.size())
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("number of arguments != histogram rank"));
    const auto idx = detail::linearize_indices(axes_, is);
    if (!is_valid(idx))
      BOOST_THROW_EXCEPTION(std::out_of_range("at least one index out of bounds"));
    assert(idx < storage_.size());
    return storage_[idx];
  }

  /// Access cell value at integral indices stored in iterable (read-only).
  decltype(auto) at(const multi_index_type& is) const {
    if (rank() != is.size())
      BOOST_THROW_EXCEPTION(
          std::invalid_argument("number of arguments != histogram rank"));
    const auto idx = detail::linearize_indices(axes_, is);
    if (!is_valid(idx))
      BOOST_THROW_EXCEPTION(std::out_of_range("at least one index out of bounds"));
    assert(idx < storage_.size());
    return storage_[idx];
  }

  /// Access value at index (for rank = 1).
  decltype(auto) operator[](axis::index_type i) {
    const axis::index_type shift =
        axis::traits::options(axis()) & axis::option::underflow ? 1 : 0;
    return storage_[static_cast<std::size_t>(i + shift)];
  }

  /// Access value at index (for rank = 1, read-only).
  decltype(auto) operator[](axis::index_type i) const {
    const axis::index_type shift =
        axis::traits::options(axis()) & axis::option::underflow ? 1 : 0;
    return storage_[static_cast<std::size_t>(i + shift)];
  }

  /// Access value at index tuple.
  decltype(auto) operator[](const multi_index_type& is) {
    return storage_[detail::linearize_indices(axes_, is)];
  }

  /// Access value at index tuple (read-only).
  decltype(auto) operator[](const multi_index_type& is) const {
    return storage_[detail::linearize_indices(axes_, is)];
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

    Both histograms must be compatible to be addable. The histograms are compatible, if
    the axes are either all identical. If the axes only differ in the states of their
    discrete growing axis types, then they are also compatible. The discrete growing
    axes are merged in this case.
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

  // specialization that allows axes merging
  template <class S>
#ifdef BOOST_HISTOGRAM_DOXYGEN_INVOKED
  histogram&
#else
  std::enable_if_t<detail::has_operator_radd<
                       value_type, typename histogram<axes_type, S>::value_type>::value,
                   histogram&>
#endif
  operator+=(const histogram<axes_type, S>& rhs) {
    const auto& raxes = unsafe_access::axes(rhs);
    if (detail::axes_equal(axes_, unsafe_access::axes(rhs))) {
      auto rit = unsafe_access::storage(rhs).begin();
      for (auto&& x : storage_) x += *rit++;
      return *this;
    }

    if (rank() != detail::axes_rank(raxes))
      BOOST_THROW_EXCEPTION(std::invalid_argument("axes have different length"));
    auto h = histogram<axes_type, storage_type>(
        detail::axes_transform(axes_, raxes, detail::axis_merger{}),
        detail::make_default(storage_));
    const auto& axes = unsafe_access::axes(h);
    const auto tr1 = detail::make_index_translator(axes, axes_);
    for (auto&& x : indexed(*this, coverage::all)) h[tr1(x.indices())] += *x;
    const auto tr2 = detail::make_index_translator(axes, raxes);
    for (auto&& x : indexed(rhs, coverage::all)) h[tr2(x.indices())] += *x;
    *this = std::move(h);
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
histogram(Axes...) -> histogram<std::tuple<std::decay_t<Axes>...>>;

template <class... Axes, class S, class = detail::requires_storage_or_adaptible<S>>
histogram(std::tuple<Axes...>, S)
    -> histogram<std::tuple<Axes...>, std::conditional_t<detail::is_adaptible<S>::value,
                                                         storage_adaptor<S>, S>>;

template <class Iterable, class = detail::requires_iterable<Iterable>,
          class = detail::requires_any_axis<typename Iterable::value_type>>
histogram(Iterable) -> histogram<std::vector<typename Iterable::value_type>>;

template <class Iterable, class S, class = detail::requires_iterable<Iterable>,
          class = detail::requires_any_axis<typename Iterable::value_type>,
          class = detail::requires_storage_or_adaptible<S>>
histogram(Iterable, S) -> histogram<
    std::vector<typename Iterable::value_type>,
    std::conditional_t<detail::is_adaptible<S>::value, storage_adaptor<S>, S>>;

#endif

} // namespace histogram
} // namespace boost

#endif

/* histogram.hpp
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
*/