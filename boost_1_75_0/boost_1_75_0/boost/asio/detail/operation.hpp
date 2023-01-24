//
// detail/operation.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_OPERATION_HPP
#define BOOST_ASIO_DETAIL_OPERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_IOCP)
# include <boost/asio/detail/win_iocp_operation.hpp>
#else
# include <boost/asio/detail/scheduler_operation.hpp>
#endif

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_IOCP)
typedef win_iocp_operation operation;
#else
typedef scheduler_operation operation;
#endif

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_OPERATION_HPP

/* operation.hpp
0e8j9PcU/T1Gfw/Q38OIzoun+xVWBX9czmfx+gaMBKoWqigEYSuCxuwPUXC1cZBc73K2EE1sIgDN9Lea/u6Cv1Xur+jva92UMKTyU7Se7tsNV+kuDgoAv4U8dVrzjPw1gnCoRjhUsdSoN0vNAn7PTD6IwIRDrzVUwE25ocZvcNEtmXfLWU0bXMyaa5WJzis/MJot1ZIbO4bqf+d2KkJ9c1KfnceCWHAeJoKGzd84qHdDk6FNnnwFq66RWII4A7nOKyVmFC/NyBBHwRV/03FYetPIAXpfkd40qD93S2/qvWc3vFmBc98rvRnh/byiY4rjSjlGajCoI0Itgv67ynAzftMAtFNtGD7w3E7eO/jz7upB/B60RXbjD6mmMRJoGZW7ngx6Lid22jMVLrCiRF4R3XRW86byagWXgNVxHHkisZKt+PvuE4Owq7WNkcAj4A0+1J6T6CPYMU+0VnSUiNM5pIqOFWJcRccawVkHTze8qQMu3+PDgtevcJjS4YYZbmCaFOlNs+cjOidQjPzGiBnXOuIqHtRf7RgKEgCUBAyR2/wMC92/it//TFkPdT/fwwPL8np4YNkCPK8UKufi2SFUzuzhAWbX9fAAM4xzR1TgnMDJw4fY7cRlwD+EuD1PVbtOc9OMtSn7cMTZZZeht51MC2ejPq3KiXf5OkLtTnwMSn2hL7RdSqIFbisFfAmo+HqBj5PkLxI2v0s+bRuQ
*/