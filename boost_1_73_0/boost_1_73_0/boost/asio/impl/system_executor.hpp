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
U0kYSgTW2FqZ1Ukgb67s5xJ1YrDTkSOKDYBE1I/K3LLyl7u9Zp7MlnySQ9M7z+ZCyoPEpUSbozfWWvPiuCC5yXmKUIG1G3/COyt0dAn/A5jow2lN+NjNiQZG05+Ph01/NxQ6BNGVDh3pOgX6l3bvYeuEU2F+UEsDBAoAAAAIAC1nSlIMop9yzAEAAC0DAAAlAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvbmV0cmMuZFVUBQABtkgkYHVSzYrbMBC+6ymGHOoEakMPveTWLi1ZaOjCpvQSKFprbA+RNa40TjZv35FMU8JSMJiRRt/fzDcO/RYCSmzN88BRtDA79NMW9nMSiGgdNOUeOo4wJ4wQ7Ihgg4PJpnTh6MyDFew5XrfQztGbuq7N3p4wlRJSawPIgHDsHhesY/cEa61+3SoO8JOC40vaQEcegZYnmbBKZmCldBSxFaUpUjz32vNGSwOHgRLoJ9eJWuv9NYO48ubrITOZH4FeG3jslosLyQC7w+Hp/SL3Qt4DBvviF3qwsyoJomBCHBp4RjQqvmhff9xk+Vp2Mq0/lCIzORRLPmVf2UaxpOejlQYebiyBxbQ8Tt6qFeq01crS6xhTqAQGe8aCEKkfBCaMI6WkMhKsSSANPHuXceAF
*/