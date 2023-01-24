//
// detail/is_executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
G/Q+MojWYJ9elHWCH4+sgIxy33znEvnPtFCph07uNQvmRVwNB0VdR7YHErVYPiUPlH5idb75Om8sLqGFUhK8eb2KIw9T0Hi4Gau8UZ8XNkHJqcaSi9hZmmSK8L6CM4qBu9Hjp4EVBhNhGEybJA847a8vP0toJzwhDhjSA3eKSlWW/N9vGN56MNNpF0aVqC9/ys6PlZqDiMqxgxhVZzdWjv2tzuLJvNn0ChqK4C9x3LcmARzdIimQQ37OZYIk53p+JlQ7CpJh8GrSG6R6wm3VcVxNi7Kg2gpMsklvKA6ISEAxKxIacyBCgdfAvUBRUl2+WtL1PO5DYJM+VCC3XwT8/C7wOXujhdt9JL8i67AwHEIXfoSEyCWfEFwDVI07KH5muRbZuCIikdK+sw+nqpZ212PAgUo7ovQCblWfLHO/0Zt9yTqQrIMKxsB4QBoIX0e1ZQFQlULWBQOuWDwejY+bhzNflc+uXTG12N5nwLlfJBXdY7iBN+Ik2GN/xzu469VY2feYTsXza83MShPqSIcAtpaQk8nqXT9CXhF5cjM8qdxOPd4uH/k1zbIhJRilAnFY/b7PqHoIG68Ay4BXEb5l4dZO3VlMu09zFkPlM7/W956z+tf09l2DseL7WkgmDwdqeoEuX6VdnoukFaCc4o4cCSw8Ydx/SK9L3nkncD+sLNMawRUuKZHXxrPoJKTkwPNXF1WPhU6BiGsBdQfE
*/