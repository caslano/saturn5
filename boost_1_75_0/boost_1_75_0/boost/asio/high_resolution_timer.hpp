//
// high_resolution_timer.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP
#define BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the high resolution clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::high_resolution_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<
    chrono::high_resolution_clock>
  high_resolution_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_HIGH_RESOLUTION_TIMER_HPP

/* high_resolution_timer.hpp
Btd4diqsHVS4o579S3MxyhZtLIGfs5zVphVg61/i8rLmxVZPQRwrR6zr4+pEtmh19GEy6clydSrITe1HNmvoFinH62O/QPayVN9sx3DbXh/fcohuERJBhozHRz4vv/+QEXH1RPCHkO91kW+NmS/vynwZkfmKYRUFbpeVnMDtdrUYY9P1WdXrWKGE1xdw9HD9AGLAtJC9sntAuQmRAzpiCdl8it/C45eSXcJXwSTIw3fvJ0I5oiOWaK9H7olN9ltWJj7eUkE2Y/BTSeCNwipMQjswFpufr8j5+eoMP8wyxq+VsaAdUBBkh7ISGpoQQ9oqAjkzjxxy80K+pk42c48dyn0EXXJ6Hob89XKlyBVhZ0uiaym6/g142ftwsPKXOxB0GYF3MdqYa4UduF3g5FpnPYJiaKB3bXWsthO/6otteGpa60cWc1s/DWsZMHyexp7669jDNWhJDDywne5Vnv8tFopr44zuMWgZwbtpGPNsM5rGiXuaWkjlYZ01X0MaSqHMgBO/C+N+AYcNvdPcFzrcZ7ALWkG3rp558cUXw47B5mYoNgNC+Y1gMmxeZTQaJpErY7wY5gl+izmdPOkf1OoTc1pIPwZFXcSlMwIjElhJW6NMhYqJOYb2dLgviKp7dfUCVF25z1qBlQ9FNkShTVjezAfZBORKGKBZ1saW+jg+bjTd1rfgVRdxlNShoSLRtplKhVasCzxsW7dhMvzd
*/