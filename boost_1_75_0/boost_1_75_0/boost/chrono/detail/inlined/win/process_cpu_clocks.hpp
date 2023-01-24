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
PvGx/zmv9xPja9MXDRvLlcK6xvJDf79jgbimmrF80D+Qsaz/2HssoX7Hcurzho2ld51jCfU/lhe9Y68d7RfIWH79yHssg8/5G0uLBo7lgS11jWVwv8Dib4QFNJbWPmN54qze94xYRT92fqfQD/82Vm/G1hkH7ILOx8YKNjlhM3YloNhrOcyyymM68rlkErXycxa7xmN6kr5C+LXzNwccfu1kL8k66kCvBodfe61vIOHX3llnqD3oVy3zbv+2vnnv0rdB8574YQPmvWy9NO+vrJfn/ZH18rzP6RrwvM/oKc37PT0bPO+d+gQy793XXv+8/7Cpvnn/OKZB8753bQPmvehTad49n8rzfv+n8rwbogKe9797SPP+S48Gz/va3oHM++cfXP+8Tyqob95jezdo3seuacC8530szfu8j+V5H/2xPO/8TQHP+9xbpHl/5JYGz3vvXoHMe/z7dcw72l66BCUW3NOC+i6mVq9bll+fXnde51CdIIz0q9dd2LM2ve6En9GRfGZb0w3X6w56z69e94U/yP6m6MhdWyOExd3AOHRkuDCPvpgFB7zwJbg5Vz7UTYkRS5hQ0/Y8GTKjyRYcqYPDkkgYZ3dCgcGoiIwD/XU164uO6F4upOcfEP/tXbRpjrl3+96EcWPQ2pU5y2P6ielS5Um97Xw1Pb+bdBHttcE4mQzXosM5BJ9f1vDTRsmbWysybjS0bsvy4PW5
*/