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
2KDOlS/Msz5SIUikeFX/Z81GyzYOyvbOl+4uaiLYUN/ECHIySlqJRUteMbrQP7ihcXV3i/HMLEXaVK9v7iabVCwzHjyji30fu19wutyiZNPY1Rw0fMWkuDFU3xi9JRSoctriwFJA95qr25QPEioTD+xVAxy07w/smW83dWi0PJkuqJ21fEYf1RZQjxvSBBvA/wjr44ISa+fAKiQYRyNlejC3JPJ0n3aqDBTauZGZKL2Q1RhHMrQ8kzlNx/7NdX86RGxJFTqpRmC0yie8L+Us0S8Q1QGbg71ILFCQLP1bAuZnlRB35WSJQ+oXsWG7TuX/z56yVgpmAtZVqkuqB4LG9owcpxpA4ySa7pkoyJIs/yVAVZS2SfcJZufSywnY4lv7PhRvJAevpTMzfQLo66ChvVmy7bHP9Fmtj5yEppKWvLLCETZDWpY+SBMX5VQoxdCiLhzEy92BXG2EwlBs7ZNh5eg39h+DFytg7RzFg1WMhVp7xABrzBjymthuA0uHfoWDhZZ6DcKDBnBwljVkiQtl8MrrEUxXS3m4o6+F1aN/2Hmx0NvIgnjHXnF5qQ==
*/