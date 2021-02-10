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
9EYPDd4vg9EtekMgqwH+XBluMQsDYl1JwfMj8q/Y6bM7oHouObPbpVCo4TtofQv3zGQlWvrtRQtaUqxoD3yXvE/OP3u+Z6pmshUl6R2Mevf96ATpDNuATMdgF0FrWFJr0XY+LH0YjSfpII2Sa/hGqEzWOYcr2htsVn6McGkArZv5dAhvjgna0LkM7Lf99GY6mMwG41HkC1PUKiNvw7q2Dla86RuDD/slLH7GpAwGwnQNd2gMi+l6MqKJSlyTFI3+p+bycGhkaiihqtobW/ua7XDtrk09gFDop4JlPAmOIUZYFNf383S2KCahTRl622DBK61yoR7DJqejRTE4nDiTHPWu2u86FLcpeWDR6Hnmz0PoGt3CHVo1GhQ+4VzkoDRNHMNZvt3xB9xHqVdMBi09bAxHlIeFKNfYeigSq51eIx/hbBMIh6ImR42RuWSSjr+upRNnriRObIeMYc1jsFhgHv0nOR2AUg1hZ5YVfF8bYkCBEJbg8U7XBrEqo3E4YbuueMaoLFQJHoBONQ3yoTI0lqhnsV21epRbYPmTsGEaBKmk3oQxuT8tEmClhDYxrIKIiPk/R0HpDY6uAjBDLJCXKuXBhmGeV6FmCkGum/bAQAyn0RMAgasngTmuuSJ3/lELw+ke7Y2DIecOh7Of
*/