//
// detail/assert.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_ASSERT_HPP
#define BOOST_ASIO_DETAIL_ASSERT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# include <boost/assert.hpp>
#else // defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# include <cassert>
#endif // defined(BOOST_ASIO_HAS_BOOST_ASSERT)

#if defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# define BOOST_ASIO_ASSERT(expr) BOOST_ASSERT(expr)
#else // defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# define BOOST_ASIO_ASSERT(expr) assert(expr)
#endif // defined(BOOST_ASIO_HAS_BOOST_ASSERT)

#endif // BOOST_ASIO_DETAIL_ASSERT_HPP

/* assert.hpp
xvoyPG9KXrkfWs5tk0D++BMPidZG/dEdm5aZLOLcs9BxclMgac5schvrANPH3IdrZ6YMIt+fXljjl+aedRMD1J/8BDTN3weakm8gmXY/boyAutOImR2M2PAaZRT48NANsBx9eqicdg4vcbn9BpbVDddPchM7+zk3k22Zz5Z3LeLIr0vUOe6eybYrptM7h39w0MxMuFVIcUbW4WWee2LxKPLXeKmGYHS4wsi0VnrdNUx44/V044aQ6+levbJZoh7DCiU0E6aQYPuuAEVeEIrHrWFcAxgNlMx+VMNBMoM17sEamK9VwgRAPyDx1ZHhSyh2QM477GQcBibsMZEe8NKdEmb2lGLCGCBPawUjDbPnHzpKqCRZfYMn71P0fFTBo7qJ5sJnMC/M3UCFXjzXayNfz1RUuRiqyj0O5Q1LkK/kt4Fx9TAepnbpqBFIRt/KMnRIzUjPmVQbaVsPGqexEHcSZ8Ev/6Q0/lbvU2FQlnZq2U0sI9PBVlSmMH/VULx93HoWhzZGmuv3Pk4rVi0bvB5kwNmiiMypwDLn+tfr8OcUEX/R3oWtIJ/TmpfrZuJ2vhDjWuAkB+pwhGmNvjDMJZC3BMZEwXSSEd+qS2kHJeRTYCTj2m14ERWXHVgLWy5ba7c5Scs3au31OA0fuBSM0xW18xzD+UsuinM+Db/9nzLag5+PcY11knL5SRjrXaFzLQAli71oxGIH2So/IY0b
*/