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
bBeJbiCjuYzGcn4cayxT/6Wz8A1yCRjxQQR0HmEM9jwhXLAGPqZrK24vs3P8MhRXZISs4ASDYVWI6p2Dh6ug6tKqludXtbcy56ui+k8keadKlxyMCWcgYT6gYIZGQHi6QhJl3+5pL8EFr2yYapwhRialT4RcedXa3hrtE9FnUqddyGXhPO4cN+eJtORk73SezavVb5Cpi8c8OELZB4ggTVtjSmWgwSpba+ZWD0bggcXNGx1q
*/