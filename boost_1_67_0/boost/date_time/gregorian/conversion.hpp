#ifndef _GREGORIAN__CONVERSION_HPP___
#define _GREGORIAN__CONVERSION_HPP___

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <cstring>
#include <string>
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/date_time/c_time.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>

namespace boost {

namespace gregorian {

  //! Converts a date to a tm struct. Throws out_of_range exception if date is a special value
  inline
  std::tm to_tm(const date& d)
  {
    if (d.is_special())
    {
        std::string s = "tm unable to handle ";
        switch (d.as_special())
        {
        case date_time::not_a_date_time:
            s += "not-a-date-time value"; break;
        case date_time::neg_infin:
            s += "-infinity date value"; break;
        case date_time::pos_infin:
            s += "+infinity date value"; break;
        default:
            s += "a special date value"; break;
        }
        boost::throw_exception(std::out_of_range(s));
    }

    std::tm datetm;
    std::memset(&datetm, 0, sizeof(datetm));
    boost::gregorian::date::ymd_type ymd = d.year_month_day();
    datetm.tm_year = ymd.year - 1900;
    datetm.tm_mon = ymd.month - 1;
    datetm.tm_mday = ymd.day;
    datetm.tm_wday = d.day_of_week();
    datetm.tm_yday = d.day_of_year() - 1;
    datetm.tm_isdst = -1; // negative because not enough info to set tm_isdst
    return datetm;
  }

  //! Converts a tm structure into a date dropping the any time values.
  inline
  date date_from_tm(const std::tm& datetm)
  {
    return date(static_cast<unsigned short>(datetm.tm_year+1900),
                static_cast<unsigned short>(datetm.tm_mon+1),
                static_cast<unsigned short>(datetm.tm_mday));
  }

} } //namespace boost::gregorian

#endif

/* conversion.hpp
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
*/