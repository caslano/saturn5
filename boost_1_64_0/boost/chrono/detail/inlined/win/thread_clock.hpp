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
60G3u1AHaC3+ftwVp/wGvrnFq3t/ROe7pJTzt6OUaxbO6kaI2SCHI0JkgyaCVoB+Bvo96Djoa1AL+FocABoLugO0GbQfdBLU3hUh+oJyQAWg2aAVoM2gKlekiPf3S6hsiByRcgwWXbE+Rmrf2OiDcAXQzPfgNOBLibWvnZ6zkumVxrOTH23xnp18fYu/j8HfeNPUOcQd3jR1RvBBldajtzqH6E1TfgKXbfY/Yzlqs//ZyQ6bTfwJPmw8E3mBJssmT1pvGV+t4r1kPFfFe8q4nAfKv6BBP7LeZxQ9a9Q4bsNfxzNTI3lmKu9RtUYF9C9YKssN1PsXJG+87/xVa/NKmd/GrSvMebM4CF1hH5+BBt3ugfQReAvbUch2HH5EtcPMR6Bqx99kuatFtrcd5E0TqdB/n4B+isZv3AM5XS3DQlxNNReBjQzPNrK9Jj4CQ2V7L8HqFtMgPgLXWvgIrNqo2lqrj0CUtdb9Z76Vj8BPN3p9BGajTy4/Dx+B+zcGPhdQvdH/XMDqup8LCMpH4HD6CLyHtrFupY9A4e3PQD4CWa6Dmt8dZHyClY9Als9Q9psyZHy8qY9ATYwLZf6N7BsP/4WW9laGbfQ+C0ldHRlvpPxlZcn4YFplQhnEbpVpof7XLK+PXjK/O+OqPM93Sl1vue6Xo2/uC8qP7Pn5FNSPWyXPV2+CAC2I72vnjrapcQvkM5DlMpWOfoWMjw7Z6ojRvacVqDXiXpl/XcgWRxLH0lNHF7+xAI/0xbdY5ueG7HHofQCWqbEt3C7PfTk89/52T/CsE+VFCe3BU91zP5flm4hkGWd5PPkkiDGOeY5CHZ9k854BlXzP8R3IwzfP0UTkOAL5CLz+cfeZJvoIlPVnyfkxZfok/EA8hhP6kqzvBWcqNEI2Y060Fb7vpiZ+BQP7DZRz6vtErw82B+g+0EhQLmgUKA80HNQ5XhKeMbw+jveDQpAX6eZleu1nEdTzxpPe541GT6hnAXWP/8fj/vf9yU/620J46nF/uwf9ZBptF/D54OltRjsF6FODn8GUJ839DOb5+BmcrN7rMXcZz5JxOWbyneWNJ5RvQePzQIL/Wvgy0nI2qGvK0pfgUAfL6dbCuTI+wcqXIMt718ISGR9v6kswBVi2wbAWkt96Ldy4wbgW/mqDcS2s2OC/Fu7bEHgtXLLBsBaivPla+HA918LAvgNt34B1OT9jdb7l00gtPW7l56eTO5buSnni3xdU9Cvr/v/pGzDdxDfgPfQHOB5/078O9yflXqeff50C6u0XAlMYTwXeDOwKnAwcCJwCHAG8BVgAnAqcCywGrqG+4M+oL7gHOAN4EFiizg9wPxLYV/ifHxhHveXx1LPNo57tjcCLgTcBezP9S4lyn9DSb2BL+g1sDWwDbEP96nbALGB74ABgJ/oN7EC/gR2B45jO8xLY47P2GziQ/TeI5yUG69pbvbXh/AZKfVnWN1r4+3Uso3+yWRy/2dTXnMP+mwu8TKeneTtwCPAO1p/j4p4O9720+m/W2od0QT3UZOBSYDPgcuo3rqLe8Wqew6gAFgMT0X+30n/jAurtrmR8A3A99R4foj7sFuBBYCX1XR+hXuM24Fc8/xHucNebDEwCtgZuR3oH4JPAK4A7gONY7kaWmwrcSf99TwFnMn828xcDdyF9BfBp4DrmVzIfefK8yHPAZ4G/YX418/8A/AXSjwJ/CTzG/D8z/yTw10j/ArgX+A/m/5P5ofTDFwHU0qOAWnpT+uNLB74IbEW/fG1YrgfLXQn8PdKzga/Rz99B4LXAQ8CxLD+O5SfRj98Upk9l+lz68VtAP37LgG8DK1huDctVAt9B+g76+XuG+T9n/j7gu9p4At8=
*/