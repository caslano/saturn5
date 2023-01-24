//
// system_timer.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SYSTEM_TIMER_HPP
#define BOOST_ASIO_SYSTEM_TIMER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/basic_waitable_timer.hpp>
#include <boost/asio/detail/chrono.hpp>

namespace boost {
namespace asio {

/// Typedef for a timer based on the system clock.
/**
 * This typedef uses the C++11 @c &lt;chrono&gt; standard library facility, if
 * available. Otherwise, it may use the Boost.Chrono library. To explicitly
 * utilise Boost.Chrono, use the basic_waitable_timer template directly:
 * @code
 * typedef basic_waitable_timer<boost::chrono::system_clock> timer;
 * @endcode
 */
typedef basic_waitable_timer<chrono::system_clock> system_timer;

} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_CHRONO) || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_SYSTEM_TIMER_HPP

/* system_timer.hpp
bYko6EfzwxfEMCaYw5i4Dc3Htw4OEO+BOFlVPy6Ns1c5QGSvagAqxpO2k/bNeRJhqW7GBEjrqv4T3pXc88KvHkNChzdr71yKIql6UlULtNJHCfiJRsqMWTFosnjYACsxG1o1r3quePAgPNBt7nk6suk34iN/9NHeqhPQkFndvmL+01+aCobExlexlFOhFr6DLfTxOUfDteyC96X0zscnhR6rD1fZU62Wqm5sGP/yMTSOtQVL/ReMpIxnRRAqZRFC4OSC4PT+TqmoaVuCDEfJPVkpRcqInK19iFC84a8leqMET716I770NpVf4ucRFD70wGckZUJxqwTiUAVv3ofnMxr5lfDEnXD47l5mUS3ftSiW71gesKyzpFrclg3w/4Pwb6plJPzvpV/3wt+7IMVtdLN0E/1vofewgpDItzUn098M/Mu/zxAXhi243xXjuNNmV+wsYQ1MbePi9WoMl47DGLQobc0plCOd/uKJ1Nb17Pl+o+s5+NOcSk9Tl1PJJVjmHf+qzH3H+owY5DPbmmdSzk9XYHmLsbxSLG8ePU2jv7N9dCf5TjIUwwZLKMri+MAWyaqMLhGGSiW8ays08jpLWaBD3mpkrrLZa0+sQiXsqEC9ZIWz+VaRMNAubx2k118ItTHhzDh7Gk+qSbzs52HRrqaJRLtgVWlVMywEv5UfeZLOTzxA5/O7EQJ1/f2lvBufuu1lZaV+qbRq/J1x
*/