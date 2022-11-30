//  boost process_timer.cpp  -----------------------------------------------------------//

//  Copyright Beman Dawes 1994, 2006, 2008
//  Copyright 2009-2010 Vicente J. Botet Escriba
//  Copyright (c) Microsoft Corporation 2014

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/chrono for documentation.

//--------------------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_WIN_PROCESS_CLOCK_HPP
#define BOOST_CHRONO_DETAIL_INLINED_WIN_PROCESS_CLOCK_HPP

#include <boost/chrono/config.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#include <cassert>
#include <time.h>
#include <boost/assert.hpp>

#include <boost/winapi/get_last_error.hpp>
#include <boost/winapi/get_current_process.hpp>
#if BOOST_PLAT_WINDOWS_DESKTOP
#include <boost/winapi/get_process_times.hpp>
#endif

namespace boost
{
namespace chrono
{

process_real_cpu_clock::time_point process_real_cpu_clock::now() BOOST_NOEXCEPT
{
    clock_t c = ::clock();
    if ( c == clock_t(-1) ) // error
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
    }
    typedef ratio_divide<giga, ratio<CLOCKS_PER_SEC> >::type R;
    return time_point(
      duration(static_cast<rep>(c)*R::num/R::den)
    );
}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
process_real_cpu_clock::time_point process_real_cpu_clock::now(
        system::error_code & ec)
{
    clock_t c = ::clock();
    if ( c == clock_t(-1) ) // error
    {
            boost::throw_exception(
                    system::system_error(
                            errno,
                            ::boost::system::system_category(),
                            "chrono::process_real_cpu_clock" ));
    }
    if (!::boost::chrono::is_throws(ec))
    {
      ec.clear();
    }
    typedef ratio_divide<giga, ratio<CLOCKS_PER_SEC> >::type R;
    return time_point(
      duration(static_cast<rep>(c)*R::num/R::den)
    );
}
#endif

#if BOOST_PLAT_WINDOWS_DESKTOP
process_user_cpu_clock::time_point process_user_cpu_clock::now() BOOST_NOEXCEPT
{

    //  note that Windows uses 100 nanosecond ticks for FILETIME
    boost::winapi::FILETIME_ creation, exit, user_time, system_time;

    if ( boost::winapi::GetProcessTimes(
            boost::winapi::GetCurrentProcess(), &creation, &exit,
            &system_time, &user_time ) )
    {
        return time_point(duration(
                ((static_cast<process_user_cpu_clock::rep>(user_time.dwHighDateTime) << 32)
                  | user_time.dwLowDateTime) * 100
                ));
    }
    else
    {
        BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
        return time_point();
    }

}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
process_user_cpu_clock::time_point process_user_cpu_clock::now(
        system::error_code & ec)
{

    //  note that Windows uses 100 nanosecond ticks for FILETIME
    boost::winapi::FILETIME_ creation, exit, user_time, system_time;

    if ( boost::winapi::GetProcessTimes(
            boost::winapi::GetCurrentProcess(), &creation, &exit,
            &system_time, &user_time ) )
    {
        if (!::boost::chrono::is_throws(ec))
        {
            ec.clear();
        }
        return time_point(duration(
                ((static_cast<process_user_cpu_clock::rep>(user_time.dwHighDateTime) << 32)
                  | user_time.dwLowDateTime) * 100
                ));
    }
    else
    {
        boost::winapi::DWORD_ cause = boost::winapi::GetLastError();
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            cause,
                            ::boost::system::system_category(),
                            "chrono::process_user_cpu_clock" ));
        }
        else
        {
            ec.assign( cause, ::boost::system::system_category() );
            return time_point();
        }
    }

}
#endif

