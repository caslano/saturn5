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
2WdMLGKIikvPbhhmLa1Tjb2dGH5vLBhg9sAg58qQCRUgC080iGF1tKOJTGFP7a2oa3qAy9sZuWFG5KzGBiteCEUvM4vJjOGb1pDIeLrLK6iktt9supwVJHSulqlTCRIHiWzEse1DKU4Z0dSo695tI7c42BtO/beFTzbYWYUsYXmFyuMtZNvVzLhZWPatyrAnIE7Wjdy2SSqbKzKZRKyn3UN+tp37LCq5pXPHc7eQ1DGrgjStEuUUq9mn2Ru6YR+HKS5quIDBi00ceIElnYV5LMSi22r6GE/xnsE83dWBd85uHZRLj159Q1GCbnkuShTGEfaSFRNaEZjgIt1y/dBlS216D9rGUGxvP3rC2dKo81r2BfJn9Z0E3/yLeeodTl1kp/AP+4cCw7raONvFMk7jWTxPPEdh2mq66zXBP1/MAytqTldsbn88UR1kghmijIhySIcj+NeD16JEBz8UoxcDQKCn3sh6bPjGIX/x/nsQK//SD+f+cTgP02vPLwr3D4bTd2uwDNKLZQSX/vwi8JYceYTLSsGCLD4D4d6QTvWpPbprab154V7JzvAiOoviqyiLrSyQEw7FdW2QBAH48yTGN8bx8llhMBh+GI1h8HA4i6MomKVZGr96tAySeH4Z7M+fYfnzNLmcPTz6H1BL
*/