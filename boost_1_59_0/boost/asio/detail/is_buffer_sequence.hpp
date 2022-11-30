//
// detail/is_buffer_sequence.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IS_BUFFER_SEQUENCE_HPP
#define BOOST_ASIO_DETAIL_IS_BUFFER_SEQUENCE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class mutable_buffer;
class const_buffer;
class mutable_registered_buffer;
class const_registered_buffer;

namespace detail {

struct buffer_sequence_memfns_base
{
  void begin();
  void end();
  void size();
  void max_size();
  void capacity();
  void data();
  void prepare();
  void commit();
  void consume();
  void grow();
  void shrink();
};

template <typename T>
struct buffer_sequence_memfns_derived
  : T, buffer_sequence_memfns_base
{
};

template <typename T, T>
struct buffer_sequence_memfns_check
{
};

#if defined(BOOST_ASIO_HAS_DECLTYPE)

template <typename>
char buffer_sequence_begin_helper(...);

template <typename T>
char (&buffer_sequence_begin_helper(T* t,
    typename enable_if<!is_same<
      decltype(boost::asio::buffer_sequence_begin(*t)),
        void>::value>::type*))[2];

#else // defined(BOOST_ASIO_HAS_DECLTYPE)

template <typename>
char (&buffer_sequence_begin_helper(...))[2];

template <typename T>
char buffer_sequence_begin_helper(T* t,
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::begin>*);

#endif // defined(BOOST_ASIO_HAS_DECLTYPE)

#if defined(BOOST_ASIO_HAS_DECLTYPE)

template <typename>
char buffer_sequence_end_helper(...);

template <typename T>
char (&buffer_sequence_end_helper(T* t,
    typename enable_if<!is_same<
      decltype(boost::asio::buffer_sequence_end(*t)),
        void>::value>::type*))[2];

#else // defined(BOOST_ASIO_HAS_DECLTYPE)

template <typename>
char (&buffer_sequence_end_helper(...))[2];

template <typename T>
char buffer_sequence_end_helper(T* t,
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::end>*);

#endif // defined(BOOST_ASIO_HAS_DECLTYPE)

template <typename>
char (&size_memfn_helper(...))[2];

template <typename T>
char size_memfn_helper(
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::size>*);

template <typename>
char (&max_size_memfn_helper(...))[2];

template <typename T>
char max_size_memfn_helper(
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::max_size>*);

template <typename>
char (&capacity_memfn_helper(...))[2];

template <typename T>
char capacity_memfn_helper(
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::capacity>*);

template <typename>
char (&data_memfn_helper(...))[2];

template <typename T>
char data_memfn_helper(
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::data>*);

template <typename>
char (&prepare_memfn_helper(...))[2];

template <typename T>
char prepare_memfn_helper(
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::prepare>*);

template <typename>
char (&commit_memfn_helper(...))[2];

template <typename T>
char commit_memfn_helper(
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::commit>*);

template <typename>
char (&consume_memfn_helper(...))[2];

template <typename T>
char consume_memfn_helper(
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::consume>*);

template <typename>
char (&grow_memfn_helper(...))[2];

template <typename T>
char grow_memfn_helper(
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::grow>*);

template <typename>
char (&shrink_memfn_helper(...))[2];

template <typename T>
char shrink_memfn_helper(
    buffer_sequence_memfns_check<
      void (buffer_sequence_memfns_base::*)(),
      &buffer_sequence_memfns_derived<T>::shrink>*);

template <typename, typename>
char (&buffer_sequence_element_type_helper(...))[2];

#if defined(BOOST_ASIO_HAS_DECLTYPE)

template <typename T, typename Buffer>
char buffer_sequence_element_type_helper(T* t,
    typename enable_if<is_convertible<
      decltype(*boost::asio::buffer_sequence_begin(*t)),
        Buffer>::value>::type*);

#else // defined(BOOST_ASIO_HAS_DECLTYPE)

template <typename T, typename Buffer>
char buffer_sequence_element_type_helper(
    typename T::const_iterator*,
    typename enable_if<is_convertible<
      typename T::value_type, Buffer>::value>::type*);

#endif // defined(BOOST_ASIO_HAS_DECLTYPE)

template <typename>
char (&const_buffers_type_typedef_helper(...))[2];

template <typename T>
char const_buffers_type_typedef_helper(
    typename T::const_buffers_type*);

template <typename>
char (&mutable_buffers_type_typedef_helper(...))[2];

template <typename T>
char mutable_buffers_type_typedef_helper(
    typename T::mutable_buffers_type*);

template <typename T, typename Buffer>
struct is_buffer_sequence_class
  : integral_constant<bool,
      sizeof(buffer_sequence_begin_helper<T>(0, 0)) != 1 &&
      sizeof(buffer_sequence_end_helper<T>(0, 0)) != 1 &&
      sizeof(buffer_sequence_element_type_helper<T, Buffer>(0, 0)) == 1>
{
};

template <typename T, typename Buffer>
struct is_buffer_sequence
  : conditional<is_class<T>::value,
      is_buffer_sequence_class<T, Buffer>,
      false_type>::type
{
};

template <>
struct is_buffer_sequence<mutable_buffer, mutable_buffer>
  : true_type
{
};

template <>
struct is_buffer_sequence<mutable_buffer, const_buffer>
  : true_type
{
};

template <>
struct is_buffer_sequence<const_buffer, const_buffer>
  : true_type
{
};

template <>
struct is_buffer_sequence<const_buffer, mutable_buffer>
  : false_type
{
};

template <>
struct is_buffer_sequence<mutable_registered_buffer, mutable_buffer>
  : true_type
{
};

template <>
struct is_buffer_sequence<mutable_registered_buffer, const_buffer>
  : true_type
{
};

template <>
struct is_buffer_sequence<const_registered_buffer, const_buffer>
  : true_type
{
};

template <>
struct is_buffer_sequence<const_registered_buffer, mutable_buffer>
  : false_type
{
};

template <typename T>
struct is_dynamic_buffer_class_v1
  : integral_constant<bool,
      sizeof(size_memfn_helper<T>(0)) != 1 &&
      sizeof(max_size_memfn_helper<T>(0)) != 1 &&
      sizeof(capacity_memfn_helper<T>(0)) != 1 &&
      sizeof(data_memfn_helper<T>(0)) != 1 &&
      sizeof(consume_memfn_helper<T>(0)) != 1 &&
      sizeof(prepare_memfn_helper<T>(0)) != 1 &&
      sizeof(commit_memfn_helper<T>(0)) != 1 &&
      sizeof(const_buffers_type_typedef_helper<T>(0)) == 1 &&
      sizeof(mutable_buffers_type_typedef_helper<T>(0)) == 1>
{
};

template <typename T>
struct is_dynamic_buffer_v1
  : conditional<is_class<T>::value,
      is_dynamic_buffer_class_v1<T>,
      false_type>::type
{
};

template <typename T>
struct is_dynamic_buffer_class_v2
  : integral_constant<bool,
      sizeof(size_memfn_helper<T>(0)) != 1 &&
      sizeof(max_size_memfn_helper<T>(0)) != 1 &&
      sizeof(capacity_memfn_helper<T>(0)) != 1 &&
      sizeof(data_memfn_helper<T>(0)) != 1 &&
      sizeof(consume_memfn_helper<T>(0)) != 1 &&
      sizeof(grow_memfn_helper<T>(0)) != 1 &&
      sizeof(shrink_memfn_helper<T>(0)) != 1 &&
      sizeof(const_buffers_type_typedef_helper<T>(0)) == 1 &&
      sizeof(mutable_buffers_type_typedef_helper<T>(0)) == 1>
{
};

template <typename T>
struct is_dynamic_buffer_v2
  : conditional<is_class<T>::value,
      is_dynamic_buffer_class_v2<T>,
      false_type>::type
{
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IS_BUFFER_SEQUENCE_HPP

/* is_buffer_sequence.hpp
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
*/