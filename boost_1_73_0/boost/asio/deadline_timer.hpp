//
// deadline_timer.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DEADLINE_TIMER_HPP
#define BOOST_ASIO_DEADLINE_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/detail/socket_types.hpp> // Must come before posix_time.
#include <boost/asio/basic_deadline_timer.hpp>

#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace boost {
namespace asio {

/// Typedef for the typical usage of timer. Uses a UTC clock.
typedef basic_deadline_timer<boost::posix_time::ptime> deadline_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
       // || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_DEADLINE_TIMER_HPP

/* deadline_timer.hpp
seGPL4fknLDBsd0PPa/qnwlRp9BN4ohMwdHxLB8dhFl8jT2Fe8vAwTD5xtPJT8J7ke0eWq9IIMpL5/IyaAStIGDD52sv9l5CslXNhGFI683NYWrK+iR9wxK/u1IX2E3NI0Raa3wsfeyuCNdYwjWQ9z3JB00mHf9mx8frk+keKutj49nQZXizyy+VB2+OCBz9IevVZY4j61Rr9vJHxrNZHzsAmlSEPyiSTqDO/UxHy736GrO/
*/