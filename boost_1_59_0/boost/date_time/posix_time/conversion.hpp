#ifndef POSIX_TIME_CONVERSION_HPP___
#define POSIX_TIME_CONVERSION_HPP___

/* Copyright (c) 2002-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <cstring>
#include <boost/cstdint.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time_duration.hpp>
#include <boost/date_time/filetime_functions.hpp>
#include <boost/date_time/c_time.hpp>
#include <boost/date_time/time_resolution_traits.hpp> // absolute_value
#include <boost/date_time/gregorian/conversion.hpp>

namespace boost {

namespace posix_time {

  //! Function that converts a time_t into a ptime.
  inline
  ptime from_time_t(std::time_t t)
  {
    return ptime(gregorian::date(1970,1,1)) + seconds(static_cast<long>(t));
  }

  //! Function that converts a ptime into a time_t
  inline
  std::time_t to_time_t(ptime pt)
  {
    return (pt - ptime(gregorian::date(1970,1,1))).total_seconds();
  }

  //! Convert a time to a tm structure truncating any fractional seconds
  inline
  std::tm to_tm(const boost::posix_time::ptime& t) {
    std::tm timetm = boost::gregorian::to_tm(t.date());
    boost::posix_time::time_duration td = t.time_of_day();
    timetm.tm_hour = static_cast<int>(td.hours());
    timetm.tm_min = static_cast<int>(td.minutes());
    timetm.tm_sec = static_cast<int>(td.seconds());
    timetm.tm_isdst = -1; // -1 used when dst info is unknown
    return timetm;
  }
  //! Convert a time_duration to a tm structure truncating any fractional seconds and zeroing fields for date components
  inline
  std::tm to_tm(const boost::posix_time::time_duration& td) {
    std::tm timetm;
    std::memset(&timetm, 0, sizeof(timetm));
    timetm.tm_hour = static_cast<int>(date_time::absolute_value(td.hours()));
    timetm.tm_min = static_cast<int>(date_time::absolute_value(td.minutes()));
    timetm.tm_sec = static_cast<int>(date_time::absolute_value(td.seconds()));
    timetm.tm_isdst = -1; // -1 used when dst info is unknown
    return timetm;
  }

  //! Convert a tm struct to a ptime ignoring is_dst flag
  inline
  ptime ptime_from_tm(const std::tm& timetm) {
    boost::gregorian::date d = boost::gregorian::date_from_tm(timetm);
    return ptime(d, time_duration(timetm.tm_hour, timetm.tm_min, timetm.tm_sec));
  }


#if defined(BOOST_HAS_FTIME)

  //! Function to create a time object from an initialized FILETIME struct.
  /*! Function to create a time object from an initialized FILETIME struct.
   * A FILETIME struct holds 100-nanosecond units (0.0000001). When
   * built with microsecond resolution the FILETIME's sub second value
   * will be truncated. Nanosecond resolution has no truncation.
   *
   * \note FILETIME is part of the Win32 API, so it is not portable to non-windows
   * platforms.
   *
   * \note The function is templated on the FILETIME type, so that
   *       it can be used with both native FILETIME and the ad-hoc
   *       boost::detail::winapi::FILETIME_ type.
   */
  template< typename TimeT, typename FileTimeT >
  inline
  TimeT from_ftime(const FileTimeT& ft)
  {
    return boost::date_time::time_from_ftime<TimeT>(ft);
  }

#endif // BOOST_HAS_FTIME

} } //namespace boost::posix_time




#endif


/* conversion.hpp
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
*/