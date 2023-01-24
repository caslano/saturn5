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
liqQKYYsB2sYOmvyl77NHlsgTvT6+LFFOM9IE3+ADZNuRSr5BZt2mKaVKt12/Pwf3+uR1a5RqbU2hfwI9fczTCWTx5Qv8O4BjkHu+Edobmik7Kp9iEakkTmukfxZH6LtVjDHiTWLNNJ6lZ4zzO1mwItI8P7VxsLbRETbDGnbyYMBREXTnCmbfsu6cp9y0ZB2oWnV8/GQ+t5WhIBpKVUmG9KVAaB0BUk1SNuhU0h3YtOPR4qXpsly45omnvcCW0dXJ/lupp1fi3pZuj5ZZrAnwdhcuQU3+CFMe5tNfmJD43eR2nO8Lp2SJwCxd57ZziEzrmSEu13SlY9eQegkyoDpSx+Mh2mD/sg/8smqetROiKf/1yFVqEHZsuJdlzd71wHWk26goMwVLOZMbc9Ooup+DtGb54R0tkUpAVA1zalxWlD+s8nD2uZ633tgVDsrYsC6YqIds117LLFbdQmUJxwZRJr95zxvd+eMf8w/Jb+RGOu+PZAeA0RpIPWg/rBhxxoEjCQSBA4mMueVIXhcEsZJ43PcGi7+00dMRIgMwgyClGRM//s8np6UU3kvcZmcpxDup7mV2hsBubSSh1AIp0K4Sgy7TELT+3gnVJ6f6nBBjiO0mW47I9BgiYoNhA8+6Rp59KGtx418M+VNzjla7R56a9rvQDbLfH1bcdTxoSPatyF6Z+TcI0OtyK/h2RN5xYhyP3d+XOOGKb2Wg8jm
*/