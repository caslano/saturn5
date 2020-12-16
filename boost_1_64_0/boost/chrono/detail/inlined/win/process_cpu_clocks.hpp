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
ebcpfn/mN+9UuApme+d5hyJ/VczjgbXAHLCBeTywI5gL9gHHg6PACbxPJ4IFYB44BcwHrwMngTeCU0CzzK8FnwCngs+A08B3wOvM+gfvBb8Ap/M+vAE8DM4w6x28h2t5jTbLFRzj8PS3aSzPSwL6W5Dl2AesLX2yq56u5BpP/Ti+/QrwInAA2In7Oa8Bv8fi2uX4vvMafMt5Un7m/AEnuUbbLzzub2AX8HfQzJ/iuH0DvAx0gleCYWAmGA4OB8sauh3zeyTakkU7LuLaWls4Xv8D5udDsB7nhWnOtfU6sl/P4PwuOdyfBx4Ab+ZaendyfpmZ4BGuvXcUfJTx3eV+gvnqa1HudxuufMzhfAYPcpz3Q5zP4BHOZ/Ao17RCHybl9Dive7fidyawmMdPlut0begz5bqHgtXNuDxfFtfMusNwXXc2zzcG7AaOBUdyfpKxjDcZzANv4TwkszgPyYPc/wQ4GTTLfwq4GLwWXAZOBQvBafzduQlcB94MbgBvAT8Abwe3y/Hc80rwew+/J6X6zSsxiM87gzmvxFVge/rN9Mn6+4R8X0F6OPwdZWh7hvRbE8BkzsdQEyxgu5jMNQVXs31cx3mDbmT7mKFc7fBWcJy0N1c53QnOAO9i/wIn8z7AydpjaCNSHvhbfn+fAjeBi8B3uRbcHvAF5brfl4D7wRfBo+Ay8EeuBfcrWAj+xjUSDcO1JmII52UIA18HY8GblfwOy/V8L+2W7/dgM5ZPJbYlJeWE+GA05x+J47wECQafu7i2WgrnIagK3gBWA28HL+XzSC3wGbA220EdcDlYn88fF4LblDxvyXNGG8N1vW3Bg2B78FuwA9tFJz5/dAHLmBoXMBLsCcaBvcEEsC+Ia5J81HIomdsg4wOZ26Ck9cf+FnMe/Je9K4GPojrjb3eTkFNyB5IAAbkvIyAgCgY5DJcGBERBk5AEQQLEJFyKgApyChFREBCigiJFjJYWbbENosUqtHiCFWukatFCRaUWrNb+5+1/387szmw2JPpr7Tz9+Ocd39vvHfNm5s33vu/HsHfQELYOrOwcFGMc14KqQSdB0X+MFK1BWaAJoDmgCtB2UDWoBnQWlHgY/tlAA0F5oHmg9aAq0CuHbTsIdrCDHexgBzvYwQ52sIMd7PBTCz/S+f/8gpLyBvP/F6s//4+qC4pK4P7PbQNgUZJQ+ttbub/1BiiF+G4afvtRdQav/4ABg3Lo/k/qZRzx8f/3mSy7h/omHt5UpYv5yGOI47+O0KuIEL7+/4w0LbZuPgGP6H0Csk2d+c2sL/XKeoP+hHI1j/m2CerU1Kc5YuITUGzVyjc7b5+A4S5zn4CZW/Xn7Dk41mcRWd7rE3Dw1tp9Ao7Z+sP4BPSc3cyz8AlY5W2bZ9rVeiZDrwcVHWJ+drN6a/BnN1E24NnNF7fW7+xmH8p6krKO5vgO4fmY025Ztes5KN94kJk8qUpHLXKbFr+U15ucRep6ayTzegU9hr6+8tK2KT9VMt6G8WIfvxwVuFglop3JxE3Iid2k2hfIdx7LtRGl1CG7RManhmg63+Wgf4MGYX3IBS0FbQf9DvQB6CtQuhP6W6BrQbeBNoKqQZ+C2uBDTx/QCFAeqBy0FLQR9JTLaXU+lTK18Duf2lbqsDEfLc0VGWI59JN/gy+BfRwX4/tKCnQURlr53SNfK1FKXbduMj495AbhEjNB34MG4wNrHmgZ6EnQAVAN6AyoGRQ6+oNGg24HbQLtA30Gagslj8tAV4PyQTNBy0CbQLtcIX5nV2fRr18XKUNZSF+Mwe0Y2Wcwv0Id2FMFTQKtBj0NOgT6BPQN6EKnU1zqjBXDQXfi70dBB0CnQU1c0DRE3w52xYo=
*/