//
// io_service.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IO_SERVICE_HPP
#define BOOST_ASIO_IO_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// Typedef for backwards compatibility.
typedef io_context io_service;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IO_SERVICE_HPP

/* io_service.hpp
MYRWfD2did4ljLwYbZ2puQBBx7JxQkjY+uuRjXoxeLe9C/tNLVEcJWCI5ch/ozFn7AFSt+A3kbDKojJl/QMG4rlOk49tMl0D/3ALWo/WvreOhIDfUpkP+TLKI+NANOupv4P3ctny3qwelOwyDhp5tdEdiR/lm30jWw82Sr2GnBtLQjMAKBhzDZOyzgQftddDQusGxyvrzBSJRB9QkbzGX9JyW3kUk4IbznM4tKyom8AlHoH1
*/