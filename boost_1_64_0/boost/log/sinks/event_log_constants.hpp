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
LuUWtG3rz2JXxT9usvKpv7jdYuoT4w0maMdNTxLZORiI+XmdjVC7e1fiMgUsBNt2N07amNTDAb9NtTt5/zPPqlG3jbdF1W32SD23a3edkD+u3HoYhNuvHl31o/7c56LUg6eKe3WJh3vhl2vlaVtxa0c8nj0b5SwiHoYZjtlNn12aXP53Ye6JchkZv6x0jXt3SnSfbIr5M2vCxdsielQFk4tZo4/WEcuxsmeO+Et2zwe49w3Y9lUq7jVMNed8gA3vl4E/u4YerUeW49Sp86+hu9dw46+tu9d2462tx1+L3yVr6E/uK1x66byec4beVnjOZR1uXR9vrfZfvyb+a53PUtG1fveaePy1b/daecXXxH+tc158a+jy/O4LV+ga+ujInBY8V9dYEzHD1X+SFz4XIxU2gbVhV3go7AbTYH+9HgAz4DBYH+bBBrBQ3HUtzNP5KN/ae2bYn/w66zdk+sAm8ERdW+wLr9HzNlbC/nquyanwOThE114nwDfh6fBTeAb8Cp6l30wZBmvrGt1hukbXGo7QtdXRuuZeqGuD58LxcIyuBY6DS+F4uBIWwTvVfT2cAB/StcWXYCl8H06EX8NJ8Ft4PvwRToWBUDnAVDgFpkPspbx2RuYv4FtaP/Uwj/vOwUnStdpGulbbCbbXtdsG8DRdsz1Tz8EZo2uupervfF3DnQoz4XQ97+cSXdOdp2u6C3UtdxlsAe/Qc3/u0rXd7epvp4b7KzwS7tL0dsP2el+9PH0P1/mEyXpOUEevTAejOtwBW8Dn9DyfP8KOcKfe5/PwdPhXva+XYZHqZkxT3YxZsJrH/aiOxpWqo3E9fBsuUfeb4btcr4Yf6hr1J/A9uBcGVAejCvwC1lTdi0PhN/AY+J2uRe+DvdX/CfBH2E91Mk5TXYxhMAhzYQI8F1aDY2FlOAVWgbPV/kr4LOGvkuvIt430vU7fRyfHfNtomq7tz9I1/UvhkfAyLcfZeq7NlXAUvArOgPNVp+U6eBNcBO9WXYZ74WO6pn+j6j7cAvfBFdCoDkOy6ipkqK5CJlwNm6luQyt4p67t3606Duu0vDZo/9sIz4P365r8Zu2HD8FZ8GF4OXwMzoVb4A1wK1yt9mvhxfAeudb2Z3RMD9ppv6qEoUzk15fyDbEfrAYHwlZwKMyCp2v5L42MeeE9Gk8KZoHGcyT+5Gwt2BL2ga3h8bAN7AQHwi5wBOwKC+BR8Dx4NJwCu8N5sAecr/5u1HBLNd7VGu8avV4n13ruUGTsp/c+OebcoSaaz2YwDbaC6fBw2By20PtuCY+GR8Ce6u9z2FfGQlqeel0Z013jX646DitgdbgS1oB3wppwFWwK74CP+84x6ndV4n/EWUa/pR7Ef4MOxAjqZTJmHuZ2zBbMS5gvMUlXJ5oWVx/UgTj4O/j7V/1+q/X/cQW/fP0/jXmuxG6hcWzovVYiLZG5cOyrh+z/ZO2zi0aO5Iz3EpOJ20+h/bIvx7ply2YdWVNSPx19fjgVubSweGwhydo4ujrds0Mv2jaO7uJnZOEEjh0I+ywcn18wWfQU3vadXbBOzy44IQxzPKYGD8h5ayLzNiceP+C4Y7Pz2EwQmf8/tJns1bbf15bxgfjnvG1ZM0p070NdEzWX5p7TcfrLde4ZVH8HmquM0vEP5buu5rumnaNwfac5V+ZU10v8lHdbI9fb9TqlefQe0sZ6Zv3KAG7wVlgdP3vXxJ5HoFVBPfjPoC/1rSeedLfMfXNdyXQhlR7mSN6dDnGVp8bv3n8k28fXhtw/814mrt6eY37TGUdJzsgC9x5Nv1+dk8vP1/WW2rCn5D3VaxFKL6QZYwZxJx3QE2/u2K/kio8zx517lazf2PZn52I=
*/