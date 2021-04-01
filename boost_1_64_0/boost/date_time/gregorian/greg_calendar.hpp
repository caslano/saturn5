#ifndef GREGORIAN_GREGORIAN_CALENDAR_HPP__
#define GREGORIAN_GREGORIAN_CALENDAR_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

#include <boost/cstdint.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/gregorian/greg_weekday.hpp>
#include <boost/date_time/gregorian/greg_day_of_year.hpp>
#include <boost/date_time/gregorian_calendar.hpp>
#include <boost/date_time/gregorian/greg_ymd.hpp>
#include <boost/date_time/int_adapter.hpp>

namespace boost {
namespace gregorian {

  //!An internal date representation that includes infinities, not a date
  typedef date_time::int_adapter<uint32_t> fancy_date_rep;

  //! Gregorian calendar for this implementation, hard work in the base
  class BOOST_SYMBOL_VISIBLE gregorian_calendar :
    public date_time::gregorian_calendar_base<greg_year_month_day, fancy_date_rep::int_type> {
  public:
    //! Type to hold a weekday (eg: Sunday, Monday,...)
    typedef greg_weekday         day_of_week_type;
    //! Counter type from 1 to 366 for gregorian dates.
    typedef greg_day_of_year_rep day_of_year_type;
    //! Internal date representation that handles infinity, not a date
    typedef fancy_date_rep       date_rep_type;
    //! Date rep implements the traits stuff as well
    typedef fancy_date_rep       date_traits_type;


  private:
  };

} } //namespace gregorian




#endif


/* greg_calendar.hpp
wtFT7Yy7ScGq5dW2lo536KcUS89zY7e48Mvof/FG7c0iXnU8BvqC18n6HEUGO/zVTzHd8fRfoz1Qx3SVuH+dzzuUjWonwXF5jjmXAEXvXny86dTcKZ3ycvBShJtfPzkAfobYPto7Tt5b3JY+TrwqjEiZhKOLerCYDlCqIuMTvcPq//SnoGT1AL2fMP/tT1Y/SAPzLH9DBVGesRcwqVXKJ5/3Q9mOhHvmwYF8gqpvB0MD4Vuvi8TmaQEn0Y9h673duEMiIF11cvpUPRydOHSOS+axcsSURtxNFIEQQL1KgheSvQhJRH7GW/cW7s2IHMLu+H9QsmrgBl3D/9ppAeXx4tdKFJOFe/2vIXpHWoIdPVdAEUxjsN5Cket3mOwk6uf5kvTlogwDvkF6GqkBbu0Vz6xI5CNzfUCfphZaGDjMy130RYtlonuDJb/e3SybDLIgTr7IztXD7RRr/mtExRlQpdsI9zWtDpfwVyUbV4GTiO2pG1AwynI6EKSc+CNg1wNYpCn7sni2+hQMoc2lIgqjX7GIIHavXnsA+Jk4NhznmeFm76RIm46x5/EjLg==
*/