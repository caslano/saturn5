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
h+ZR82Od1xE5ypPR/+qZgNtRfmspvzUib7hHX9NLyqKLV/WgJYq8ho825KHSvfjK9TNKNAeDVK7X6I3uSKhNb2RDxdFYkO7vxjNdRXtkSghEe2T5pm45v8dVaaCd5bfWV/XK+fzvUTceR+7Zc+NwJHhow3Gk4An/OJJccH048siZG4QjwBddL478O/jG4MhvX9aBI8bLEnBcrpHequW332sojjS9IuPIwRpEjquX8fHPZYYjFKaW3HTjYSq4+MbB1BeDGg5Tj8/0D1O3bLw+mGr15w2CqYig64epDwfeGJh64fM6YGrDRQl+1shvb8lvL16kMFVwSYap+RcRmNZdwsc7l/Refksi8YhceOsfyWhgKjMauOdzb6MB7zL7fcrcXG8Z4wXvMuc21FcmzqfMdz5l1OcOqjgtXXfK2wgnbSMs7ihzQKI9Ef8znlrLJyiu9CUffxOlW0PM/1Kp0OTSFZHeEFxEKlo4Nyomkoj38zrCnhNM9xyIzWi1hJt+6mbSnbdZ5odUhTDzErh5FWIrCq7AITGnZdPjJWV5jCxgaZTlGCUlc71BjpISqTlOhjt6F/TeMRFU82HdcX3z8VPcdczH1QsBz8e3Nwc0H+PjApmPqZ/VMR/r/6lrPkzbr28+9g24jvk4/U/A87Gya0DzkTwgkPlI+7SO+Vj1t94nxtfyL+u0/6k1LlbR1jrtf27za//TNsTb/ue2gOx/
*/