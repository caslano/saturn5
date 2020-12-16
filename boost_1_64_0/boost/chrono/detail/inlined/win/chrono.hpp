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
1u+2mRLvMlUNIe45Z141w/jNLk+OPWLy+PHT4O8s5Xmr7I92v+fKWKnnSzFO6kzqw4yXJ/Uh5/apj48rKtn6sj668D45oevD/psIyx1xfe+T2DWmv5FNPTC+/X3C/fb3SbQcv4FlX9Jwje/zeZr4nbbP5ymyPzYgvn6P+BPvjd6VlWzFrIvtvDeGrdF1Yft9pRLLZprEXSv3xgC4m/T9wePY3x/cn6QqsR6niH+j3B9D4e6EY52xTjx1ZqyVb9Q+dZLE886T4yzC95xkvK0mItx9DJeVZOLIkTBEeOYOCZdjNeccQu4xrqVbW+RMvv+4f++mp1jPFTBshS53mSrApv0znv08Adwv768ZKJtaKWc+F8CkFSXPBZC3InAugBfOfC4Ar7Zr/61oYFUlW23Ob53CtacylrrLS4xKduXFeFV1PzxB/D+iZThgfRnGZyTsWGaGT1LhajDnCQhoszxWef28liP+GKOqMry+DZnfJDJZVu40NT1tWfYrPVfNaNkfYVRUTq84+XjF8NhGfpA4o61/d3kvLpA473sdI3v05AnjdD8ZLtc30Pp69e9B6cbNltTuUW4233ilXHz6oGE8STNkpyLH1ZljoNcv03XLnwP73+dDElcZVyHkRZXBencfozafEw2V/pLpH4I+oxvbfUD9Mk2Krt9i8ccak/T66L6/H6N1mvr+fZWu3y9kf4IxRRm29Xub5K2/d3+mn91jZN92vHvEWdQt617idLW6Vvv+j9c8V+I2Pu/9H8rX/lt/pvcYabuxuHZjj898LK71GGm7scTnb2yz9Vhuu7HB9mO8UyLN8JZrx85v0WV2v0PL7t4754lRrezGTtuNYbYbI33mY9TP19jyMx0LbTeW23/Nn9YcI43vnNKn/BN/P8m/74NbxL8fwHnc44JFw0G9RarfuOA9HJ9XDFYB94LudCdKSLeT6XYx3W6djhoHsJ5Fun1Mtx80ww4wXSHcMKb7gekSwEVMt5TjopeBDcFXwG7gcrAXuAIcDK4EM8FV4AjwdfBacDV4PbgWnAG+CT4IrgMfAd8Bl4AbwJfATeBK8D1wLbgFLAK3gu+DHzHfwxRt0WCm5Nt3fPe/ES8G/A1MBv8DtgR/B9uBYU7XeEUH2Bd0gpeDIeAg7nePexc7L+2GqX7j3r9muX4LJoDfgU3A4zzfSZ7ve7Pc6O9JP68DtlP766jodF1HCpgMVnG6jlvV6TpubV5HdV5HDV5HTV5Hba/rUKvsr6Ms1waJAhPAaKfrOsrxfEk8XxzYjf6e9Ou1nnj8cIv214Lj2VtyHHwr77WemC4FrvU5joOf56ANizZA5EPG4M6kpmih4bq+pw1JL+OjO3NNoe5cUyibawmNBvs5XON7rwBzwQFs18uwfzrjPcw1h+ZxzaHHuNbQU+AK8DVwJfg6+Cr4Ftce2sTjFvG46KZk/PROhu9m+JfgBoT/xPCTDHcYrvHSEeB2MMZw7Y8zXPtTwE857rwYbMn9rbm/C3gI4d0Y3p3h/cDvED4IPA4O5f5h3D8O/MlAOTB8GsNvA/+N8AfoXwD+Dv93jHeC4b+CIWC4w+VPAMuC3R2ueD0ZfgUYA2aBsWAO94/j/ilgBfP8DL+e4XeAKeAshj/gYH7AVHAxWBN8mftf4f41YD1wM1gffI/7t3D/LrCdWR9gB/AI93/N/T+B3UDD6VqrKRTsAVZyyn6Ou+Z3fNoDUv3GXd+PeCZngSHgA2BZcA7nZ5gLxoEPcZ6G+WBl8DGwGvg4WBN8ArwAXAjWB58CG4PPgE3BReyfnme+8hS/ufObfarfmmCDed9dzbWJhoKJ4FiwKpjJNdSywbqSDr8LHGdtHnsUeA84BpzFdOY=
*/