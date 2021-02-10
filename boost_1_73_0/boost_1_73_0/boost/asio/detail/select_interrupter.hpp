//
// detail/select_interrupter.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP
#define BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__) || defined(__SYMBIAN32__)
# include <boost/asio/detail/socket_select_interrupter.hpp>
#elif defined(BOOST_ASIO_HAS_EVENTFD)
# include <boost/asio/detail/eventfd_select_interrupter.hpp>
#else
# include <boost/asio/detail/pipe_select_interrupter.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__) || defined(__SYMBIAN32__)
typedef socket_select_interrupter select_interrupter;
#elif defined(BOOST_ASIO_HAS_EVENTFD)
typedef eventfd_select_interrupter select_interrupter;
#else
typedef pipe_select_interrupter select_interrupter;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_SELECT_INTERRUPTER_HPP

/* select_interrupter.hpp
9TUX23IW7C1anYUQjAhh0ojUmFAmMnphf5jSr3JWiFIx25wgjmYHcPt+Rkng5Yr8Gn91cjSO5Je+PLi4fDoaGfNkC7KuXdFIAgI8+kYcuciUo6kZr5PpIdktqTIIGARjK6ZZRgw0AyPKWs8HFGAjPlkPbtOPUDhoGyRwgTMnwRdNrfEuxkUoZFVHU3N2T81mD3ZBPVGwDswsfDm0DPjUeEkGon0JX2I+hqRDozhWAwN4AUTdPiTm5xEh+iaomDDOd9kvxVD6eufrZznYARQip+WrLjPfYCiFNy+ZPSFmIvBE7e8tGsj5EmGrLOsQmVOhO8QZJ2ta04RvuuzJQHi5SCvyODLrABrReozECalawp7KdeaFJmF14rTu7fRSFuhm4ZVx5TYpwc2MttPlsMT6aSOxnqm0xOzOLJHOmz7QNsuW8mLLbIqOpbWmVb6C491RpicuiA+zLFcEmy5r6+nOQBVBvNDeoiFHdAe0vPZgLKUM76xV2Hher4dj5OwOnufF1Rt5B8uv25fPRk+v5G0xc93Sl88udC0qwO7t6FV8G1Y9sJevIty1X5+2b9/8+OaUb6nGGij0/Q9XWC1SXRR+MiEbC/F0sRoV6vqOWAqTnrjTtj0KTcIy44ACF1kwBiHwmSlzz0wNWfMtxIM6
*/