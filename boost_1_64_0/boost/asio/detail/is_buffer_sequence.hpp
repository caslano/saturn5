//
// detail/is_buffer_sequence.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
DVXd5NF/937TZb4ULces8f3o101+G02dVm+ZtsNynedbsVY3ub3Gb05deWPLdOZa16jrfMab3snjHZN3ect+MWb+xrvGqbPv+T7FRB2ejbIOP4eZOjxovTnRRT4dq425yrdjlW7wy1iq25x533rTOd4fi3SRT8dCXeHrMVPX+Sms0C3+xweeO2PO/9t6wRQdvg+zdDi7wbzp8NexRFfDH3p2dPG/zoV1cS5+ASO/17PJd3zkd4UO/wlTdPVjY8dG+4cnf6IjZW0PV5DXhc070vGoxP3iS7FS1/iHA+wzXvMaNHX6ZEfq3aIjjdcNfhnrY3543KCONFyHv7plRxqpw0dgvK5zC/0+G965oyOt1eECkn3CZ2CIrvEjnR1plnGGT+jqSPN0eCaW6GymI+2Jpg7/Dv06fD/aOvwIBn3f/Hd3pOswNPpTHemiz3SkYbo22HV9tiOVdJHfxEid/VxHOgpTYx/eauuONLpknPwQ5tkefheLdHjkNh1phW7yztu6Zl3gT36+I82N5ltQcJzcUPOMVbrCczA9zsXZ7Vy7zvOTWG2f1NORvouNusLz0afrvO8XOlLXD3o2+UrkdHgO+nSLv5brSAN0iacj77NVvhe9usUHbd+RNjhvid/GINuzO3SkszFEV/l5FHX435igw9t80Vzp8FHDnFuHL8QiHb4Ty3VhR/ui7VxVnrSTNrbwrV9y3h/2bPIHyOlqb0e6CVPtE25hlg5/58sdaYEOT0FDh6/ESt3iT+9svekcv4GJ0btYJyjqNn99eEfa27lKfP6u1q1u8keYotu7WZ+7d6SyLuQ70jN7dKQxurRnR3oUI3SLe/dynAn24eMx4ISeTd5tb/dIh3fHMF3mDzHC/uHSPsajw2ejrNO+Hel69Nk/vG2fdajDp6Ok2b+zGadu8Sf260hVHe7DHB0ehbou8TQ0jTm8+9c8OzqcR1s3uHOEtn+OJ2KY8VT4MQzWbe7b37OvS3wLWjEG3u4AxzrJPPBdqDhmeCNm6vCkAztSTYfPxWLd5MEF98tx8lxGr+NUuR9D47y8z0HmU5f4e1+3ruxf5xMOtoZ1lW9DwWfr/AT6dIuPHulYJ7oWfgprHafFo7/hXWSfMr+Ltu25UR3pYrTsX+OHscH2TUayPTzwm54RnePvo2WfMr+Ogu3Z0a4bTV3nHQ/x37rIT2CtbvOJhzqvrvLAbzmHzvN8DIrxc3GM50KX+XVUnSu822HutQ6XUNfhH2G5rvMOh5sHxyzwE6jq8E5HuBc6/DUs1hUeWDQvOlzCOB0+G2Xd4D2PdK91kd9A1tiy3zYPGKIr/DhG6xYPPMp7Q2f5tyjqJn9yrDWhc3wMJuvwA5iqw0sxW7f5s0dbAyf3sHNhsA4/juE6/BeM1IVjOtLWJ3hX+GzxpI50B5br8Kmnul86/BA26NZpHWnGJGPw2Tp/iKk6PP50Y9DhMhbqGhd/ZPy6wl8+wzXqEg8s+4zO89lo6CpfdKYx6CbvfpbvAl3k7X/sna9L/Bds1Gmyc6F3Yg+bExR0+FmM0+GDzjYGHT4V03WTx51rbejKed6N04xZ5873DkFDh3+Fpg4/jLU6vArplPh3w470CoboXMV8XmDO7VPiOvpsD4//ubnQ4TIm6gbvf6HvAl3iR5DXLd5uurnV4e9hug4/jLk6XeR7BMt1uIa1OvwQ0qk9m7x+hvHo8H+xt65cbH8UdfgxlHT4yzOdV4cPvsT86PBhqOvwBCzV4avQr0u/tH4wWjf5yFm+a07r2eRfY60O34w0qWeT37zUu0uHt7nM2HT491XH0eG/YaLOX9GRHsR6x2/zp6/sSOt0jp/EAMcPL73aMXV4A/p0+xpjmeM=
*/