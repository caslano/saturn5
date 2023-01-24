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
l++FjgXvzwMPJ6oMH8OY2gLijkolmuO3JjXnb0IFdou+tYRTnr5M2fPkVE2/0r3olhUgc684JFiNcBzY37oao9Tja6PoI1b/lYm1kJxuYO/KO31OA1MCW9REVxEy3DFVyDskUtzaQpNBxIwTdT53MfR2VRYvFRpuSirHB4DsoExv2Qflb5vFP8c/icuSIr9PvjNxZkdKJNfZT45w7X7zUlNKdMGPtfsYaBxXPm6w2+Yl1ZXz0jWARdzxSSOFzjvvKlv704vIju/4HPjcW7ie15u22RwWlx7E6+xk+Do9HaPM/DBaBEDNySgM0x2d8Rs2Pdn+tT9+NAtuJ+10s4G8YxGteCHih828aYNwPRXcGWFc3jidvCoanxW3t6PcNI3cUnYowzYlH9uzS/pErmSubE/srV0WYk7T/wz6ESwy4uSJknjYzfquCb6PLlYVXCU7hLsFd6Jbwpir6W/p9+hfD25LuXnE7k/oVxDLU+/+Id1L4k1/xWqM7Pz3NB21m6ydoh15Bd0eiQdZL7imn2dH0VjQOYP3mPLAL+Qp+CmEoh+5n7VOOOo19H4nl4dnyGSnp58GxUFaRUTzagvg+oYPwf+vmlsIxx/r6gtsMTFGOoHdrZ+PiBOwMmc++VZXapKSIpOcF9mTmZ8YNzvGZITUi0VwS3hyJpgCoKt/4nbuAnSh377ZcWE6zcfJWTqxaVv3oDhTn+cmQD7SaRvh
*/