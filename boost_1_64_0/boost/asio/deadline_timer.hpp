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
S66cgfcL41Wcmi/3I87E28++3vO5D2fhHWK8UnLlunhHGa+WXLke3onGayNXzsY73Xh5F7j7EefgnWe8cnJlCV6D8ZrIu+D6HNOvsa/3QtYz3IDt1mTHK/K8i0JuiNdsty95NdzI6/+nkbwNbuyl+bk4zAvhJl7/P+Xk1XBTr/+fFTPxOL8qpd+32P4yi/V7ScjNWM8P2/2XvB1uzvKesvvvpYwXcAu8ZXb9kVfDLXncduMtIVduhfe67X/k3XBrHvc94xU1hPcr4DZ6vLT9nrwJlunx0h5nyHvgtnjfGa/kMo4zcDu82M9mPZO3we3xBhgvcTnrGe6AN9x4VeQNcEe8AuN1kCeuCLkT3prGKyGvgTvjTTdeDeNzM1651/9PO7lyF85jS8zyKk7LD9cz3q6c/21gn9+VbF+4G97Gxqsnb4dz8UqNl/9btj9M4m1hvDryZrg73tbG6yLPvyrkHnjbGq+cvAZW4O1gvEbydvgLvJ2N10NeeHXIPfF2NV63ng/h7cX2TRqvlrwB7u31/9NC3g5/me58g9xrDPkrr/+ffPISuI9U3Pl2/ZFXw0q8/Ww/IG+C+3r9/3SwXjrw9kt3Xkeed03I/VnPB5rHLSYvg/PwDrL7L7nyALwF9nWQN8MDucY83Hid5PnXhpzP8o4zXiV5DaxiPF1k1/PJbr+MeBDLO9n2U5ajPBjvVLu821gePATvDOPlzWB7sLwF9NMzbb8nz/9dyEPTnceSV8DDvP5/6shb4OHp+jO5sprnd6F5fkXX8bjwCM5frrTjC3kTPNLr/yeP43kn3kK22+9sv+oI12/i+vD3R/G4TcYrZHlleEezvNt7vX/8p5rlNMBjmau52yyvjbwb1nAe9oAdn2/gPBYe5/X/U0VeD49PN16Rd8ITvH/tJ34j4y48kevGpeZ1lJHXwV/T758z3ivkypNYf+3Gy21y9yPWsn1ftY9LXgdPZj2/bccN8qKbQi7G+8D2U/J2eAreZ3a73cx2g6fifWO8avJGeBrej8ZrJ/duCXk641+GN3bV10teA8/AG2y8VvIuWIc32njTlnB+A3+DN8F4DeQt8Ey8tY3n3cp4Bc9i3JhjvAryGni2nr8Yr4W8E56Dt4Xxim7jdcBz9fzFeHXkTfA8xoNtjddO3gPreb072ce9nceF5+NVGK+WvAlegLef8brI85pDXoi3wHjl5LXwIrxjbD8g74YX49Xa13GHyyNewn5+pu1/5MpL8S42Xg25sgGv0XhXkisvw7vFvg5y5eV499r1R668Au8x4+Xf6fKIV+p8p/FKyZW/1flO41WRK69iPb9j9yNy5dV4XcZrI1c24n1pvJXkymt4fj8YL/cul0e8Fi/DX9UrJlf+jvFqkPEqyGvhdXgjjddC3gGvxxtvvFbOTwvvDnmD1/9PKXkVvFGv88zy6slbYJNe5xkvcQ+vF96EV2K8WvImeDPeZsbrIM+/N+QtbLftjFdOXgeXsLy5xnuIXHkr49ovjefd5/KIt+FV2sclV97OcXV/451NrmzGO9i+Xn3clpB3sH2PsI9LrrwT7zi7nslb4F14Jxuvmzz//pB34/3GeKXkR8F7vP5/msjb4b1Sjueb5cUfYDyA97GeLzBeHfly2MJx5mK7vAdZHryf86HLjbeIXPkAr7fR7m/kygd1ntB4neSJh+hf9L9m45WQKx+mP99vvCpy5SN4jxuvkVz5KN5z9nWQK1vxXjNeO7nyMbx3jddFrlyK96nx8h52ecTH8b6x/Ypc+QTHmZ+NV02ufBIvJ7aq10SufApvRMy8XnLl03iFxushV7bhTTVe8SMuj/gM3mzjVZMrn8XbzHjN5MpleDsYr5tcuRw=
*/