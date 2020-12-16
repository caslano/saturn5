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
qlnVhM9rVz+LrZ/gxeIeMOaXyP+xv7H8x07afftouS5tPsu+L5Q9JxY710l02Ufl/9Db3fL/wkZGfq/g2AQ+AUPyf+/qWPkvk+9++W/Hf3XvkHlYr7+pJycb3IqZ6aW6zzpaHV++J0s8a73o94b6yNit7jOPVpdfvqtfp3yvAxMl7fu8EciqyzF3Yx6lB7xG2i75rvE55Xc9+Ez4Xsi9W34PEvdFPvndpWz+9k7ZN2bleY74vYJ7/n1ceX6I+PkLvf8pO25vJHZ3efFkeX1xX+GdJJr9yeYmzDRklUuW14YjJF+p9NHq4qdDN8lHRCbLO2aZjJ+UM9YXNhgKK+O8Kr7nQOm4Yt9+5Trip5E9nyNZrhOM9P36+G7o6/u7tO9X0b6vfhZYP8GZMyrY959xzM32+437fqRP3xVnXdM39pPypg4IW7r/PGxjnavHeJhLMX9tT7u7a79+PXLi+Dxffyy286Onid+ZJp3/22FOxuS5v9eg8drz920ZW+PYa5JwwLN/iqPO2r+4iZHfYRogE/Mp5WTCZ7PJzeQVZ8uHNbT9Yp9fUupbl0oSvzWc+Te+c8U+zpDz0ybkmTjnTOx31pr0RTvfmiDu9Z1ySMM6ysJ91l3oPupyH/7zqcgfdpK/6POpNB/+cuuqBXacnp9+LKZ5SAcgttyys5zlVgd20zMBXeWWVYFyy/qZcuso7i0c5eYKy75eDZsK88S9sktWa1j3nuPua6L3HBeH/f7s/vFfUj/a79VO7iNqj5N7L1DF98BUdI/QB9s87J9aPvfODsnd6q04LGftxNIH3qv4nh/3nquK7wWq6N4k956fiu/1cu9BqvjeM/eeq3h7un69vWS+PU7yLJR+gl/d26L6LvRRx96WPbq35R1YSc+dj4Qzi+OH+0DDfajhPvKFSz5AuE813Gcabq8vXOMDhPtCw32p4b6y4TAHCPethvtOw+3TcKM91WtQXZFQuCMw7CuQXy/VrR4Cz9Rz1kfBM+AY3eswEZ4Ffw8fhHPhMNWdHg5Xqf198Bz4AMyGz6r9qzAHvg5z4W693qPXCeQlD1aG+bpnYiRsCotgK/h72AFeAm+Hl8I74ZVwK5wDn4Rz4XZ4DXwezocvwQXwNbgMvgmXwx/gKuiF9lrBunADPBzeB0+CG2F/uAmeDR+AI+GDcCI8DV4k13o+vafrmrpWPBm2M5K+/J7V8n5Hy/t9Le8PtLw/1PL+SMt7QiBc3h9reX+i5Y29lPdnWt57tbyxl/L+XMv7C/imXr+j19U92hesAb+CtaEJhMs5EbaHjeBRsDHsDg+HT8EWcAdsA/fAtvBDeCT8DHaAxGU6wsqwM6wO+8NkOADWgQNhJ3ga7ALPhsPhCHgOzIFFMA+eB/PhJDgKXgbHwOvhOLgVjodPwCL4F3gefB1OgJ/Ad0N7c/Ra60nXSWTtab96ukj3XtwAz4Q3wVHwZjgG3gInwqXw9zA/GK6nW3UPxjK4Su3vgyt0r9NK+Kzav6rn8L8Ob4e79XqPXieTl9UwFd4B0+FdMAs+CDvDJ+Dx8ElYCP8In4a7YKhdvwIT4DuwEdyr5fwDXA//Du+DVcnPLngyTKXd/g6mwX4wCw6E7eEg2A+eCgfAITAbDoU58HQ4Ep4Jz4dnw8thNtwIR8AHYQ7cDvPgCzAfvg1vJD975VrlXkDnHHUud7KO+ZoGdI8I/lrBeTAbXgvHwQXwPLgQXgCvgxfDaQnsyYGLuF4IF8M1ar8Z3sD1FngjfF7t34I3cb0H3gzf1ev39fpDvd6r1z/CW2Ao00thAC6DGfBu2BFugIPhJlgK74dT4QNwOtwCl8CtcBl8FK6C2+FOuAO+CF+G38B3IH3JfAw=
*/