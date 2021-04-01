//
// detail/wait_op.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WAIT_OP_HPP
#define BOOST_ASIO_DETAIL_WAIT_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class wait_op
  : public operation
{
public:
  // The error code to be passed to the completion handler.
  boost::system::error_code ec_;

protected:
  wait_op(func_type func)
    : operation(func)
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WAIT_OP_HPP

/* wait_op.hpp
6JdhEQu9ghCCgLW7i0cnYe489PiHgs3rEKFqes+3tskbYP5sm2Kg4bNr2U1fBTzGhmEpeOsF116GcT1wpQlqKf8ivbJVZXmbZzEGaMl78nz7JUuK8eBrkdc2rOoFGlz0aogs7VpXc8lGc1jDKUguJsMcsFaBy54t3+pweveByybR14tjtbBUQv7D2icvRKLuZdrPnvvVqyXSpcJGCIdnYkHVcKfOni32r+4J5mAEdrssXPtky6jtuQ+TbiC8xbkGZCRicWJrhM29OvXSTj/6Tiz/rIwl0PwrrjmJ1lBZvChOQnxgYyBYbLN1SkiS5iOS0Fu306CO/GIUZiyNqGj39N7kwlkShG25a33/TDmvTO/fF+CtV7u/rXXVS8lGlA2KcHL6JgVE/5Nq7XzzI65YeKZs0X8O0/OcX+AkJQttYPU/dYiJDpBgbsQJnecTK69/16je4v2xn4hZv/0VcuSjR+xURPpVj++0HjhSygZ75kP6ZXmrZN3nt/1dm7yB8bdLoW5CQcdZ8tmF3ybpMVDuigeby4bDrmWHseJqXkRH1xoygswxzIMyAi4v+Q==
*/