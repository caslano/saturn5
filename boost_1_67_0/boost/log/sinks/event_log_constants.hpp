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