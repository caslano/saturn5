//
// ip/host_name.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_HOST_NAME_HPP
#define BOOST_ASIO_IP_HOST_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/system/error_code.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Get the current host name.
BOOST_ASIO_DECL std::string host_name();

/// Get the current host name.
BOOST_ASIO_DECL std::string host_name(boost::system::error_code& ec);

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/ip/impl/host_name.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_IP_HOST_NAME_HPP

/* host_name.hpp
BOVdNmZdNEB0p0wpDjOZ07fidrwNZd1A7uc6eBkB1YyYAC/FUlSo5ns1HRh2UIhIIfn72Jot9285A9SXIQFcOyFNJPEEcYsue4o40mNJTe+Z6U4UeZc+r1bTB8x71Gc+RMmKCAt5D7lttujCr80g5QVeVpv5FxeYvWvoYa8Ws0O3bN2siX3wr1HrSKcMNV2EcxxnMxfQ/CAWgFpSyIlebK0FzAkxEql7B7mYzNxPsuuVof1cWJoyzZGwXREaQT4srcB5A25GB3JirCvGiGKPWkpNyQo4xuqtrqi2z2vChRbg8ZKN4hpdfLHThednJrewn0Uo9dkJ7AOq4DPGotnntvvQTkamuDtE81iUXZ1LSzjNTAfh7wZ1wImlBKkiKzlzytw//vedrCldXyHPQL/F3bjGXAwkrBCO2jvFD+BvlGiUeKwBTUPZJJIIN73UMVtxCG9bNIo5FPn5Y2aRNJV+gT56OYlKX5oRWbGilV94cg+yCOnK8K+f2PN9NI62Egc1OQV+jB/HSGuGrCDFqM44WYZy/Qib/8iCD/nPDaeUuWG/LR6I7fmvNtsB4w==
*/