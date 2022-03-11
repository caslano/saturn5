// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_AXES_HPP
#define BOOST_HISTOGRAM_DETAIL_AXES_HPP

#include <array>
#include <boost/assert.hpp>
#include <boost/core/nvp.hpp>
#include <boost/histogram/axis/traits.hpp>
#include <boost/histogram/axis/variant.hpp>
#include <boost/histogram/detail/make_default.hpp>
#include <boost/histogram/detail/optional_index.hpp>
#include <boost/histogram/detail/static_if.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/tuple.hpp>
#include <boost/mp11/utility.hpp>
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>

/* Most of the histogram code is generic and works for any number of axes. Buffers with a
 * fixed maximum capacity are used in some places, which have a size equal to the rank of
 * a histogram. The buffers are statically allocated to improve performance, which means
 * that they need a preset maximum capacity. 32 seems like a safe upper limit for the rank
 * (you can nevertheless increase it here if necessary): the simplest non-trivial axis has
 * 2 bins; even if counters are used which need only a byte of storage per bin, this still
 * corresponds to 4 GB of storage.
 */
#ifndef BOOST_HISTOGRAM_DETAIL_AXES_LIMIT
#define BOOST_HISTOGRAM_DETAIL_AXES_LIMIT 32
#endif

namespace boost {
namespace histogram {
namespace detail {

template <class T>
unsigned axes_rank(const T& axes) {
  using std::begin;
  using std::end;
  return static_cast<unsigned>(std::distance(begin(axes), end(axes)));
}

template <class... Ts>
constexpr unsigned axes_rank(const std::tuple<Ts...>&) {
  return static_cast<unsigned>(sizeof...(Ts));
}

template <class T>
void throw_if_axes_is_too_large(const T& axes) {
  if (axes_rank(axes) > BOOST_HISTOGRAM_DETAIL_AXES_LIMIT)
    BOOST_THROW_EXCEPTION(
        std::invalid_argument("length of axis vector exceeds internal buffers, "
                              "recompile with "
                              "-DBOOST_HISTOGRAM_DETAIL_AXES_LIMIT=<new max size> "
                              "to increase internal buffers"));
}

// tuple is never too large because internal buffers adapt to size of tuple
template <class... Ts>
void throw_if_axes_is_too_large(const std::tuple<Ts...>&) {}

template <unsigned N, class... Ts>
decltype(auto) axis_get(std::tuple<Ts...>& axes) {
  return std::get<N>(axes);
}

template <unsigned N, class... Ts>
decltype(auto) axis_get(const std::tuple<Ts...>& axes) {
  return std::get<N>(axes);
}

template <unsigned N, class T>
decltype(auto) axis_get(T& axes) {
  return axes[N];
}

template <unsigned N, class T>
decltype(auto) axis_get(const T& axes) {
  return axes[N];
}

template <class... Ts>
auto axis_get(std::tuple<Ts...>& axes, const unsigned i) {
  constexpr auto S = sizeof...(Ts);
  using V = mp11::mp_unique<axis::variant<Ts*...>>;
  return mp11::mp_with_index<S>(i, [&axes](auto i) { return V(&std::get<i>(axes)); });
}

template <class... Ts>
auto axis_get(const std::tuple<Ts...>& axes, const unsigned i) {
  constexpr auto S = sizeof...(Ts);
  using V = mp11::mp_unique<axis::variant<const Ts*...>>;
  return mp11::mp_with_index<S>(i, [&axes](auto i) { return V(&std::get<i>(axes)); });
}

template <class T>
decltype(auto) axis_get(T& axes, const unsigned i) {
  return axes[i];
}

template <class T>
decltype(auto) axis_get(const T& axes, const unsigned i) {
  return axes[i];
}

template <class... Ts, class... Us>
bool axes_equal(const std::tuple<Ts...>& ts, const std::tuple<Us...>& us) {
  using namespace ::boost::mp11;
  return static_if<std::is_same<mp_list<Ts...>, mp_list<Us...>>>(
      [](const auto& ts, const auto& us) {
        using N = mp_size<std::decay_t<decltype(ts)>>;
        bool equal = true;
        mp_for_each<mp_iota<N>>(
            [&](auto I) { equal &= relaxed_equal(std::get<I>(ts), std::get<I>(us)); });
        return equal;
      },
      [](const auto&, const auto&) { return false; }, ts, us);
}

template <class T, class... Us>
bool axes_equal(const T& t, const std::tuple<Us...>& u) {
  using namespace ::boost::mp11;
  if (t.size() != sizeof...(Us)) return false;
  bool equal = true;
  mp_for_each<mp_iota_c<sizeof...(Us)>>([&](auto I) { equal &= t[I] == std::get<I>(u); });
  return equal;
}

template <class... Ts, class U>
bool axes_equal(const std::tuple<Ts...>& t, const U& u) {
  return axes_equal(u, t);
}

template <class T, class U>
bool axes_equal(const T& t, const U& u) {
  if (t.size() != u.size()) return false;
  return std::equal(t.begin(), t.end(), u.begin());
}

template <class... Ts, class... Us>
void axes_assign(std::tuple<Ts...>& t, const std::tuple<Us...>& u) {
  using namespace ::boost::mp11;
  static_if<std::is_same<mp_list<Ts...>, mp_list<Us...>>>(
      [](auto& a, const auto& b) { a = b; },
      [](auto&, const auto&) {
        BOOST_THROW_EXCEPTION(
            std::invalid_argument("cannot assign axes, types do not match"));
      },
      t, u);
}

template <class... Ts, class U>
void axes_assign(std::tuple<Ts...>& t, const U& u) {
  using namespace ::boost::mp11;
  mp_for_each<mp_iota_c<sizeof...(Ts)>>([&](auto I) {
    using T = mp_at_c<std::tuple<Ts...>, I>;
    std::get<I>(t) = axis::get<T>(u[I]);
  });
}

template <class T, class... Us>
void axes_assign(T& t, const std::tuple<Us...>& u) {
  // resize instead of reserve, because t may not be empty and we want exact capacity
  t.resize(sizeof...(Us));
  using namespace ::boost::mp11;
  mp_for_each<mp_iota_c<sizeof...(Us)>>([&](auto I) { t[I] = std::get<I>(u); });
}

template <class T, class U>
void axes_assign(T& t, const U& u) {
  t.assign(u.begin(), u.end());
}

template <class Archive, class T>
void axes_serialize(Archive& ar, T& axes) {
  ar& make_nvp("axes", axes);
}

template <class Archive, class... Ts>
void axes_serialize(Archive& ar, std::tuple<Ts...>& axes) {
  // needed to keep serialization format backward compatible
  struct proxy {
    std::tuple<Ts...>& t;
    void serialize(Archive& ar, unsigned /* version */) {
      mp11::tuple_for_each(t, [&ar](auto& x) { ar& make_nvp("item", x); });
    }
  };
  proxy p{axes};
  ar& make_nvp("axes", p);
}

// create empty dynamic axis which can store any axes types from the argument
template <class T>
auto make_empty_dynamic_axes(const T& axes) {
  return make_default(axes);
}

template <class... Ts>
auto make_empty_dynamic_axes(const std::tuple<Ts...>&) {
  using namespace ::boost::mp11;
  using L = mp_unique<axis::variant<Ts...>>;
  // return std::vector<axis::variant<Axis0, Axis1, ...>> or std::vector<Axis0>
  return std::vector<mp_if_c<(mp_size<L>::value == 1), mp_first<L>, L>>{};
}

template <class T>
void axis_index_is_valid(const T& axes, const unsigned N) {
  BOOST_ASSERT_MSG(N < axes_rank(axes), "index out of range");
}

template <class Axes, class V>
void for_each_axis_impl(std::true_type, Axes&& axes, V&& v) {
  for (auto&& a : axes) { axis::visit(std::forward<V>(v), a); }
}

template <class Axes, class V>
void for_each_axis_impl(std::false_type, Axes&& axes, V&& v) {
  for (auto&& a : axes) std::forward<V>(v)(a);
}

template <class Axes, class V>
void for_each_axis(Axes&& a, V&& v) {
  using namespace ::boost::mp11;
  using T = mp_first<std::decay_t<Axes>>;
  for_each_axis_impl(is_axis_variant<T>(), std::forward<Axes>(a), std::forward<V>(v));
}

template <class V, class... Axis>
void for_each_axis(const std::tuple<Axis...>& a, V&& v) {
  mp11::tuple_for_each(a, std::forward<V>(v));
}

template <class V, class... Axis>
void for_each_axis(std::tuple<Axis...>& a, V&& v) {
  mp11::tuple_for_each(a, std::forward<V>(v));
}

// total number of bins including *flow bins
template <class T>
std::size_t bincount(const T& axes) {
  std::size_t n = 1;
  for_each_axis(axes, [&n](const auto& a) {
    const auto old = n;
    const auto s = axis::traits::extent(a);
    n *= s;
    if (s > 0 && n < old) BOOST_THROW_EXCEPTION(std::overflow_error("bincount overflow"));
  });
  return n;
}

// initial offset for the linear index
template <class T>
std::size_t offset(const T& axes) {
  std::size_t n = 0;
  for_each_axis(axes, [&n, stride = static_cast<std::size_t>(1)](const auto& a) mutable {
    if (axis::traits::options(a) & axis::option::growth)
      n = invalid_index;
    else if (n != invalid_index && axis::traits::options(a) & axis::option::underflow)
      n += stride;
    stride *= axis::traits::extent(a);
  });
  return n;
}

template <class T>
using buffer_size_impl = typename std::tuple_size<T>::type;

template <class T>
using buffer_size = mp11::mp_eval_or<
    std::integral_constant<std::size_t, BOOST_HISTOGRAM_DETAIL_AXES_LIMIT>,
    buffer_size_impl, T>;

template <class T, std::size_t N>
class sub_array : public std::array<T, N> {
  using base_type = std::array<T, N>;

public:
  explicit sub_array(std::size_t s) noexcept(
      std::is_nothrow_default_constructible<T>::value)
      : size_(s) {
    BOOST_ASSERT_MSG(size_ <= N, "requested size exceeds size of static buffer");
  }

