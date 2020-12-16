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
+0Bnr+1Id2OCDn/5Oterw1+/3hrW4TOxUIfnoaGbN3hH/cb+xlPgyzBd1zlX81ld4MsxV9f5P5ilszf6XsY8XeYHsFC3uD3fGtCFBZ45NHX2VvOJtbrFlduseV3nDzD49B62rn5nzejwNxa6Rh0+GhN1+CxM1eFzUNVt3vZ259V5vukOvyF1+n1H+iZW6RLfgtW6wRfUzXk0b/sH49F5noEBP7KW+F/o0tk7/ZbDYF3hlzBUZ+9ynzFMF3jeIu8lne52HozRuXs60j8wSefv9e5cbJ3r8IVo6fCyP7rHOvwkBp/Rw55H9Orqfa79fu+3OM4DHan7Yd8vOvuI42CEfWr8Z4zULf70UmPQOb4CY3WdP8IEHe571Hzq8NcwW4cPWeae6nAFS3V6zFpGvw5vttz91uHPYlDZPPO5GKor3MIwHZ78hPPp8JUYp3NPakzSdX4Nk3Wbd15hbLrAd2K6bvJ/MFtnn3L/n7Y+dZt3bbrvusKfedZ91wV+Aut1OLPSPT2zh72H0atb/PvnzaEOn/qisenwdJR1+6WO9ItV/luHsy3n1eEdsVgXXu1I12KFrvMTWKWbfPRr1oQOV1Z7b5xlnPxrDNXF140ReR1uv2GudXjAWvdLN3jrN/0O1OGHUdXhF7FQ597yGwMNHf4lVurwY1inw/usc9wf92zysRiqw7cgr8P3vGMt6dY/O9Kn2sagczwKk3SJb8UsHT7wXfdFh4/AQl3ldViqs//ynsYKXeJPvWdsusDnYrUO777eZ3T4QAyY7Jh8CobqNve9b5y6xD/DGF3lb39gnUfzPf/23tBpg7WEKbrA/0Ql+j/edf+13pyrxu9vdFzbi//zrGGmrvDvUNUN3nezztSvc5/oTD9HU9f4feTOdo2bd6YpW3SmDbF9UGe6B4t1g19AQ7f4A9R02rIzfQ5zdI73QV0X+Bgs0CW+Ast1nTMdnWmSc+X5EvTq8J9Q0OFrOzvTOJ26OlMfJuvwrzBTh5ejpsMbsVgXMp3pLKzQ4Z27O9Mqzf5NzXXp8BEYfI5ryXamIYONQec+25mGDulME3WLj96mM83TVT5j2860VDf4/e0603Td7OlM2+c600Jd4RHbd6aVuswLUdINfhVzdZt328F4dPgJrNbhVRjwk55NfhPDdP6LnWkURtunyCehoMs8A3ld5fkYp+u8DEXd5DXo023ea5jxOWaRV2KMTjt2puMwUpf5Gzt1pgm6wl/4Umcaq4t8Hibr8J2YrsOvYq4OZ3s70yIdPhArdPhMrNbhGjbq8DMYPKVnkzf7cmcarsN7YaQOn4jxOnwNJuvwrZilCzt3ph13cV5d4v2Hu1+6wrvvagy6xDdiqW7wt3brTGt1je/HoJ+a59070zto2V7Md6bTkWyv8Wq0bc/uYT1ggy7zjRhnnzq/jqJOe1on6NNV3oiCzu3VmQ5HWZe4hqyu8zF7u7+6xV/6ijWjC/xTTNRVno+8rvMyDNFNXoNe3eaB+3h+dZYfx2Kd9jWX6Nfhy9HS4b/0uRYdPuSr7sW5PZv82f060966xT/+mndBzAPvNcJzp0v8Gubo7P6eayzQDT7uAM+krnALYx2neaC1dJB1pSv8Psbr3Nc700eYpAsHd6brMFnXeclI906nb3Smb2OuLvMfsFI3uWeUNaAL/Fss1A0e+k1rQBd4FhbpGg8d7bi6wG1MPc8YDvE5rNVN/hcKOvzTQ90XHT4fJV3nv2KybnP2W55ZHZ6DLh2+HsN0k/+DPp0d05mORzuuhbc4zDOv83ws5tmnxOdjlq7yMszWLU6HG6sOL8AiHb4dK3SLtzzCvOsi71h0f3WJ+4401qnOy7O/bc3o0lGeZazVTf4=
*/