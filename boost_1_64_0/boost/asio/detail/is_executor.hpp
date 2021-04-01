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
AuOYIzBn+eXxEJQDm61BNfgd5k/x/B5ahpacEzajU12CPtMslPXte8qkvsT+qX2j+mLrNlOFsGRCCQr4jA86IFIWPJnanUJCQ8d7njoLzf83Usj7bianVM3K4GBITEG5iA0UL35E959asH2SBJ2oVSMm0E2sPVMlTQrlwGPgsPrrmMNC//WOxW4APzk+rBzzgpk8bmDFPscHvnIj3wgCTpPkTh62bAs4npWqqI8PPAFC/Cv7aUupyj4PyJECNjZEN1lCTOw3KGx0mUWYGqkmjKkmUCMVAo7e/at/UvegsrD2sRxkUPEhjuOhmp7xmSAdutblHqQU9t8AaRVCklTwpyRcfJx4yTzJSe49IH4DyNjRSAwQbb2BM+wMf1PYERueKrniZGnm4N+RlTdN8rWIytZIKKqBLs4mzCDJnPFochJ5AylzzYH9kGC29kvJ63cNIB1dYae5Z+ZtXmnclnEb1Cx1T8BKzG5kr4iGsxFsYhD2qbSxV7t4N8x0PDNu4IQu84IeIMJBDBUWXB/K7PqowYz3M3HHhkt6J2vWJwBHdZ+e7iMllzbZ4+JHBw==
*/