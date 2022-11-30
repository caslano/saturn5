//
// detail/is_executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IS_EXECUTOR_HPP
#define BOOST_ASIO_DETAIL_IS_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct executor_memfns_base
{
  void context();
  void on_work_started();
  void on_work_finished();
  void dispatch();
  void post();
  void defer();
};

template <typename T>
struct executor_memfns_derived
  : T, executor_memfns_base
{
};

template <typename T, T>
struct executor_memfns_check
{
};

template <typename>
char (&context_memfn_helper(...))[2];

template <typename T>
char context_memfn_helper(
    executor_memfns_check<
      void (executor_memfns_base::*)(),
      &executor_memfns_derived<T>::context>*);

template <typename>
char (&on_work_started_memfn_helper(...))[2];

template <typename T>
char on_work_started_memfn_helper(
    executor_memfns_check<
      void (executor_memfns_base::*)(),
      &executor_memfns_derived<T>::on_work_started>*);

template <typename>
char (&on_work_finished_memfn_helper(...))[2];

template <typename T>
char on_work_finished_memfn_helper(
    executor_memfns_check<
      void (executor_memfns_base::*)(),
      &executor_memfns_derived<T>::on_work_finished>*);

template <typename>
char (&dispatch_memfn_helper(...))[2];

template <typename T>
char dispatch_memfn_helper(
    executor_memfns_check<
      void (executor_memfns_base::*)(),
      &executor_memfns_derived<T>::dispatch>*);

template <typename>
char (&post_memfn_helper(...))[2];

template <typename T>
char post_memfn_helper(
    executor_memfns_check<
      void (executor_memfns_base::*)(),
      &executor_memfns_derived<T>::post>*);

template <typename>
char (&defer_memfn_helper(...))[2];

template <typename T>
char defer_memfn_helper(
    executor_memfns_check<
      void (executor_memfns_base::*)(),
      &executor_memfns_derived<T>::defer>*);

template <typename T>
struct is_executor_class
  : integral_constant<bool,
      sizeof(context_memfn_helper<T>(0)) != 1 &&
      sizeof(on_work_started_memfn_helper<T>(0)) != 1 &&
      sizeof(on_work_finished_memfn_helper<T>(0)) != 1 &&
      sizeof(dispatch_memfn_helper<T>(0)) != 1 &&
      sizeof(post_memfn_helper<T>(0)) != 1 &&
      sizeof(defer_memfn_helper<T>(0)) != 1>
{
};

template <typename T>
struct is_executor
  : conditional<is_class<T>::value,
      is_executor_class<T>,
      false_type>::type
{
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IS_EXECUTOR_HPP

/* is_executor.hpp
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
*/