process_system_cpu_clock::time_point process_system_cpu_clock::now() BOOST_NOEXCEPT
{

    //  note that Windows uses 100 nanosecond ticks for FILETIME
    boost::winapi::FILETIME_ creation, exit, user_time, system_time;

    if ( boost::winapi::GetProcessTimes(
            boost::winapi::GetCurrentProcess(), &creation, &exit,
            &system_time, &user_time ) )
    {
        return time_point(duration(
                ((static_cast<process_system_cpu_clock::rep>(system_time.dwHighDateTime) << 32)
                                    | system_time.dwLowDateTime) * 100
                ));
    }
    else
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
      return time_point();
    }

}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
process_system_cpu_clock::time_point process_system_cpu_clock::now(
        system::error_code & ec)
{

    //  note that Windows uses 100 nanosecond ticks for FILETIME
    boost::winapi::FILETIME_ creation, exit, user_time, system_time;

    if ( boost::winapi::GetProcessTimes(
            boost::winapi::GetCurrentProcess(), &creation, &exit,
            &system_time, &user_time ) )
    {
        if (!::boost::chrono::is_throws(ec))
        {
            ec.clear();
        }
        return time_point(duration(
                ((static_cast<process_system_cpu_clock::rep>(system_time.dwHighDateTime) << 32)
                                    | system_time.dwLowDateTime) * 100
                ));
    }
    else
    {
        boost::winapi::DWORD_ cause = boost::winapi::GetLastError();
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            cause,
                            ::boost::system::system_category(),
                            "chrono::process_system_cpu_clock" ));
        }
        else
        {
            ec.assign( cause, ::boost::system::system_category() );
            return time_point();
        }
    }

}
#endif

process_cpu_clock::time_point process_cpu_clock::now()  BOOST_NOEXCEPT
{

    //  note that Windows uses 100 nanosecond ticks for FILETIME
    boost::winapi::FILETIME_ creation, exit, user_time, system_time;

    if ( boost::winapi::GetProcessTimes(
            boost::winapi::GetCurrentProcess(), &creation, &exit,
            &system_time, &user_time ) )
    {
        time_point::rep r(process_real_cpu_clock::now().time_since_epoch().count()
                            ,
                ((static_cast<process_user_cpu_clock::rep>(user_time.dwHighDateTime) << 32)
                        | user_time.dwLowDateTime
                ) * 100,
                ((static_cast<process_system_cpu_clock::rep>(system_time.dwHighDateTime) << 32)
                        | system_time.dwLowDateTime
                ) * 100
        );
        return time_point(duration(r));
    }
    else
    {
      BOOST_ASSERT(0 && "Boost::Chrono - Internal Error");
      return time_point();
    }

}

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
process_cpu_clock::time_point process_cpu_clock::now(
        system::error_code & ec )
{

    //  note that Windows uses 100 nanosecond ticks for FILETIME
    boost::winapi::FILETIME_ creation, exit, user_time, system_time;

    if ( boost::winapi::GetProcessTimes(
            boost::winapi::GetCurrentProcess(), &creation, &exit,
            &system_time, &user_time ) )
    {
        if (!::boost::chrono::is_throws(ec))
        {
            ec.clear();
        }
        time_point::rep r(process_real_cpu_clock::now().time_since_epoch().count()
                            ,
                ((static_cast<process_user_cpu_clock::rep>(user_time.dwHighDateTime) << 32)
                        | user_time.dwLowDateTime
                ) * 100,
                ((static_cast<process_system_cpu_clock::rep>(system_time.dwHighDateTime) << 32)
                        | system_time.dwLowDateTime
                ) * 100
        );
        return time_point(duration(r));
    }
    else
    {
        boost::winapi::DWORD_ cause = boost::winapi::GetLastError();
        if (::boost::chrono::is_throws(ec))
        {
            boost::throw_exception(
                    system::system_error(
                            cause,
                            ::boost::system::system_category(),
                            "chrono::process_cpu_clock" ));
        }
        else
        {
            ec.assign( cause, ::boost::system::system_category() );
            return time_point();
        }
    }

}
#endif
#endif
} // namespace chrono
} // namespace boost

#endif

/* process_cpu_clocks.hpp
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
*/