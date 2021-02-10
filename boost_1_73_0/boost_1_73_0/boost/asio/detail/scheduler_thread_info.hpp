//
// detail/scheduler_thread_info.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SCHEDULER_THREAD_INFO_HPP
#define BOOST_ASIO_DETAIL_SCHEDULER_THREAD_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/op_queue.hpp>
#include <boost/asio/detail/thread_info_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class scheduler;
class scheduler_operation;

struct scheduler_thread_info : public thread_info_base
{
  op_queue<scheduler_operation> private_op_queue;
  long private_outstanding_work;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_SCHEDULER_THREAD_INFO_HPP

/* scheduler_thread_info.hpp
Z0pSuDOrVewUAABfMwAAHgAJAGN1cmwtbWFzdGVyL2RvY3MvVVJMLVNZTlRBWC5tZFVUBQABtkgkYKVb63LbRpb+30/RK1cqsouibpZjK+XKyreEU7bjtZRxpryuYpMESYxBNIMGRDOzs6+yD7Mvtt93TjcAykomzvoPIaD79Llf23fsT29f2rAta/fJunJm62WWV7YJmc1LO22qwpg7d+zlOpvm83zq6tyXwZirZWb9HC9yV9i9DsSezYNdV/nKVXmxtbNsnpfZjKAAFzDrjbezfD7PqqysTdiBem6MPbDv3754ak8fPXzwYX9Z1+twfnhYe1+EYZ7V86GvFofLelUcVvMpF921+66ol75ZLIUQnD51RYEjgdRoLx5cZXcFNLF+98PF1bvvZfEOUd1xoHlIzIabpas3CznzrjEJL54BmDZzVZFnlfVlNhDOkVl26YJ1xcZtsajKgUftrZsRBT7VgMgNZj/k5RQsrm1Y5uu1sugvrmxctbUnR0dnd4fK5B66xMluAH9T5XWdlbZwdVYNiA+A+dUadEyKzG7yeikYthgDOzNdunKRBeuvgXOdr7KhCPavEFQSKg9ZuypkFWgA0NW6yFaQk2I3qfyGnwa2yCcVtgGYKAylA4VpwPet9esab0xo1mtfCa3Q
*/