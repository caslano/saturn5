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
oUAcfaes/QYPJtZVSATVkQn2PgRmOb1UX7qoh2WmpDevOCO/ceNGhAoHVE/+TKfB7NpJttTsWcNlZDxEyBuZxE3hAXO5zPqlU7DMdfs4i7papPbZBAiNDD9aDeElDo3m7CdsJEJYETQmZKShfXyVyPID1MfmQZrMTPf1VEt4K4cES9tBFIzYnbn2kNNAPju/Hx9erAvANY0sA5uW7zHemUSn6lAYSYL7Uh6yzFd1IgDvj685hjYgbIHmNjeQIwDz+WX80LD1bs7d7zWz8DuipQaBAty6mXvtw4+UMW2tWE05EIY1JmkfZd/y3LeHBbl0tl+vghhvwrQDcixBMl4YgawSKuKCIcy6/t0z9Aq1TUaPCLfqvmBrD7bnlr2WhwyiTl3IXEjxH6+A1AGvgZRQw6evDAGusXLRKmQhDMCLgFGGSOJDwRIW2JKHkqvXhH6md2KmtBXv/K+b1oWgL/e4FhrMB6JGhGHIiMlmDWltLjy/otVnjKu22O984OuIkwRn3AU4vNietHaf8kqGctl7lCPPKG+5rPVHDdZI36mhAD8X8++90TtEsVXFfg==
*/