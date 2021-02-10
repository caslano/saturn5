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
y+T+OSceoCIRm8w3YvyaKggvTBbyEKjEETQi9girVWOW9LE0jIfPwYEQvgzToy5R5Ym68aHkWY2ybQsrrjR44fMhiv3Amw9Hey46KLvMAU2aTNEiZ2aSnefRK/qPIC8JY1Vx/klPqhrE2CTRuVeDFaV/gEcSf7zhE02rGk5S6Ji84ccptKJ9UGlCqqsRmt9KGhVXxRUKMbcPY5o2PK0Xzrc5u8EoaE17SRzQ89zjz2nuq0lDUprGUE+Zksp/iAAdZ/GyHBt5E5w3xUEQjt598ERD6kP+IjR8CjthwRsPU4Yx4kkJZpf6reYpdthei0l3NCTqizSSHg6StNZFeRRZp6dSThJH1XbFSKo9Tqewv7y/0ILGFUluogmRZDGaSvjZKIlFSURDOK7109qicBeQEvuekbNaM76Sg6umCz3+AId0N2RkiAEwgPYqmUGSw4//ZTzBTbuA66oHIQQYbBQZ/4hkA/rKrdgq6e28Z4xrzDGQIO4FKGjsxf2ZIOtpFqlOVXun8K0SuEQ1PEHupfwWHGLAomjzet9Wh+uS+hKsuD5iQ9zvje/9LClSdSXrDrGI6dKjFn19zF5XJy9mOVkybOgC9D41CVpmR0tAMpDkaxdd3EQs3htMl+wDja8N9xOgHs+/9WkIk+RETdxE
*/