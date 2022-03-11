/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   syslog_constants.hpp
 * \author Andrey Semashev
 * \date   08.01.2008
 *
 * The header contains definition of constants related to Syslog API. The constants can be
 * used in other places without the Syslog backend.
 */

#ifndef BOOST_LOG_SINKS_SYSLOG_CONSTANTS_HPP_INCLUDED_HPP_
#define BOOST_LOG_SINKS_SYSLOG_CONSTANTS_HPP_INCLUDED_HPP_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_WITHOUT_SYSLOG

#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

namespace syslog {

    //! Syslog record levels
    enum level
    {
        emergency = 0,                //!< Equivalent to LOG_EMERG in syslog API
        alert = 1,                    //!< Equivalent to LOG_ALERT in syslog API
        critical = 2,                 //!< Equivalent to LOG_CRIT in syslog API
        error = 3,                    //!< Equivalent to LOG_ERROR in syslog API
        warning = 4,                  //!< Equivalent to LOG_WARNING in syslog API
        notice = 5,                   //!< Equivalent to LOG_NOTICE in syslog API
        info = 6,                     //!< Equivalent to LOG_INFO in syslog API
        debug = 7                     //!< Equivalent to LOG_DEBUG in syslog API
    };

    /*!
     * The function constructs log record level from an integer
     */
    BOOST_LOG_API level make_level(int lev);

    //! Syslog facility codes
    enum facility
    {
        kernel = 0 * 8,               //!< Kernel messages
        user = 1 * 8,                 //!< User-level messages. Equivalent to LOG_USER in syslog API.
        mail = 2 * 8,                 //!< Mail system messages. Equivalent to LOG_MAIL in syslog API.
        daemon = 3 * 8,               //!< System daemons. Equivalent to LOG_DAEMON in syslog API.
        security0 = 4 * 8,            //!< Security/authorization messages
        syslogd = 5 * 8,              //!< Messages from the syslogd daemon. Equivalent to LOG_SYSLOG in syslog API.
        printer = 6 * 8,              //!< Line printer subsystem. Equivalent to LOG_LPR in syslog API.
        news = 7 * 8,                 //!< Network news subsystem. Equivalent to LOG_NEWS in syslog API.
        uucp = 8 * 8,                 //!< Messages from UUCP subsystem. Equivalent to LOG_UUCP in syslog API.
        clock0 = 9 * 8,               //!< Messages from the clock daemon
        security1 = 10 * 8,           //!< Security/authorization messages
        ftp = 11 * 8,                 //!< Messages from FTP daemon
        ntp = 12 * 8,                 //!< Messages from NTP daemon
        log_audit = 13 * 8,           //!< Security/authorization messages
        log_alert = 14 * 8,           //!< Security/authorization messages
        clock1 = 15 * 8,              //!< Messages from the clock daemon
        local0 = 16 * 8,              //!< For local use. Equivalent to LOG_LOCAL0 in syslog API
        local1 = 17 * 8,              //!< For local use. Equivalent to LOG_LOCAL1 in syslog API
        local2 = 18 * 8,              //!< For local use. Equivalent to LOG_LOCAL2 in syslog API
        local3 = 19 * 8,              //!< For local use. Equivalent to LOG_LOCAL3 in syslog API
        local4 = 20 * 8,              //!< For local use. Equivalent to LOG_LOCAL4 in syslog API
        local5 = 21 * 8,              //!< For local use. Equivalent to LOG_LOCAL5 in syslog API
        local6 = 22 * 8,              //!< For local use. Equivalent to LOG_LOCAL6 in syslog API
        local7 = 23 * 8               //!< For local use. Equivalent to LOG_LOCAL7 in syslog API
    };

    /*!
     * The function constructs log source facility from an integer
     */
    BOOST_LOG_API facility make_facility(int fac);

} // namespace syslog

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_WITHOUT_SYSLOG

#endif // BOOST_LOG_SINKS_SYSLOG_CONSTANTS_HPP_INCLUDED_HPP_

/* syslog_constants.hpp
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
*/