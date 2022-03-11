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