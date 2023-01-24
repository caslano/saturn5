//  boost thread_clock.cpp  -----------------------------------------------------------//

//  Copyright 2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_WIN_THREAD_CLOCK_HPP
#define BOOST_CHRONO_DETAIL_INLINED_WIN_THREAD_CLOCK_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <cassert>
#include <boost/assert.hpp>

#include <boost/winapi/get_last_error.hpp>
#include <boost/winapi/get_current_thread.hpp>
#include <boost/winapi/get_thread_times.hpp>

namespace boost
{
namespace chrono
{

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
thread_clock::time_point thread_clock::now( system::error_code & ec )
{
    //  note that Windows uses 100 nanosecond ticks for FILETIME
    boost::winapi::FILETIME_ creation, exit, user_time, system_time;

    if ( boost::winapi::GetThreadTimes(
            boost::winapi::GetCurrentThread (), &creation, &exit,
            &system_time, &user_time ) )
    {
        duration user = duration(
                ((static_cast<duration::rep>(user_time.dwHighDateTime) << 32)
                        | user_time.dwLowDateTime) * 100 );

        duration system = duration(
                ((static_cast<duration::rep>(system_time.dwHighDateTime) << 32)
                        | system_time.dwLowDateTime) * 100 );

        if (!::boost::chrono::is_throws(ec))
        {
            ec.clear();
        }
        return time_point(system+user);

    }
    else
    {
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            boost::winapi::GetLastError(),
                            ::boost::system::system_category(),
                            "chrono::thread_clock" ));
        }
        else
        {
            ec.assign( boost::winapi::GetLastError(), ::boost::system::system_category() );
            return thread_clock::time_point(duration(0));
        }
    }
}
#endif

thread_clock::time_point thread_clock::now() BOOST_NOEXCEPT
{

    //  note that Windows uses 100 nanosecond ticks for FILETIME
    boost::winapi::FILETIME_ creation, exit, user_time, system_time;

    if ( boost::winapi::GetThreadTimes(
            boost::winapi::GetCurrentThread (), &creation, &exit,
            &system_time, &user_time ) )
    {
        duration user   = duration(
                ((static_cast<duration::rep>(user_time.dwHighDateTime) << 32)
                        | user_time.dwLowDateTime) * 100 );

        duration system = duration(
                ((static_cast<duration::rep>(system_time.dwHighDateTime) << 32)
                        | system_time.dwLowDateTime) * 100 );

        return time_point(system+user);
    }
    else
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
      return time_point();
    }

}

} // namespace chrono
} // namespace boost

#endif

/* thread_clock.hpp
MI6fZMEa4CN13abHsyi7KLyx8qqYSxK6QbWtda5pnchfCCk6T0S/X3YMssuRl9bMzYS9E7zEkZduiJBFZAoQVj1hKxOM6Iwi0s6XJgIMHkQAxjPAV0gW17wQnSNC8snVAvggnVGvwxt3WROl702wJ/KJG2mGfeymfFQ7AwuV74hJbryS3lF0CZOnTL4XHXddqtRTx10Xb5EcbbkFqjj4qRLgga2FDO8nvpbhPYU/S+/eA7jAOpxFZccByyIBxZlCy6IT+LKbRiGUIJIskSCmJQyG1pxDGOwaAPjtUlgUMnh0XKgBb1g3cDIIk/alHgC96i4E94FnHck43CPSDcGsuepqUwOoNqs3VNX3mBp3IAXM7inamFazWx1s8kqEKadk1UrU73q8qZVKPoGzscRTetlndcS48RPoBGaSCXz7K4VgoE4DXD05Bbw4N05gdw2ki488oSbQ7Qz4WIqOTJwV1PVcBS52JiR8K+euwNxZ8HEDzV1Oc5ejo7oFOmo/+5ZcoBy9Euaw70vhsqLbuYGW2YBlcllaFi1jyYPvpMwK9j2DlvmKlvkKy6xmaWPlMl9hmXXseyItk0/L5GOZDSwtRi6Tj2Xy2fdIWmYzLbMZyxSytCZymc1Ypph9v6rHMoW0TCGWqWBpgl4qU4hlBPa9nJbZQcvswDL7WdoOucwOLCN5LPyKfC9K2k83Jyi2H4uBihSSV9JiPHwmpczs
*/