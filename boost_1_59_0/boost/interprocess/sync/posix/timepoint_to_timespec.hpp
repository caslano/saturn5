//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_TIMEPOINT_TO_TIMESPEC_HPP
#define BOOST_INTERPROCESS_DETAIL_TIMEPOINT_TO_TIMESPEC_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/mpl.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/detail/timed_utils.hpp>

namespace boost {

namespace interprocess {

namespace ipcdetail {

template<class TimePoint>
inline timespec timepoint_to_timespec ( const TimePoint &tm
                                      , typename enable_if_ptime<TimePoint>::type * = 0)
{
   typedef typename TimePoint::date_type            date_type;
   typedef typename TimePoint::time_duration_type   time_duration_type;

   const TimePoint epoch(date_type(1970,1,1));

   //Avoid negative absolute times
   time_duration_type duration  = (tm <= epoch) ? time_duration_type(epoch - epoch)
                                                : time_duration_type(tm - epoch);
   timespec ts;
   ts.tv_sec  = static_cast<time_t>(duration.total_seconds());
   ts.tv_nsec = static_cast<long>(duration.total_nanoseconds() % 1000000000);
   return ts;
}

inline timespec timepoint_to_timespec (const ustime &tm)
{
   timespec ts;
   ts.tv_sec  = static_cast<time_t>(tm.get_microsecs()/1000000u);
   ts.tv_nsec = static_cast<long>((tm.get_microsecs()%1000000u)*1000u);
   return ts;
}

template<class TimePoint>
inline timespec timepoint_to_timespec ( const TimePoint &tm
                                      , typename enable_if_time_point<TimePoint>::type * = 0)
{
   typedef typename TimePoint::duration duration_t;
   duration_t d(tm.time_since_epoch());

   timespec ts;
   BOOST_IF_CONSTEXPR(duration_t::period::num == 1 && duration_t::period::den == 1000000000)
   {
      ts.tv_sec  = static_cast<time_t>(d.count()/duration_t::period::den);
      ts.tv_nsec = static_cast<long>(d.count()%duration_t::period::den);
   }
   else
   {
      const double factor = double(duration_t::period::num)/double(duration_t::period::den);
      const double res = d.count()*factor;
      ts.tv_sec  = static_cast<time_t>(res);
      ts.tv_nsec = static_cast<long>(res - double(ts.tv_sec));
   }
   return ts;
}

}  //namespace ipcdetail {

}  //namespace interprocess {

}  //namespace boost {

#endif   //ifndef BOOST_INTERPROCESS_DETAIL_TIMEPOINT_TO_TIMESPEC_HPP

/* timepoint_to_timespec.hpp
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
*/