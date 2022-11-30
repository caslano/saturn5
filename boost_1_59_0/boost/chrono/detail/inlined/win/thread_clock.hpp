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
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
*/