  sub_array(std::size_t s,
            const T& value) noexcept(std::is_nothrow_copy_constructible<T>::value)
      : size_(s) {
    BOOST_ASSERT_MSG(size_ <= N, "requested size exceeds size of static buffer");
    std::array<T, N>::fill(value);
  }

  // need to override both versions of std::array
  auto end() noexcept { return base_type::begin() + size_; }
  auto end() const noexcept { return base_type::begin() + size_; }

  auto size() const noexcept { return size_; }

private:
  std::size_t size_;
};

template <class U, class T>
using stack_buffer = sub_array<U, buffer_size<T>::value>;

// make default-constructed buffer (no initialization for POD types)
template <class U, class T>
auto make_stack_buffer(const T& t) {
  return stack_buffer<U, T>(axes_rank(t));
}

// make buffer with elements initialized to v
template <class U, class T, class V>
auto make_stack_buffer(const T& t, V&& v) {
  return stack_buffer<U, T>(axes_rank(t), std::forward<V>(v));
}

template <class T>
using has_underflow =
    decltype(axis::traits::get_options<T>::test(axis::option::underflow));

template <class T>
using is_growing = decltype(axis::traits::get_options<T>::test(axis::option::growth));

template <class T>
using is_not_inclusive = mp11::mp_not<axis::traits::is_inclusive<T>>;

// for vector<T>
template <class T>
struct axis_types_impl {
  using type = mp11::mp_list<std::decay_t<T>>;
};

// for vector<variant<Ts...>>
template <class... Ts>
struct axis_types_impl<axis::variant<Ts...>> {
  using type = mp11::mp_list<std::decay_t<Ts>...>;
};

// for tuple<Ts...>
template <class... Ts>
struct axis_types_impl<std::tuple<Ts...>> {
  using type = mp11::mp_list<std::decay_t<Ts>...>;
};

template <class T>
using axis_types =
    typename axis_types_impl<mp11::mp_if<is_vector_like<T>, mp11::mp_first<T>, T>>::type;

template <template <class> class Trait, class Axes>
using has_special_axis = mp11::mp_any_of<axis_types<Axes>, Trait>;

template <class Axes>
using has_growing_axis = mp11::mp_any_of<axis_types<Axes>, is_growing>;

template <class Axes>
using has_non_inclusive_axis = mp11::mp_any_of<axis_types<Axes>, is_not_inclusive>;

template <class T>
constexpr std::size_t type_score() {
  return sizeof(T) *
         (std::is_integral<T>::value ? 1 : std::is_floating_point<T>::value ? 10 : 100);
}

// arbitrary ordering of types
template <class T, class U>
using type_less = mp11::mp_bool<(type_score<T>() < type_score<U>())>;

template <class Axes>
using value_types = mp11::mp_sort<
    mp11::mp_unique<mp11::mp_transform<axis::traits::value_type, axis_types<Axes>>>,
    type_less>;

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* axes.hpp
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
*/