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