//
// windows/random_access_handle.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP
#define BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/windows/basic_random_access_handle.hpp>

namespace boost {
namespace asio {
namespace windows {

/// Typedef for the typical usage of a random-access handle.
typedef basic_random_access_handle<> random_access_handle;

} // namespace windows
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_WINDOWS_RANDOM_ACCESS_HANDLE_HPP

/* random_access_handle.hpp
KGnKOtv/5sD/uqleNn+FqBHQ5ZPVxep6NRtj+Avw1HLmLlpprYJWQ2O1VtoQcPjP2jmoavjjEA+7ruAmXUAfYt4wV9hXLMMZXAdw0EG4pidQMzyvAa1a8lF8Z3vl+HM+Be5oGj8HSnE1v5E/xl/i1wuDoOE8pEUSpzSwZ6AHKIOVFGWislBZqtxVHinF1NJqeVxh3Ee1Mm9VX7gFCV4hRusPP1BO76xPBc6v1scYqcYFIxDYfR2awoOKx5g7Ex+MehZ0RFM6jG5Px0IRjaW/omfR8+kltDPG9Hdo4KKczDXisrnbXEm+OtydBn0bBoVr6dsEOLuR/Dio3NnQuZbK3cLvAataOvcyNNIjnhaaCxFAmCHCSGEKtNFKYZtwQDgqnBHuCE+FqqIgjhdvivcwTlbdSyWgaW1JlSxXbunVwdLnGK0ZYLol0lZ47CvSTSkELNpVHiPPtF2zi1JCaag0x/gNU8ZhDGco3yjLgCtblF1wYjnwYNeVW1AjL5S3ShG1OLxXRbWqKgFrPgXOdFNnqLvV74AzL9Tq8Fiq1gD83lsbrI3VJmnTtEXaUi1T267t1Q5qJ6HTLmqxcFWj9C5An9PGVSiWR8Zzw930htKtbNaw1yx1s5H5k/mLvXblYfPTr0QEU+8BGjrLpXHt4+H7T8tL4Q3vK+vBzi/Uq1o1vb7uDDfGGV/Cc500Vpm3HOueiR5ULH7tJi+JB32D
*/