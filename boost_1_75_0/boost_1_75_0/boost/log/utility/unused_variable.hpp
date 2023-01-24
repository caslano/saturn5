/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unused_variable.hpp
 * \author Andrey Semashev
 * \date   10.05.2008
 *
 * The header contains definition of a macro to suppress compiler warnings about unused variables.
 */

#ifndef BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(__GNUC__)

//! The macro suppresses compiler warnings for \c var being unused
#define BOOST_LOG_UNUSED_VARIABLE(type, var, initializer) __attribute__((unused)) type var initializer

#else

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
BOOST_FORCEINLINE void no_unused_warnings(T const&) BOOST_NOEXCEPT {}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

//! The macro suppresses compiler warnings for \c var being unused
#define BOOST_LOG_UNUSED_VARIABLE(type, var, initializer) type var initializer; ::boost::log::aux::no_unused_warnings(var)

#endif

#endif // BOOST_LOG_UTILITY_UNUSED_VARIABLE_HPP_INCLUDED_

/* unused_variable.hpp
XDENJMiBfEoWFxLnJ4h7x3xSLSWWz3CVzIFgQJ1kFqN7daTiu4U1M8UxFNZM5RgkAUohkScK6EkvqsDSibFyImdxyT7GDMSLcRHIGYuvbkCzEKwhxjC2H0vq2ofYNa9C/qMlxCml/iAMs4RqdTqLfLh2fGSFCAHkTKGpEHPDII4H5Tm6vxKMogvpurAZjDJMEEZrbkhTlAvusj3UQG4IL9adNEJVOhGiDxUkQGHwFivgJgwjRbZHYdBTPFiTjK84ahCTJwqAN4hrCeF28LITJQMk7RJ8G7gcLGJ0+enjH8rzypQwgYc4NsyNyFJIZ8op1iwGNZPBJ8coGpP5XSU0xbZRMveIDqf8frmCMiuCDseDzjQM0kwiKWPhCU7cUE7RGI1XlXr2GTkxykFJU0zRUdNHvljFxTYkWFHS1KUr2MXHI0Gly0SMjvUvIVNdyxATxZBgTTFVFw/FVZd8gb9q04vTWfmE5um4N/foGOl7sHFILs/wMUhQW8ccS2IWFMYm0PFiaJgh877NQoqrk8K/Po7Wa4rwSjDGysbjIG4NqJMWQZd2XQi1SGbgTxwqdFMIQcK/xnYxI3a2dUqcNVoL6KRhjePG610YDqa6wyySm1MEgAeZ8jPnYO8pCyO+TWPvc28tFhqqEcXPjbGEQ7vpUrLGWMaOPuAlL+DCusIa2uqyTshA6dxp1kQoIID7TxaUMiurjkaCoj8HXwX5
*/