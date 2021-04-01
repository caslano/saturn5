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
iansfjae7z9EI86tBqOpGCmoSl2tT3D6qu8QLeUWbeyBLVSP7Xe05NivP4zdSek9B6P2AFMviq9M8OXIPDspKvk02gIx2bxDfZHq/wO1tHYr9GG4h/vAy2Z6OcufaE2B4QQr3cy/6vCfAnmrVIUtjcnFxlPxW10BrcNLv9Lrep2R6SfqUKpcEtdiAa+EHkHSvAxdUSHY0kq3/FJVAcu8HCzna0aeWM/UC4VLLo3Q9SbfiduCzaYT5y+/ZLBDraaY5TK8x4NHEzVKEB3J2byOpO0FNoMfXJKC9BUXPgv1zQ/eOhOewU8EajeryJtbQBG6KX8z4BGUW6toqSacSImQvGATLv6StFwtJulMDyJw+bOlNcWaFdexVs7+Z2k7o4HEfKa6qeVi0Ow83hSITbRTkK5NfF4swSqMSUmQXMFw5QrE5z20j5yTILmKfTkSEmw1Gc383fSEDbxCU9aMxKrkBJW37TEOS6uqTzUCCf06wqofdDf35GJd9JQN4RKiDr/ugDDc4e8hPPQ8sDFN1sG/yLTvif7i7Bg5JUH6bY3+WXCZwn6ngz0Qe5GQMA==
*/