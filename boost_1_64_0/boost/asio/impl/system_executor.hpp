//
// impl/system_executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SYSTEM_EXECUTOR_HPP
#define BOOST_ASIO_IMPL_SYSTEM_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/executor_op.hpp>
#include <boost/asio/detail/global.hpp>
#include <boost/asio/detail/recycling_allocator.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/system_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

inline system_context& system_executor::context() const BOOST_ASIO_NOEXCEPT
{
  return detail::global<system_context>();
}

template <typename Function, typename Allocator>
void system_executor::dispatch(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator&) const
{
  typename decay<Function>::type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));
  boost_asio_handler_invoke_helpers::invoke(tmp, tmp);
}

template <typename Function, typename Allocator>
void system_executor::post(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  system_context& ctx = detail::global<system_context>();

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((ctx, *p.p,
        "system_executor", &this->context(), 0, "post"));

  ctx.scheduler_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Function, typename Allocator>
void system_executor::defer(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  system_context& ctx = detail::global<system_context>();

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((ctx, *p.p,
        "system_executor", &this->context(), 0, "defer"));

  ctx.scheduler_.post_immediate_completion(p.p, true);
  p.v = p.p = 0;
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_SYSTEM_EXECUTOR_HPP

/* system_executor.hpp
9uGP0vozHuu7BXo37f+U1Lc9fjeP9T3Z8u+i9WnoXbR+0L1+pb7itP82vX+CmpceSBk901qxZGNAfXYZ8Au09hOoF2y47aeOk/FHnUZz0W3GPq2H2vei1ulGkm5lD9JtXHJLoG+w9rMfMxm/T/DzzQwYGRDJMVm8TPa11m3mRJDrHtKf9jDbVHnrs7enJuybb9pjRLAjSo3tq5VuN9TXebYvvrnUf03EgMbITgZuY2701L7mpRekqHQz2Y7a0PUzLcStfUncJrXeY5o0JF+y55TYFlFPbJJIgUgkJ0GiV9t0/qTduNkl8RrX2q6pll2uZVYhdgVKpADkIcos1atd1E/6bGrDq20SN/A321ZaX3aekkgdVPnRbnI92pbvVJ9ebZO44R7P92aG5V+T7WM92i5uQS5t1rUNrGhgJhAn7aA30p02UOY5P2dtA2a8cI990TjLP8Jjn/Gq9mvo3LfUeg+m6nmOr+mcbMg/8t1GM2QC0pQIVd7y7L19WXvuNLxJxR1AL27tvyTptfLW74t/C2vfnXo6jaF812Gr1tfVfk8Wt3Jw6cNkfy0phyQ5wf6BdBS+Fc25cpNVDgv7pKTNmZOSXkTmdZ29Fq33DpI82sNGWXlYrfU3jUmGzWMbGWfF6abjTEe/UetvE8fP6RzIypkt5dsCrtRhruMqFiPXPXs6XSSMzdip9UfIy4XaLdvmcIvmP5X20TC98vl857pbo8O8zn1jqFO7zNbHycb/jPYP9JhmiOSxgaG2UpVyl+u4hMPCobgN515N1meU/LfWbjZc7GE3E7YR3w221Hv4lDakjgL43kZdIxtc6rQ/rFz7JEwRYY710PsF7bGHCengGmYTYd7sRpiAklsd+xa6hqkgzOf6WCUrHPvBulxnrWvsFz1qd53tfrPTdRb90ZssvbduE3JNpV1Z+wYle2jHqVYfptuFy95ZxXIBGyfncwJymPTKbnZqx7LdsTRlo5FuCy5tWcKHWW15j9Z705783dql9M0Sp7mOo9dk0nqM0YEjqPucZM6xIOz7UpWrf/dA/6ZSnuLXt7HUi387w6qXs+/DZ5avnPPkwyq7ePdyss73sibu5XQ0WnWIzuXE9dTpfD/ier4T1rWMwlafvYyI41JGzVe7lpH6eK0vth3qVq2MxC+5yW8vI/JRUxlZ18MzTc3IE6SMBiOVqk/0VEb2Bz3PZUUc1/59oZRVe8Pm7VlP4oQTxyrLtPyC3Jx8w7DKb7EO052Urb3XJF4rt2ewENkDsUT798TOAPu1RT+HHY04+953NZehaX8Ll/2+xOZqZXtC/6u/AzeaCY+RZoXHspWHLH18XbZue5xWSJ5bSH/7vtbpZ/h3AeLluivxWlj70r2n9UIjCFvnIx7K3rpH+UmH9bHq4metJ3EuBUld2NPv53wtsfZHbHCL8hvONT7A6flLro9SV611mAB9DSBZ9jmW9l9/qFv7t4cpDpbzp1Gi215vohPm7HUd4lLXlLfH+4ia63uYvb71yc/3/bq+oZxLubd4rm/rVtl7nUvcMKvubtD6IqMxx12AeLmHlnjNjRZSD9dr/WpcVM3baqzzrbe41vk2rV9qjLTXuWVX3+p1rq/5u7XfGGOAe51b5+cBHaYPrTlM3GxGhXLTdwStdFuowpg5zextIcG9LUiYG5pZbeFc9nY9a/07niFqrH/rulwqH1hfIM8WrZAvSDdmjaf6n51TmF3gqR+V8BeYZUDeZoRa1wMrT5Hn0H8577uc2rzavsty75C6xtrr2uVxQG4j5F7SvX0ST/ZVtvZdljZo+Vl10rR17fdcNq/xcizXPZdd8uPXwj0/IQQu8ZYfvcu84TU/JdVsTgg5P5udbQw=
*/