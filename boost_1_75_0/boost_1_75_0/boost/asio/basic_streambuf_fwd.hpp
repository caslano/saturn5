//
// basic_streambuf_fwd.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP
#define BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <memory>

namespace boost {
namespace asio {

template <typename Allocator = std::allocator<char> >
class basic_streambuf;

template <typename Allocator = std::allocator<char> >
class basic_streambuf_ref;

} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_BASIC_STREAMBUF_FWD_HPP

/* basic_streambuf_fwd.hpp
kW44RrLsyVlOoRjy3SZXFlezeKbbQjamGkSLNJ8Tb5Xqk3S1N+3x3IEMFgiB04MJ8cjp5T6MsQWMaoZ+8SIhGS2k3ZZ0kAJMfBaemuIAAuAdYuHksmxVMgs+hCPcpw/9W3MIcxuLcJN242nd71psM+88ymw0KodWJHcGNnBAhtMU13zzzl9rUqCReFKQUUw7kW1oQUug4oiryFgjAn0CtgCprHtI2vSwrqYYzmzDMQPspMJUQ7FRuidevBfOMCmDE7dIm2wwO0Pium0/TNWJ90nALYqrSLZV0W374R26YBxqe8XxJYUAPZ1QyMxRmCE99A4MHHLVnXyOsYrkMi7ByM8373gAuQFvfxbyet5+HkayI4e5kTEGDZpqp7+HlkLvsG5IVipaenN6Fob8d6pqzb8nO5WcB1S5k7htkN2WnapT8qzKwiSESkhQ8mzKwhTitUquBMAdt0WaCfl2Jd+hLLSHZhGvjYhYSa9kWRVP0p5s5GoSlCyb4kkBqq9k2kFQsGqmzSgosKfbgNumdz8IGFi/plHpew3gqcwIVGRW6oro93kW75wcKypRxAj901ODyp5dR1V0Xk5yNxHgU2EpUFdFmM2fqq0aiGqrwqitUsQhUpChiAOKGPbTo71ACHKcPOPhayagJvh4ERyFOU72PsGm0DjVdBYTWJNA/WdLj1p1QhIgt9gPqLs7ZyZsMtm+O4uvXyN7I8IsstUW
*/