//
// detail/throw_exception.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP
#define BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)
# include <boost/throw_exception.hpp>
#endif // defined(BOOST_ASIO_BOOST_THROW_EXCEPTION)

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)
using boost::throw_exception;
#else // defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)

// Declare the throw_exception function for all targets.
template <typename Exception>
void throw_exception(const Exception& e);

// Only define the throw_exception function when exceptions are enabled.
// Otherwise, it is up to the application to provide a definition of this
// function.
# if !defined(BOOST_ASIO_NO_EXCEPTIONS)
template <typename Exception>
void throw_exception(const Exception& e)
{
  throw e;
}
# endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)

#endif // defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)

} // namespace detail
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_DETAIL_THROW_EXCEPTION_HPP

/* throw_exception.hpp
tnF3EqrhIb8l9EFKYj2KTc4fVBJmvATPJ30Tr4HCLHIsS+gpvNaMKcm6tu7B2l3SNsJd9eadEuyXoCNZ0kP3Ibp9PRBc+xxb5kPvmmaLEAzQpMMWitWvEeQZzl0u34mHednBCL0rkK/fOzEZv41ssMD0sc7L4KIcJDjCeJNUIWjs0r6Qx3o+2PBqXTihcdirhVkRTQK0r++Zs86cAZYNDWIO+SbK9OPGXuDt6tQvV+dbLtWMELGo0+evH2Gm/9QYSEShZqAfK1svGZ7oMduNZ1t12ojkx/rtgsH1AeQWBKAr0eN/sjzEOEtpmjC/Gg2unNAEP12LIvIouXHWf4kfTvDu5R9yEUAPURfvgTLoCDFp8rJORxIePJsQ1TirWKh7bCon0NM5N1/huJpK8coceiKhhl7QvY7o1n/AVlcfoxBUXjdEIF7tPWUoxH7WYeolZJi0FFb3DazjBHldy53JAyu5NS6CQboTIuI+n+N3im46RloS2RXOSsLFnNv5ml9O4WiYM+vdHxWpDf0gxWZHlN80GK5oSrqFOB0mSiofOsm90beIkOALYkTkOg==
*/