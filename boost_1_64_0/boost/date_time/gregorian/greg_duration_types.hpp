#ifndef GREG_DURATION_TYPES_HPP___
#define GREG_DURATION_TYPES_HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Subject to Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/int_adapter.hpp>
#include <boost/date_time/adjust_functors.hpp>
#include <boost/date_time/date_duration_types.hpp>
#include <boost/date_time/gregorian/greg_duration.hpp>

namespace boost {
namespace gregorian {

  //! config struct for additional duration types (ie months_duration<> & years_duration<>)
  struct BOOST_SYMBOL_VISIBLE greg_durations_config {
    typedef date date_type;
    typedef date_time::int_adapter<int> int_rep;
    typedef date_time::month_functor<date_type> month_adjustor_type; 
  };

  typedef date_time::months_duration<greg_durations_config> months;
  typedef date_time::years_duration<greg_durations_config> years;

  class BOOST_SYMBOL_VISIBLE weeks_duration : public date_duration {
  public:
    BOOST_CXX14_CONSTEXPR weeks_duration(duration_rep w) 
      : date_duration(w * 7) {}
    BOOST_CXX14_CONSTEXPR weeks_duration(date_time::special_values sv) 
      : date_duration(sv) {}
  };

  typedef weeks_duration weeks;

}} // namespace boost::gregorian

#endif // GREG_DURATION_TYPES_HPP___

/* greg_duration_types.hpp
9pg+zWxqiNIKACx2E6o7QBlpsICUTgnElTqbssNENMy1Jy8HH8CB2RNpumPWMifJD4gYKRf/xnpMuxZkT6mt6xT02gtZskR8TQNm72vTVeYQPeHGbM3DR8n9I821LFCBUxQ24Y4x3P3CVIvxmo2ubmhMBv40M48sONPu5uculczafhmjxP3ZvkDFep1Z7FpLxos0Zii5YMJI7QgmjIQt7lj/zesCikQGXxV0GKXhuhi8rBoXzWS+5afPObEZg1JM9U1m7Khc69rR/nrV0ikza4Uek81dePg+j5oB9mSGAXwFYlhgueEAEovUF0rS5rlrEMX0FtdA/HiJ3WioYYt4Xg1ozKdrGzwiNPvUfMTvseeWlJR2OopJb71V1Y3Qoe5CuRhyUVHmvcFEmkNaZHA3MSCuzB7I6VBOTrHtYmdRr0tOPK/aX0ObPf5F8axNOVBQFpSfodUzsLCJFHtgTLGHXch55CGin4Exl1AgJwTsPCT+/wYZ6JapL2f7YyIvNnqQOL9WUbnaF/KdU6+y67Q6T2IqIqNLsx3N9BU9I27JKLDlqVIoTVVHOaP8kA==
*/