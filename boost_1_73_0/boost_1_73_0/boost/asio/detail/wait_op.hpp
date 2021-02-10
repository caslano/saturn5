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
FaeYKOAscSa246EZifpkiXm5SKDrZM+MV5SdXER/ZI5waW3dwsU6B50+8dchOFGKggxZU8duzQ5up+pOj6JEq70ZwTZqpOEmIBOT2tRmHnymO1iv8xQXm9rcu6oc1eXdNCAFMATd4JLtHcL7zyeVgvaxwcAkikqRyTPkmU7sCUua9WdRwOcPEfA3U2Q1NPC4Q4TbTbW522YuKlObdc3yFRF8Yt2XUBrr2a63GXhyl656zeJ/TPMSi95pJp2TWkIZ1e2aKO4wOrwTtgL4jCnWusdPP+gfHk8v/q29r6eJPda2sexzFrKqpnKx2TPtnCgtqvdD2sEzLUNm8gdUl2AT850XSlA5J1Tis9rLQJNN5VX1S4fJKJ7n4TeG2nJJrYfsnW2ArecQf/B+Th5v/mLrailnR1HNzvB2PZbzc9ePq1Rk2IpkeT+zEnPpqqyarJJ2hvxNmtSSMBjq2JStnPBX0c9XBZsvLfjcONWpWzxznW4SXwm8VJa3gAMi7Bpyji5o7nKbWntPSUzvyBRfDtKu3CZVxKRKoyWsU99p5SSwXh+cmMZw80H+kXZz8ZQ9yb7KOc8sDpTa2dVCgrI4QxrCKnPxmVUpyFu+zk7IQeGx1UXei+xWNsCgkWuO7whjApa7N8qIcUBRKS0yigtX
*/