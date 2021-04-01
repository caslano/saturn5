/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   to_log.hpp
 * \author Andrey Semashev
 * \date   06.11.2012
 *
 * This header contains the \c to_log output manipulator.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_TO_LOG_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_TO_LOG_HPP_INCLUDED_

#include <iosfwd>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/is_ostream.hpp>
#include <boost/log/utility/formatting_ostream_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief Generic manipulator for customizing output to log
 */
template< typename T, typename TagT = void >
class to_log_manip
{
public:
    //! Output value type
    typedef T value_type;
    //! Value tag type
    typedef TagT tag_type;

private:
    //! Reference to the value
    value_type const& m_value;

public:
    explicit to_log_manip(value_type const& value) BOOST_NOEXCEPT : m_value(value) {}
    to_log_manip(to_log_manip const& that) BOOST_NOEXCEPT : m_value(that.m_value) {}

    value_type const& get() const BOOST_NOEXCEPT { return m_value; }
};

template< typename StreamT, typename T, typename TagT >
inline typename enable_if_c< log::aux::is_ostream< StreamT >::value, StreamT& >::type operator<< (StreamT& strm, to_log_manip< T, TagT > manip)
{
    strm << manip.get();
    return strm;
}

template< typename T >
inline to_log_manip< T > to_log(T const& value) BOOST_NOEXCEPT
{
    return to_log_manip< T >(value);
}

template< typename TagT, typename T >
inline to_log_manip< T, TagT > to_log(T const& value) BOOST_NOEXCEPT
{
    return to_log_manip< T, TagT >(value);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_TO_LOG_HPP_INCLUDED_

/* to_log.hpp
R585B4go5hvwsGMfaKJKw6UhFjXljKZ8b0+FdZ/6kgFSGFLwGf8M7yHc2tVaAEOEd1Bq2ZiPAQc5vzm2+QknVhGdigqzU1Igv50EGJVzERPLaoXmcWZwbzoZIw3pai/zECxPtATjq9SpkXdCF/dw97pkoHCOkt9t73fnd6KUcJxGceAm0NbaYxSDpGmcYPavwediaqoIoKdz/M1MZF7oTwA3QBQcUiJeh7Xg2RQylTqgH/msaWgg1zlhAGJIdLxG01aHjL51r+/pf8rxsANYggGx0k8e6wZv5f5KvWLhpoenIUs4ldZmYUnduZdI/7uy1kmjnK+a+TuPzgtWhAFPYiVvyiibiDZzprL1DhddoCJJOvEutRj6qlAjt2J8Ge0pZCFQYi9LrJB04I0k0TV2Vmf9lW9wc5pajpthVlI7m5dK25FEBX9qL+nibjdt/s5m2IILp4jKM0xUbWJWpTOB4bmMPjglIOdfefyiw0ksH0abRsC1DGxhgXTZ1AexlYtToVacHFT4xu1w1ZHmkXehupsEoNvwjwHyJV9JSLOA+TDK+Rs3B3eEy9fXHA==
*/