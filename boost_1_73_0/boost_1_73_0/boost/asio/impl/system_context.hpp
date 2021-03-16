//
// impl/system_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP
#define BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

inline system_context::executor_type
system_context::get_executor() BOOST_ASIO_NOEXCEPT
{
  return system_executor();
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_SYSTEM_CONTEXT_HPP

/* system_context.hpp
n7TY68C3FnsZOGVpDzMQ4nxR6JgnrsETbV5EDE1bAlPNttk6IYgaZEYYOS7rTbfZVno3myem+CHEhAvo5Vq5EOIwcDe9TAv3sZiCKJnAGa4gqiRw7iVeByeg9IUQcy5eB3NrFwixHuinl3dtoWaiTG9lqp8Ku17YYmHLhd0s7BfCHhD2sLBnhG0X9oawt4V9KOxjYWiog1mWZVi+sP7CzhM2XNgkYZcKWyBsibAbhf1c2H3CHhC2Xdhzwj4U9rE=
*/