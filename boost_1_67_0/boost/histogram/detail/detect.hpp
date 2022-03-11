// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_DETECT_HPP
#define BOOST_HISTOGRAM_DETAIL_DETECT_HPP

#include <boost/histogram/fwd.hpp>
#include <boost/mp11/algorithm.hpp>
#include <boost/mp11/function.hpp>
#include <boost/mp11/utility.hpp>
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

#define BOOST_HISTOGRAM_DETAIL_DETECT(name, cond) \
  template <class T>                              \
  using name##_impl = decltype(cond);             \
  template <class T>                              \
  using name = typename boost::mp11::mp_valid<name##_impl, T>::type

#define BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(name, cond) \
  template <class T, class U>                            \
  using name##_impl = decltype(cond);                    \
  template <class T, class U = T>                        \
  using name = typename boost::mp11::mp_valid<name##_impl, T, U>::type

// metadata has overloads, trying to get pmf in this case always fails
BOOST_HISTOGRAM_DETAIL_DETECT(has_method_metadata, (std::declval<T&>().metadata()));

// resize has overloads, trying to get pmf in this case always fails
BOOST_HISTOGRAM_DETAIL_DETECT(has_method_resize, (std::declval<T&>().resize(0)));

BOOST_HISTOGRAM_DETAIL_DETECT(has_method_size, &T::size);

BOOST_HISTOGRAM_DETAIL_DETECT(has_method_clear, &T::clear);

BOOST_HISTOGRAM_DETAIL_DETECT(has_method_lower, &T::lower);

BOOST_HISTOGRAM_DETAIL_DETECT(has_method_value, &T::value);

BOOST_HISTOGRAM_DETAIL_DETECT(has_method_update, &T::update);

// reset has overloads, trying to get pmf in this case always fails
BOOST_HISTOGRAM_DETAIL_DETECT(has_method_reset, (std::declval<T>().reset(0)));

BOOST_HISTOGRAM_DETAIL_DETECT(has_method_options, &T::options);

BOOST_HISTOGRAM_DETAIL_DETECT(has_allocator, &T::get_allocator);

BOOST_HISTOGRAM_DETAIL_DETECT(is_indexable, (std::declval<T&>()[0]));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(
    is_transform,
    (std::declval<T&>().inverse(std::declval<T&>().forward(std::declval<U>()))));

BOOST_HISTOGRAM_DETAIL_DETECT(is_indexable_container, (std::declval<T>()[0], &T::size,
                                                       std::begin(std::declval<T>()),
                                                       std::end(std::declval<T>())));

BOOST_HISTOGRAM_DETAIL_DETECT(is_vector_like,
                              (std::declval<T>()[0], &T::size,
                               std::declval<T>().resize(0), std::begin(std::declval<T>()),
                               std::end(std::declval<T>())));

BOOST_HISTOGRAM_DETAIL_DETECT(is_array_like,
                              (std::declval<T>()[0], &T::size, std::tuple_size<T>::value,
                               std::begin(std::declval<T>()),
                               std::end(std::declval<T>())));

BOOST_HISTOGRAM_DETAIL_DETECT(is_map_like, (std::declval<typename T::key_type>(),
                                            std::declval<typename T::mapped_type>(),
                                            std::begin(std::declval<T>()),
                                            std::end(std::declval<T>())));

// ok: is_axis is false for axis::variant, because T::index is templated
BOOST_HISTOGRAM_DETAIL_DETECT(is_axis, (&T::size, &T::index));

BOOST_HISTOGRAM_DETAIL_DETECT(is_iterable, (std::begin(std::declval<T&>()),
                                            std::end(std::declval<T&>())));

BOOST_HISTOGRAM_DETAIL_DETECT(is_iterator,
                              (typename std::iterator_traits<T>::iterator_category()));

BOOST_HISTOGRAM_DETAIL_DETECT(is_streamable,
                              (std::declval<std::ostream&>() << std::declval<T&>()));

BOOST_HISTOGRAM_DETAIL_DETECT(has_operator_preincrement, (++std::declval<T&>()));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_operator_equal, (std::declval<const T&>() ==
                                                          std::declval<const U>()));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_operator_radd,
                                     (std::declval<T&>() += std::declval<U>()));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_operator_rsub,
                                     (std::declval<T&>() -= std::declval<U>()));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_operator_rmul,
                                     (std::declval<T&>() *= std::declval<U>()));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(has_operator_rdiv,
                                     (std::declval<T&>() /= std::declval<U>()));

BOOST_HISTOGRAM_DETAIL_DETECT_BINARY(
    has_method_eq, (std::declval<const T>().operator==(std::declval<const U>())));

BOOST_HISTOGRAM_DETAIL_DETECT(has_threading_support, (T::has_threading_support));

template <class T>
using is_storage = mp11::mp_and<is_indexable_container<T>, has_method_reset<T>,
                                has_threading_support<T>>;

template <class T>
using is_adaptible =
    mp11::mp_and<mp11::mp_not<is_storage<T>>,
                 mp11::mp_or<is_vector_like<T>, is_array_like<T>, is_map_like<T>>>;

template <class T>
struct is_tuple_impl : mp11::mp_false {};

template <class... Ts>
struct is_tuple_impl<std::tuple<Ts...>> : mp11::mp_true {};

template <class T>
using is_tuple = typename is_tuple_impl<T>::type;

template <class T>
struct is_variant_impl : mp11::mp_false {};

template <class... Ts>
struct is_variant_impl<boost::variant2::variant<Ts...>> : mp11::mp_true {};

template <class T>
using is_variant = typename is_variant_impl<T>::type;

template <class T>
struct is_axis_variant_impl : mp11::mp_false {};

template <class... Ts>
struct is_axis_variant_impl<axis::variant<Ts...>> : mp11::mp_true {};

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

template <class T, class U, class = std::enable_if_t<std::is_convertible<T, U>::value>>
struct requires_convertible {};

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