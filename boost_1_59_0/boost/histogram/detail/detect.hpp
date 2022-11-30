// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_DETECT_HPP
#define BOOST_HISTOGRAM_DETAIL_DETECT_HPP

#include <boost/histogram/fwd.hpp>
#include <boost/mp11/function.hpp> // mp_and, mp_or
#include <boost/mp11/integral.hpp> // mp_not
#include <boost/mp11/list.hpp>     // mp_first
#include <iterator>
#include <tuple>
#include <type_traits>

// forward declaration
namespace boost {
namespace variant2 {
template <class...>
class variant;
} // namespace variant2
} // namespace boost

namespace boost {
namespace histogram {
namespace detail {

template <class...>
using void_t = void;

struct detect_base {
  template <class T>
  static T&& val();
  template <class T>
  static T& ref();
  template <class T>
  static T const& cref();
};

#define BOOST_HISTOGRAM_DETAIL_DETECT(name, cond)       \
  template <class U>                                    \
  struct name##_impl : detect_base {                    \
    template <class T>                                  \
    static mp11::mp_true test(T& t, decltype(cond, 0)); \
    template <class T>                                  \
    static mp11::mp_false test(T&, float);              \
    using type = decltype(test<U>(ref<U>(), 0));        \
  };                                                    \
  template <class T>                                    \
  using name = typename name##_impl<T>::type

#define BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(name, cond)      \
  template <class V, class W>                                 \
  struct name##_impl : detect_base {                          \
    template <class T, class U>                               \
    static mp11::mp_true test(T& t, U& u, decltype(cond, 0)); \
    template <class T, class U>                               \
    static mp11::mp_false test(T&, U&, float);                \
    using type = decltype(test<V, W>(ref<V>(), ref<W>(), 0)); \
  };                                                          \
  template <class T, class U = T>                             \
  using name = typename name##_impl<T, U>::type

// reset has overloads, trying to get pmf in this case always fails
BOOST_HISTOGRAM_DETAIL_DETECT(has_method_reset, t.reset(0));

BOOST_HISTOGRAM_DETAIL_DETECT(is_indexable, t[0]);

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(is_transform, (t.inverse(t.forward(u))));

BOOST_HISTOGRAM_DETAIL_DETECT(is_indexable_container,
                              (t[0], t.size(), std::begin(t), std::end(t)));

BOOST_HISTOGRAM_DETAIL_DETECT(is_vector_like,
                              (t[0], t.size(), t.resize(0), std::begin(t), std::end(t)));

BOOST_HISTOGRAM_DETAIL_DETECT(is_array_like, (t[0], t.size(), std::tuple_size<T>::value,
                                              std::begin(t), std::end(t)));

BOOST_HISTOGRAM_DETAIL_DETECT(is_map_like, ((typename T::key_type*)nullptr,
                                            (typename T::mapped_type*)nullptr,
                                            std::begin(t), std::end(t)));

// ok: is_axis is false for axis::variant, because T::index is templated
BOOST_HISTOGRAM_DETAIL_DETECT(is_axis, (t.size(), &T::index));

BOOST_HISTOGRAM_DETAIL_DETECT(is_iterable, (std::begin(t), std::end(t)));

BOOST_HISTOGRAM_DETAIL_DETECT(is_iterator,
                              (typename std::iterator_traits<T>::iterator_category{}));

BOOST_HISTOGRAM_DETAIL_DETECT(is_streamable, (std::declval<std::ostream&>() << t));

BOOST_HISTOGRAM_DETAIL_DETECT(has_operator_preincrement, ++t);

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_operator_equal, (cref<T>() == u));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_operator_radd, (t += u));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_operator_rsub, (t -= u));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_operator_rmul, (t *= u));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_operator_rdiv, (t /= u));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_method_eq, (cref<T>().operator==(u)));

BOOST_HISTOGRAM_DETAIL_DETECT(has_threading_support, (T::has_threading_support));

// stronger form of std::is_convertible that works with explicit operator T and ctors
BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(is_explicitly_convertible, static_cast<U>(t));

BOOST_HISTOGRAM_DETAIL_DETECT(is_complete, sizeof(T));

template <class T>
using is_storage = mp11::mp_and<is_indexable_container<T>, has_method_reset<T>,
                                has_threading_support<T>>;

template <class T>
using is_adaptible =
    mp11::mp_and<mp11::mp_not<is_storage<T>>,
                 mp11::mp_or<is_vector_like<T>, is_array_like<T>, is_map_like<T>>>;

template <class T>
struct is_tuple_impl : std::false_type {};

template <class... Ts>
struct is_tuple_impl<std::tuple<Ts...>> : std::true_type {};

template <class T>
using is_tuple = typename is_tuple_impl<T>::type;

template <class T>
struct is_variant_impl : std::false_type {};

template <class... Ts>
struct is_variant_impl<boost::variant2::variant<Ts...>> : std::true_type {};

template <class T>
using is_variant = typename is_variant_impl<T>::type;

template <class T>
struct is_axis_variant_impl : std::false_type {};

template <class... Ts>
struct is_axis_variant_impl<axis::variant<Ts...>> : std::true_type {};

template <class T>
using is_axis_variant = typename is_axis_variant_impl<T>::type;

template <class T>
using is_any_axis = mp11::mp_or<is_axis<T>, is_axis_variant<T>>;

template <class T>
using is_sequence_of_axis = mp11::mp_and<is_iterable<T>, is_axis<mp11::mp_first<T>>>;

template <class T>
using is_sequence_of_axis_variant =
    mp11::mp_and<is_iterable<T>, is_axis_variant<mp11::mp_first<T>>>;

template <class T>
using is_sequence_of_any_axis =
    mp11::mp_and<is_iterable<T>, is_any_axis<mp11::mp_first<T>>>;

// poor-mans concept checks
template <class T, class = std::enable_if_t<is_storage<std::decay_t<T>>::value>>
struct requires_storage {};

template <class T, class _ = std::decay_t<T>,
          class = std::enable_if_t<(is_storage<_>::value || is_adaptible<_>::value)>>
struct requires_storage_or_adaptible {};

template <class T, class = std::enable_if_t<is_iterator<std::decay_t<T>>::value>>
struct requires_iterator {};

template <class T, class = std::enable_if_t<
                       is_iterable<std::remove_cv_t<std::remove_reference_t<T>>>::value>>
struct requires_iterable {};

template <class T, class = std::enable_if_t<is_axis<std::decay_t<T>>::value>>
struct requires_axis {};

template <class T, class = std::enable_if_t<is_any_axis<std::decay_t<T>>::value>>
struct requires_any_axis {};

template <class T, class = std::enable_if_t<is_sequence_of_axis<std::decay_t<T>>::value>>
struct requires_sequence_of_axis {};

template <class T,
          class = std::enable_if_t<is_sequence_of_axis_variant<std::decay_t<T>>::value>>
struct requires_sequence_of_axis_variant {};

template <class T,
          class = std::enable_if_t<is_sequence_of_any_axis<std::decay_t<T>>::value>>
struct requires_sequence_of_any_axis {};

template <class T,
          class = std::enable_if_t<is_any_axis<mp11::mp_first<std::decay_t<T>>>::value>>
struct requires_axes {};

template <class T, class U,
          class = std::enable_if_t<is_transform<std::decay_t<T>, U>::value>>
struct requires_transform {};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* detect.hpp
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
*/