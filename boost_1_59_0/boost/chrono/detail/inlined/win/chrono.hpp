//  win/chrono.cpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2008
//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_WIN_CHRONO_HPP
#define BOOST_CHRONO_DETAIL_INLINED_WIN_CHRONO_HPP

#include <boost/winapi/time.hpp>
#include <boost/winapi/timers.hpp>
#include <boost/winapi/get_last_error.hpp>
#include <boost/winapi/error_codes.hpp>
#include <boost/assert.hpp>

namespace boost
{
namespace chrono
{
namespace chrono_detail
{

  BOOST_CHRONO_INLINE double get_nanosecs_per_tic() BOOST_NOEXCEPT
  {
      boost::winapi::LARGE_INTEGER_ freq;
      if ( !boost::winapi::QueryPerformanceFrequency( &freq ) )
          return 0.0L;
      return double(1000000000.0L / freq.QuadPart);
  }

}

  steady_clock::time_point steady_clock::now() BOOST_NOEXCEPT
  {
    double nanosecs_per_tic = chrono_detail::get_nanosecs_per_tic();

    boost::winapi::LARGE_INTEGER_ pcount;
    if ( nanosecs_per_tic <= 0.0L )
    {
      BOOST_ASSERT(0 && "Boost::Chrono - get_nanosecs_per_tic Internal Error");
      return steady_clock::time_point();
    }
    unsigned times=0;
    while ( ! boost::winapi::QueryPerformanceCounter( &pcount ) )
    {
      if ( ++times > 3 )
      {
        BOOST_ASSERT(0 && "Boost::Chrono - QueryPerformanceCounter Internal Error");
        return steady_clock::time_point();
      }
    }

    return steady_clock::time_point(steady_clock::duration(
      static_cast<steady_clock::rep>((nanosecs_per_tic) * pcount.QuadPart)));
  }


#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
  steady_clock::time_point steady_clock::now( system::error_code & ec )
  {
    double nanosecs_per_tic = chrono_detail::get_nanosecs_per_tic();

    boost::winapi::LARGE_INTEGER_ pcount;
    if ( (nanosecs_per_tic <= 0.0L)
            || (!boost::winapi::QueryPerformanceCounter( &pcount )) )
    {
        boost::winapi::DWORD_ cause =
            ((nanosecs_per_tic <= 0.0L)
                    ? boost::winapi::ERROR_NOT_SUPPORTED_
                    : boost::winapi::GetLastError());
        if (::boost::chrono::is_throws(ec)) {
            boost::throw_exception(
                    system::system_error(
                            cause,
                            ::boost::system::system_category(),
                            "chrono::steady_clock" ));
        }
        else
        {
            ec.assign( cause, ::boost::system::system_category() );
            return steady_clock::time_point(duration(0));
        }
    }

    if (!::boost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return time_point(duration(
      static_cast<steady_clock::rep>(nanosecs_per_tic * pcount.QuadPart)));
  }
#endif

  BOOST_CHRONO_INLINE
  system_clock::time_point system_clock::now() BOOST_NOEXCEPT
  {
    boost::winapi::FILETIME_ ft;
    boost::winapi::GetSystemTimeAsFileTime( &ft );  // never fails
    return system_clock::time_point(
      system_clock::duration(
        ((static_cast<__int64>( ft.dwHighDateTime ) << 32) | ft.dwLowDateTime)
       - 116444736000000000LL
       //- (134775LL*864000000000LL)
      )
    );
  }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
  BOOST_CHRONO_INLINE
  system_clock::time_point system_clock::now( system::error_code & ec )
  {
    boost::winapi::FILETIME_ ft;
    boost::winapi::GetSystemTimeAsFileTime( &ft );  // never fails
    if (!::boost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return system_clock::time_point(
      system_clock::duration(
       ((static_cast<__int64>( ft.dwHighDateTime ) << 32) | ft.dwLowDateTime)
       - 116444736000000000LL
       //- (134775LL*864000000000LL)
       ));
  }
#endif

  BOOST_CHRONO_INLINE
  std::time_t system_clock::to_time_t(const system_clock::time_point& t) BOOST_NOEXCEPT
  {
      __int64 temp = t.time_since_epoch().count();
      temp /= 10000000;
      return static_cast<std::time_t>( temp );
  }

  BOOST_CHRONO_INLINE
  system_clock::time_point system_clock::from_time_t(std::time_t t) BOOST_NOEXCEPT
  {
      __int64 temp = t;
      temp *= 10000000;
      return time_point(duration(temp));
  }

}  // namespace chrono
}  // namespace boost

#endif

/* chrono.hpp
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
*/