//
// impl/thread_pool.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_THREAD_POOL_HPP
#define BOOST_ASIO_IMPL_THREAD_POOL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/executor_op.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/recycling_allocator.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

inline thread_pool::executor_type
thread_pool::get_executor() BOOST_ASIO_NOEXCEPT
{
  return executor_type(*this);
}

inline thread_pool&
thread_pool::executor_type::context() const BOOST_ASIO_NOEXCEPT
{
  return pool_;
}

inline void
thread_pool::executor_type::on_work_started() const BOOST_ASIO_NOEXCEPT
{
  pool_.scheduler_.work_started();
}

inline void thread_pool::executor_type::on_work_finished()
const BOOST_ASIO_NOEXCEPT
{
  pool_.scheduler_.work_finished();
}

template <typename Function, typename Allocator>
void thread_pool::executor_type::dispatch(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Invoke immediately if we are already inside the thread pool.
  if (pool_.scheduler_.can_dispatch())
  {
    // Make a local, non-const copy of the function.
    function_type tmp(BOOST_ASIO_MOVE_CAST(Function)(f));

    detail::fenced_block b(detail::fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(tmp, tmp);
    return;
  }

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((pool_, *p.p,
        "thread_pool", &this->context(), 0, "dispatch"));

  pool_.scheduler_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Function, typename Allocator>
void thread_pool::executor_type::post(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((pool_, *p.p,
        "thread_pool", &this->context(), 0, "post"));

  pool_.scheduler_.post_immediate_completion(p.p, false);
  p.v = p.p = 0;
}

template <typename Function, typename Allocator>
void thread_pool::executor_type::defer(
    BOOST_ASIO_MOVE_ARG(Function) f, const Allocator& a) const
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef detail::executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(f), a);

  BOOST_ASIO_HANDLER_CREATION((pool_, *p.p,
        "thread_pool", &this->context(), 0, "defer"));

  pool_.scheduler_.post_immediate_completion(p.p, true);
  p.v = p.p = 0;
}

inline bool
thread_pool::executor_type::running_in_this_thread() const BOOST_ASIO_NOEXCEPT
{
  return pool_.scheduler_.can_dispatch();
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_THREAD_POOL_HPP

/* thread_pool.hpp
auluYyg2lnmzMTM7n01Pvdko8VrIueW2bzz+3vfCznDyd9w7n18e5TyRe1dssN5duu+PPcy+P7aHsmhOIhXeykI9ZmQXZqk+0rpHr8Xe3c7lHxlW7ZhyXlZ6PWbhghquw8Q7//3QSc9jGzFaVbdR7lXXerFR74fu1Ubi1bgfOv7nvx/6keiz74d+Us87+ffvk3mu+6Ce6z6ZnvdN9bYPp7f9Wr3tg3ru+2d63mfV+36qQ/R+qq/f2vPy2Oy7TnR5asuTvTc+WultP9Xfb9/U32tfWc/7r3rbH9Xbvqbe9ok99/1Ove3Te0rWieNPjx2U2LhmG/q6refvTOH3Ieu3fu9g/f7M6feXTr+PWb/12IBO82l1Tym/Oawh62TJmJaspVxtnaybZB7WGhgj80/7yfzTKTL/dDq8Hc6H62Td5PWwCN4BlzjNbywzZIxFxpFKqq3DsAmnXjLva5DM+7pY5n3Nk/lemXAHvAU+CDfCnXCz6PeK/qjM59or87ueh7jp9YQel/lYu+B7ej1oWV9I7Iw3ZOxA93s4VluX+pjMV/0C1ldlL/PKaKbWfPdEid9Yx3ed7/6RxP8L9IcfSzqfwAawEgaKbk8vVdIL9JDee5LenyW9I5LeB5Le+zBAdPv+ELmSXrhOz3V/iD9Jei9KevskvVckvZdga/gy7CDu9nTLJN04D+kekHJ6HYbAN2R97ndgK9XmZX3vQ7C3drfPG5R3wPK7pNq8wack/tPSXvfCHvBZ2Ac+BxPg83CcrOs9Qev2dVjkHam82y2ptg7LLJw6wtkwCqbDaDhP0s+A41U8/p8s878vlfnfaXCFzA+8HhbDLLhC1je/FebBTTAflsFCuAMWwT3wanhA0v8aFsMqeI3MH7zWKn95zwbHeSj/6TiFwctgdzhDzreZcIDog+HlUl64W+kaq72nO0nSTZR0p0i6SZLuFEl3sqSb5FSvqZLuBA/12k7qNVzWb+8IO8ML5DgR0h91UumLPkZ0+7q6FZL+zUqvtq5upKQfBdvDnlLP8TAWRsOhMFbS7S3z+PvIPP6+MFPcc3Sbp34l/irYz7JDnnt1H+puxyApvwRZ536o5He89LvDpNxGwtFwlNgxWuwYAxeIez4cB0skvsr3xdb8WHlG1GWIY7X5sc3l/Gwh52dLOT9biV1hkk649YymwxoNqs2Pn+IUrqSW4cpqGa6iluEqaxnOWFtzuHh/w5pzWsP8VD0XNXBHzXNRvc9D9TgHtdbzT3/r3NMa5p3+rnNOk6CXOab/1bml5zOv9Fzmk9Z2LqnMI60+h9R5/qjMHdXzRn/TnNHDsb/fXNFznScqc0RlfujvNzf0954XWm1O6P/0fNDc4upzQM8+97Mcsc/53Mo8v0PIGSTyHeYNIkXIVuQgchIJPcx8QyQJKUI2IfuRE0jou5wfyBykFNn1bt28wbq/ur+6v7q/ur+6v9r8+SHZ/4nv/wuKCqLN4enfPAfgwx48d9q/CZHvUdf5OtitI89s1zm+F1yYnpc5lxFsxqlS+LYpJy8lvyCPVO3fhoRAm4wJ81vi5vrwvbPP2b5JbWIEajtirtfPdPo7qg7m74jxE+P6G+LW0uHWz+7W1OHW1+5W3+HWx+726wrLrbfd7WeHW6zd7TuHW4zd7UvLrf8Au9vHDrd4u9ufHW5xdrc3HW5WPl5xuFn5eN7hZuVjt8PNyscjDjcrH9sdblY+tjjcrHxssNz6WflY63Cz8rHK4WblY6nDzcrHIoeblY8ch5uVj3kONysfKQ43Kx/THW5WPiY53Kx8jLbc+lr5GOJws/IR53Cz8tHL4Wblo6vDzcpHB4eblY+WDjcrH00dblY+6jvcrHz8utw=
*/