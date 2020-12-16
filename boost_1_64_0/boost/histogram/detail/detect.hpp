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
rB2R9UNSiDWPTQV9IsjBKTsBlqI6c1QaMsjj1FPqh2ToyydT3Nh0xE2qH9KlfqzzS7wtK0ZegKd3fHB9qvxxyJ90+eOyyBnehqkkKbDdqeZ2q/GQJAWBq92ASUV4SgxMsnqw46HvYWREkFmATENg5xjITurBEQuZDUgnArvEQGaoh/RYyJxTlCU6+mjdgACt8WbIhIeWYPPCrf0Oz83Js/CXcZE823gSWxAfGfAAXp3+xubku02I+cZTm7Nrcj2nvl+l+eEhSvMwZX+fdM544iqzfTX70LzReWvoE+eORhGA1I6c7XljeVumN+JOQCBLi1n/hTTR8zRFUNGUkvqmBC925VqsThqcoMAinIeZwEvJYuxtuF8ivRDphLrRSa6c2zNc2o+pAcuFaRi3IPlxhMARDImwg39Ora321ZaInz+tmot1cP91tAE04I1vIO2Pm8wIASaaLZ6FWC/9zGWFHeo+Noldca20Q9IzCPWPEp6druTfUdr+hGq/foBGvw2M99FleEd++QgoDTK8syt4L+5wQN2nFy5NdpVZZGdSAObKUMHy9cKG0dfp5kYrnInZWmSycPdHCYrvDLij86AWZ2XoMQrgq2FvuvHGG/e3hg7a9LbQ7j62tgb74tC2pIIWT+OCVc6fNdpW2kSQq4ZZhZrUxWjI2hA3hNyMKbcJpEyje+9JHnrOTX3Z7tb31FicY/aK27CBXOUV52Ef0VAO30saaTd5vED4Wypc+khqeIrrv3vBrjl99ZUFKyAAExkD8A9RQFKNVzN5hx0+E6AhClAonVW4fTj0MiManEkFO8gfHsAnR8OPsFWOUaGcPWY46TgjgLbt9qwKIjvsQJ9t3I+SXjikiAtuqLR6Ioxg5+h23OjyIa12GQc09QdWuAPCjbSsbRsE6dC5aBvULAZKexgoHSzNtMzzrU5XBlGGZ9Xzdn6jSyycH7c4u3Lwjfej/NKGkdaieS/gNbDTWre7DcSUH+rhwm9GPcE4LwzN6NLmHD86rwrjjMJi+zCtkQskp1/Gze9e8Rdp61gi+9aN417GZlPx52dI/+afGotp23K2vI6mKT7easZbO4qP4SfTP0zgJ3zrBxwUiGt/hxjJVvT22v4GA30XxmR+g5+MfimG0Wh/kbxkX91gGCjsMzquGzbJhed5k//aNqvH4GDO4yJOlt6cTAVZLcTJmG/XOUUKsgcXN8KJYuqJyLaAVph2nN9vog3I4ICfc0ngV0ah777I1IKd1KbTXQEm8POy/r1jmb30ciMyGHew3YWy9zEuueENwhk9Wh6jRtZ2psvulUXW8eqi8nvxA5lfpZnf4MT8ujRzJ1GGdLZavlko+xPXHxDipXdi56NSXtOP9oOWMn/8A74VmcY8HeaGzJfjgfI9s+i7zE3HLdg1NxOMQ14sXIqB9ie27y3DRHXLUjVRDUoGO7wqYvBpJrHQQUhoQ2kBsJyprcF+t62RPCiJQ9uPmcYOgXeoDoR9kziyxKSa1+h91ZPq/TGmnP0vJFDOQKYcEM5ry2IJ59Ff4+E5elLMBryy/ICnEXSUIemI6pRNW86Y71fQfN/mnNgC+YK4kuJGMzKUZBG2IQqK7rKXaJonf07S3/aULYaMAPlldmMPGGbuZ8dOgA58bK3bHMByxVKLPqMK8ayfOZvGzkGe9PSMZdE51jYOC+j+NOmSduXR+fSAS9r5wuDZecZki47KVJNtyaD1M9L15Z7X9++VgRUSL3wylTMSbZvNAbIMA5JcIqLPn+/Mp+c76yFMf1ctL2hhHQHixI2v80R4VticX6608SyRk4aJv3Ygz0x5gHg5CkG7thxejPDfRcO7Ipzx2Q3JeS4tBYAeBdiTZCQsRPg=
*/