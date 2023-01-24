//
// detail/global.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GLOBAL_HPP
#define BOOST_ASIO_DETAIL_GLOBAL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS)
# include <boost/asio/detail/null_global.hpp>
#elif defined(BOOST_ASIO_WINDOWS)
# include <boost/asio/detail/win_global.hpp>
#elif defined(BOOST_ASIO_HAS_PTHREADS)
# include <boost/asio/detail/posix_global.hpp>
#elif defined(BOOST_ASIO_HAS_STD_CALL_ONCE)
# include <boost/asio/detail/std_global.hpp>
#else
# error Only Windows, POSIX and std::call_once are supported!
#endif

namespace boost {
namespace asio {
namespace detail {

template <typename T>
inline T& global()
{
#if !defined(BOOST_ASIO_HAS_THREADS)
  return null_global<T>();
#elif defined(BOOST_ASIO_WINDOWS)
  return win_global<T>();
#elif defined(BOOST_ASIO_HAS_PTHREADS)
  return posix_global<T>();
#elif defined(BOOST_ASIO_HAS_STD_CALL_ONCE)
  return std_global<T>();
#endif
}

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_GLOBAL_HPP

/* global.hpp
Yl12p/wkgnFwfX+i4uBqhkn3qoHEfLGVBD5PeZPNfzsGoZT/p2z1bjNUFCdda7O+5eNOWeZaTJD3Hj4OFwt9E5WCTstWPq1qzrSPYtqLEx2C5XDrR+Vvyk4g6KPcN9UNn6acsqAB4id8NM9x+PiHwU9aO/dfczcnX0Rk4yOHjytWuIkxFnAA446jBLIQEv/d2xq2qznvI73hqAxSlQMMVxdmR3Zfw1zVcGuG4ZbYNtdfUItlZeL8aMiIChLJ0UAoD9ZtOJu2NUnstmyKEbvP2zxGrnw7Mv/zeRomCAWHATOq4dna9NoSUAQp5L/TLN7Dm73F4c1jcTSVq9mHfJ/SGQ5XF0MgV0usl0Tie80bEdbHVI/KU/aDVFV1TRNixEaLElPVNVWIhctefDEZVA26+pyqrum83RW/zFeerMyojp29kbfPXsrbXHYFUnW8KnY7BChkupBEd22zlwpDqvPM3tywWG+R6h6T3ih0usKuMC5wg2x6HQihr7hNKq71gT0neYA8rrog7Ctv9eUeSz8olR+DuAIIzZHKQdllsdXG27nXmsTgdGUshJGTEX3geX/2E3Bx9pgNVjGYJgaapNyQr0DOKkhe91PxgN1X3pFV2bb24g0xWbntayfDH2E4XBASs4pb146CqwVH13O4RuSADR4FEzlemVIKatWCe0X8/tzTYStEvV0u0/XA5KSu6mF5wZVo+4HjBY5FnXV2
*/