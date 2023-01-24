//
// detail/cstddef.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CSTDDEF_HPP
#define BOOST_ASIO_DETAIL_CSTDDEF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_NULLPTR)
using std::nullptr_t;
#else // defined(BOOST_ASIO_HAS_NULLPTR)
struct nullptr_t {};
#endif // defined(BOOST_ASIO_HAS_NULLPTR)

} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_CSTDDEF_HPP

/* cstddef.hpp
De/MIL2woxn6ctF6ZD2H7oCfZHfAuy/j4gPlNNV6hO9DXQJOB+kWbN8P2iM8cbi15iC/vaiWcFDioDnsGUxh5J8meYNGstamhteC5bcsqjx8/zKTBWMxX8cXr+ITQEEeHsn8MbVSd3wFdiz+kUoSrUeQ6taumOOKksqlufWJu/Vltjmzyel/sv1S+PKfQDcjSSPp0Q0Hid4so/RDMmAkPaHBv0N6YvdZtaLRlwCDmzS2YRBqgG0j5LcOMrnVD6iFGa9W1MOB1JNUR4ZCiZ0MxHJYwqQymu1oCNUwwt+jqcJ4a5ZN1Q/3dNAXNwKxAF3NO4H7X9EsdqgOPoMuTqPi4owlD49QQr6eAV2yYSJmhxoHXyDzmOPRRGYhsFzDEHquiziiWQBRweRGQCMn9AH1dYqe3ljB0tt8iu99CXmIvDxEOH1hJ0VhahAo+sqIYRWzkWs9ASHaFb8QoGt4ky78apwlUj2cTcwRcmA45s2UY0NNeVM9HAeroN5GTh1FdTvW7e8h9Al+D3CmfIrfS56BxqlJQhQponuAR0SjO78+wF9vJ7sw14k4fQC9k0GoJ+MxVtN3pbjCIE4QVxhfxVjl7tSLON0kWevF6XicV0xB+6pWmau+HM0QGkmupjDCNA2Jolp9HVRy51dzePy6px3ThIeR9CitH7vjfE06Qe3G4u9hvjZ1k2O9yOErZfKE9nOdbEp6SNb4wUlkOy1q
*/