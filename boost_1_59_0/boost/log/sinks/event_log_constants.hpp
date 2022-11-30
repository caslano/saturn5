/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   event_log_constants.hpp
 * \author Andrey Semashev
 * \date   07.11.2008
 *
 * The header contains definition of constants related to Windows NT Event Log API.
 * The constants can be used in other places without the event log backend.
 */

#ifndef BOOST_LOG_SINKS_EVENT_LOG_CONSTANTS_HPP_INCLUDED_
#define BOOST_LOG_SINKS_EVENT_LOG_CONSTANTS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_WITHOUT_EVENT_LOG

#include <boost/log/detail/tagged_integer.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

namespace event_log {

    struct event_id_tag;
    //! A tagged integral type that represents event identifier for the Windows API
    typedef boost::log::aux::tagged_integer< unsigned int, event_id_tag > event_id;
    /*!
     * The function constructs event identifier from an integer
     */
    inline event_id make_event_id(unsigned int id)
    {
        event_id iden = { id };
        return iden;
    }

    struct event_category_tag;
    //! A tagged integral type that represents event category for the Windows API
    typedef boost::log::aux::tagged_integer< unsigned short, event_category_tag > event_category;
    /*!
     * The function constructs event category from an integer
     */
    inline event_category make_event_category(unsigned short cat)
    {
        event_category category = { cat };
        return category;
    }

    //! Windows event types
    enum event_type
    {
        success = 0,                 //!< Equivalent to EVENTLOG_SUCCESS
        info = 4,                    //!< Equivalent to EVENTLOG_INFORMATION_TYPE
        warning = 2,                 //!< Equivalent to EVENTLOG_WARNING_TYPE
        error = 1                    //!< Equivalent to EVENTLOG_ERROR_TYPE
    };

    /*!
     * The function constructs log record level from an integer
     */
    BOOST_LOG_API event_type make_event_type(unsigned short lev);

} // namespace event_log

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_WITHOUT_EVENT_LOG

#endif // BOOST_LOG_SINKS_EVENT_LOG_CONSTANTS_HPP_INCLUDED_

/* event_log_constants.hpp
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
*/