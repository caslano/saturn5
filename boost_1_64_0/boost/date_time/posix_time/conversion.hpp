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
9jgj+hs3+Zf3Q5ap+I6doy/B/t3G+sm+a0g/SeYRtjL3pOfoodbVr38TyUTIIRR10+E/JXEBB7zU0ksIXkL0EmZDF1jX/XnR4nBPF1SE+aOc5IWkWkxCiFhC2x/Zcc6noFaaCn6U86ZCyKFCGVYwubX5ucNMrkQWr1elucjwPIw4s4QNxrADxnIDM+yAscIVY5iLjMgHEMoHUCkb5AxgpK3NDkX2cm94XrkqKrcSbViwblF1nlKmRwi36EejZIByYeD4B5bo6cNeChAGrIDp6dnwUi1qB5xqB1xq48xRTek2QJVOgCpdAM0sAKjaCVC1C6BwAUA1ToBqXABNLwCo1glQrQugUAFA450AjXcBVFcAUNAJUNAFULAAoDonQHUugMYXABRyAhRyAVRbANB0J0DTXQDVFAAUdgIUdgFUXQDQTCdAM10AVRYAFHECFHEBFCgAaLYdyGwXIP4BQGAxQt4tqUgOZN8cOwSBzucGxWuH8oECULxuUPwA5UgB5WhXKFvSTlzpgyxMX41F0/QegHewrZDFZKZane7xBPi//bnrg05bTOsztEh0gzCAh55a9hCA/fHm9Di1AeMyAbO2T5KSuTf9j22Qzwfl9CCFRzqsW79FOf8nOnoTKrUTNsedEDv7aVXJLMZ4CeAhmJUV8BDUVR/RmS/4UJs7t76ymkr5vcpZh6t6MRGOOTBUX36Wrt1RGbBVJGV5vb8CViPBvAWZxwB9B/fqplNgEV+tCKcpFq/YdsCJXWmzbF23SPekuDhmnkc6mhqN9c2X4x6otaFrooVb1bJ/jYNY/QAkkm+dQmX8JB3Z6rf/HKd2xA2wI15rdsRBZZ7NfBmMTh6xP4w+7ffkXPD0WV4cPpmbdEz/dgtvUqGn4W2IZ5rGcwXiieXj6fqIwnOUjwPnmqsFmnS07ya+FAOjP0pf5aRp9n1LjIl5ng4jwZEzInDwGN/wTldq9pGanPQ/HMg5GMj5plcw9XylGoivF/b4/u6Grtmav19RIOArOfhIB+4eo9Es/4cDdzd+WKE5zis8+BgfWeST5DuJu2o2ZqJaY/GE+ALNKv0ddsY8Hrias7FqBdyWI7zGw2QbhOPzHGMcrhRQvJoDbIR3vqXDBeZlo0EabNnJVaFoNgCw4QmA7ngRPDHa9oFneFqK/hqIWbPhPM2GK//uwO1H5ys2fIAuYBHkkAIHqQQFTqoewOMTwrxUw5ziBPMCgPlHupkHLoKFZQ3HGPKB0Gn3oKZPdST0GW6QtuwErPlMwG+0Y7MZCFFlXwC1SNU9ikj2pYBqRCWpmZZo2q7/mwNtPzhHqZlOy8x8m4QqkABxxS/HmtfomkmnmjdBzTH05RGBqwM6qM9+DV2r9XjcR1XV+snkKjhrusc89dzg9EsYKn/fS8zUGQFmqrPhbXDO+EQQ4lG1mFOzVTcHrjtiw1gLS6K0OUA/LogGqJh+76jWhX2q8KCuEECqAEagI1r5ZOH8QIF8+M9yy++qRYH/CdPqoAKmFuLZAN+XQImVcEfCvnxHQjDPX0u1qLZ4ixz5fdfFhJk0FREa2WFg/uq4fK6UgSzpSH3Nil4vsnd1Q41mc1d0e39pHCZKiEew3lb4RLWY09Jq+0KkN2dlPqlNG83wBHg3ff/bjNi/Mff9n4knwGfBQEqaETKPHbE7AumXvzDW+M4lFS3kwHn09v5Sj7jn/bBrRQXHq9inLDT61Ld1aGroFhEYC6Ja8cuUWRz0ilNqZkmdMpgW9/bTHVEmvM5JTZpDFXzfUzbAyxlorNGpqjMnP/PR1W+5qIuicsxUjlHlmKx8q48rXf8JXBTUPuIxRHxtnnaDzSzycVJPPWq4x+k6D+i3kaxZxhA=
*/