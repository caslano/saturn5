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
/1p1G5S5qBozZRhCKw2vrYORroTocA4ok+gr5YKLgpvxVmsVY8kp55G60NQ/DGWTmJvFk6VcyF4vAKVRA4ztwZTLdvn7PMjbKbShRcof23iXuzcwIoKtU5ih28NnAxOvygv8QX5uxbsvD+qt93Sxps8cOjX++XKuH4hn4WZsxnUr1pynBPinoZJ6xq161rbaA5uJZAmzf1VVnadv2raSyBzwoGvMvcEXiuFSqkuHqzLFL7eAhwazxDmU+enKNMY0PEFP7u+do4jniRWRnAIEuN7k0QqjPG4jQJ03v4p6TvpSaNOo5fl2ALK9ZmVUQa/ygWhIlxPl1MRdWlKEcRpcqd7Pcfswhm8PUmRxaWrPf9Owd3cpvakx99gP4CO8auk/Wljbf+TuqXK2Zzr8HRncVWuLrT/rF00o8sWYFoZ0HOEDubVWLD6Ypjt+MDz5H7ZiYgvbpHw/qhfYNRfy0oxee26w8zgo4yDASoBDd6LC1VzPU/S+CqOORFSUSP6axAxQ1Eyl0d3mqnWtHZqY9v3bTYBofLtkVuK/Cbpr/47mLDbAFxeBXpc43nm37A==
*/