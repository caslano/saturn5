//  This code is based on Timer and Chrono code. Thanks to authors:
//
//  Boost.Timer:
//  Copyright Beman Dawes 1994-2007, 2011
//
//  Boost.Chrono:
//  Copyright Beman Dawes 2008
//  Copyright 2009-2010 Vicente J. Botet Escriba
//
//  Simplified and modified to be able to support exceptionless (-fno-exceptions).
//  Boost.Timer depends on Boost.Chorno wich uses boost::throw_exception.
//  And Boost.Chrono DLLs don't build in Win32 as there is no 
//  boost::throw_exception(std::exception const&) implementation
//  in Boost.Chrono:
//
//  Copyright 2020 Ion Gaztanaga
//
//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#ifndef BOOST_MOVE_DETAIL_NSEC_CLOCK_HPP
#define BOOST_MOVE_DETAIL_NSEC_CLOCK_HPP

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <cstdlib>


#   if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32))
#     define BOOST_MOVE_DETAIL_WINDOWS_API
#   elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
#     define BOOST_MOVE_DETAIL_MAC_API
#   else
#     define BOOST_MOVE_DETAIL_POSIX_API
#   endif

#if defined(BOOST_MOVE_DETAIL_WINDOWS_API)

#include <boost/winapi/time.hpp>
#include <boost/winapi/timers.hpp>
#include <boost/winapi/get_last_error.hpp>
#include <boost/winapi/error_codes.hpp>
#include <boost/assert.hpp>
#include <boost/core/ignore_unused.hpp>

namespace boost { namespace move_detail {

template<int Dummy>
struct QPFHolder
{
   static inline double get_nsec_per_tic()
   {
      boost::winapi::LARGE_INTEGER_ freq;
      boost::winapi::BOOL_ r = boost::winapi::QueryPerformanceFrequency( &freq );
      boost::ignore_unused(r);
      BOOST_ASSERT(r != 0 && "Boost::Move - get_nanosecs_per_tic Internal Error");

      return double(1000000000.0L / freq.QuadPart);
   }

   static const double nanosecs_per_tic;
};

template<int Dummy>
const double QPFHolder<Dummy>::nanosecs_per_tic = get_nsec_per_tic();

inline boost::uint64_t nsec_clock() BOOST_NOEXCEPT
{
   double nanosecs_per_tic = QPFHolder<0>::nanosecs_per_tic;
   
   boost::winapi::LARGE_INTEGER_ pcount;
   unsigned times=0;
   while ( !boost::winapi::QueryPerformanceCounter( &pcount ) )
   {
      if ( ++times > 3 )
      {
         BOOST_ASSERT("Boost::Move - QueryPerformanceCounter Internal Error");
         return 0u;
      }
   }

   return static_cast<boost::uint64_t>(nanosecs_per_tic * double(pcount.QuadPart));
}

}}  //namespace boost { namespace move_detail {

#elif defined(BOOST_MOVE_DETAIL_MAC_API)

#include <mach/mach_time.h>  // mach_absolute_time, mach_timebase_info_data_t

inline boost::uint64_t nsec_clock() BOOST_NOEXCEPT
{
   boost::uint64_t count = ::mach_absolute_time();

   mach_timebase_info_data_t info;
   mach_timebase_info(&info);
   return static_cast<boost::uint64_t>
      ( static_cast<double>(count)*(static_cast<double>(info.numer) / info.denom) );
}

#elif defined(BOOST_MOVE_DETAIL_POSIX_API)

#include <time.h>

#  if defined(CLOCK_MONOTONIC_PRECISE)   //BSD
#     define BOOST_MOVE_DETAIL_CLOCK_MONOTONIC CLOCK_MONOTONIC_PRECISE
#  elif defined(CLOCK_MONOTONIC_RAW)     //Linux
#     define BOOST_MOVE_DETAIL_CLOCK_MONOTONIC CLOCK_MONOTONIC_RAW
#  elif defined(CLOCK_HIGHRES)           //Solaris
#     define BOOST_MOVE_DETAIL_CLOCK_MONOTONIC CLOCK_HIGHRES
#  elif defined(CLOCK_MONOTONIC)         //POSIX (AIX, BSD, Linux, Solaris)
#     define BOOST_MOVE_DETAIL_CLOCK_MONOTONIC CLOCK_MONOTONIC
#  else
#     error "No high resolution steady clock in your system, please provide a patch"
#  endif

inline boost::uint64_t nsec_clock() BOOST_NOEXCEPT
{
   struct timespec count;
   ::clock_gettime(BOOST_MOVE_DETAIL_CLOCK_MONOTONIC, &count);
   boost::uint64_t r = static_cast<boost::uint64_t>(count.tv_sec);
   r *= 1000000000U;
   r += static_cast<boost::uint64_t>(count.tv_nsec);
   return r;
}

#endif  // POSIX

namespace boost { namespace move_detail {

typedef boost::uint64_t nanosecond_type;

struct cpu_times
{
   nanosecond_type wall;
   nanosecond_type user;
   nanosecond_type system;

   void clear() { wall = user = system = 0; }

   cpu_times()
   {  this->clear(); }
};


inline void get_cpu_times(boost::move_detail::cpu_times& current)
{
    current.wall = nsec_clock();
}


class cpu_timer
{
   public:

      //  constructor
      cpu_timer() BOOST_NOEXCEPT                                   { start(); }

      //  observers
      bool          is_stopped() const BOOST_NOEXCEPT              { return m_is_stopped; }
      cpu_times     elapsed() const BOOST_NOEXCEPT;  // does not stop()

      //  actions
      void          start() BOOST_NOEXCEPT;
      void          stop() BOOST_NOEXCEPT;
      void          resume() BOOST_NOEXCEPT; 

   private:
      cpu_times     m_times;
      bool          m_is_stopped;
};


//  cpu_timer  ---------------------------------------------------------------------//

inline void cpu_timer::start() BOOST_NOEXCEPT
{
   m_is_stopped = false;
   get_cpu_times(m_times);
}

inline void cpu_timer::stop() BOOST_NOEXCEPT
{
   if (is_stopped())
      return;
   m_is_stopped = true;
      
   cpu_times current;
   get_cpu_times(current);
   m_times.wall = (current.wall - m_times.wall);
   m_times.user = (current.user - m_times.user);
   m_times.system = (current.system - m_times.system);
}

inline cpu_times cpu_timer::elapsed() const BOOST_NOEXCEPT
{
   if (is_stopped())
      return m_times;
   cpu_times current;
   get_cpu_times(current);
   current.wall -= m_times.wall;
   current.user -= m_times.user;
   current.system -= m_times.system;
   return current;
}

inline void cpu_timer::resume() BOOST_NOEXCEPT
{
   if (is_stopped())
   {
      cpu_times current (m_times);
      start();
      m_times.wall   -= current.wall;
      m_times.user   -= current.user;
      m_times.system -= current.system;
   }
}



}  // namespace move_detail
}  // namespace boost

#endif   //BOOST_MOVE_DETAIL_NSEC_CLOCK_HPP

/* nsec_clock.hpp
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
*/