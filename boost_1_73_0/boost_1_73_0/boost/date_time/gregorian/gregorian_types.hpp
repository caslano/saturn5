#ifndef _GREGORIAN_TYPES_HPP__
#define _GREGORIAN_TYPES_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

/*! @file gregorian_types.hpp
  Single file header that defines most of the types for the gregorian 
  date-time system.
*/

#include "boost/date_time/date.hpp"
#include "boost/date_time/period.hpp"
#include "boost/date_time/gregorian/greg_calendar.hpp"
#include "boost/date_time/gregorian/greg_duration.hpp"
#if defined(BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES)
#include "boost/date_time/gregorian/greg_duration_types.hpp"
#endif
#include "boost/date_time/gregorian/greg_date.hpp"
#include "boost/date_time/date_generators.hpp"
#include "boost/date_time/date_clock_device.hpp"
#include "boost/date_time/date_iterator.hpp"
#include "boost/date_time/adjust_functors.hpp"

namespace boost {

//! Gregorian date system based on date_time components
/*! This date system defines a full complement of types including
 *  a date, date_duration, date_period, day_clock, and a
 *  day_iterator.
 */
namespace gregorian {
  //! Date periods for the gregorian system
  /*!\ingroup date_basics
   */
  typedef date_time::period<date, date_duration> date_period;  

  //! A unifying date_generator base type
  /*! A unifying date_generator base type for: 
   * partial_date, nth_day_of_the_week_in_month,
   * first_day_of_the_week_in_month, and last_day_of_the_week_in_month
   */
  typedef date_time::year_based_generator<date> year_based_generator;

  //! A date generation object type
  typedef date_time::partial_date<date> partial_date;

  typedef date_time::nth_kday_of_month<date> nth_kday_of_month;
  typedef nth_kday_of_month nth_day_of_the_week_in_month;

  typedef date_time::first_kday_of_month<date> first_kday_of_month;
  typedef first_kday_of_month first_day_of_the_week_in_month;

  typedef date_time::last_kday_of_month<date> last_kday_of_month;
  typedef last_kday_of_month last_day_of_the_week_in_month;

  typedef date_time::first_kday_after<date> first_kday_after;
  typedef first_kday_after first_day_of_the_week_after;

  typedef date_time::first_kday_before<date> first_kday_before;
  typedef first_kday_before first_day_of_the_week_before;

  //! A clock to get the current day from the local computer
  /*!\ingroup date_basics
   */
  typedef date_time::day_clock<date> day_clock;

  //! Base date_iterator type for gregorian types.
  /*!\ingroup date_basics
   */
  typedef date_time::date_itr_base<date> date_iterator;

  //! A day level iterator
  /*!\ingroup date_basics
   */
  typedef date_time::date_itr<date_time::day_functor<date>,
                              date> day_iterator;
  //! A week level iterator
  /*!\ingroup date_basics
   */
  typedef date_time::date_itr<date_time::week_functor<date>,
                              date> week_iterator;
  //! A month level iterator
  /*!\ingroup date_basics
   */
  typedef date_time::date_itr<date_time::month_functor<date>,
                              date> month_iterator;
  //! A year level iterator
  /*!\ingroup date_basics
   */
  typedef date_time::date_itr<date_time::year_functor<date>,
                              date> year_iterator;

  // bring in these date_generator functions from date_time namespace
  using date_time::days_until_weekday;
  using date_time::days_before_weekday;
  using date_time::next_weekday;
  using date_time::previous_weekday;

} } //namespace gregorian



#endif

/* gregorian_types.hpp
A6kAQWT4mDBU82KsXnC27ODveeQbQVAmMSwx1DJ1goRb7yPv2Lt/iHEnpHwIJMXfOFQO+TANTXitGVQMUlATu+GF7uo0VHewwdaKFwk36KgmyT36sKW2z6K4aaXLTBneYQy1qx/A7JB0HTO2D6e2tezDyp4Au0PJgGMTwsDpmZ3BkTd8OLvjGIV82r1OZBGZQU6k3HZBd9V8SZV2RVm5cuBX1SXUCo6QFmm1Hd1ZoGSw4tEtZlXFi/TguN9RJLEHsdpkw5po+x5ZzXnMpHziIznUqKmMJgFyUbe+3bEscCQ0lDYzOlaU2twV5vIxLWPF1jRcYag76FV7YeAAukxKaXQVXG82rZ7a+W3BNRDe5dxqYZvFbnrdrFz4i/HcmSzGY7swnYXz8CwcR46lvFka/el/nI5Hdtzb4bXi8+7JaItC6AOMn8gOzGKf/nFeHFTz/QZbX4iCWXgUAzxc6u1uum5QvKTc9JAD7jbYO/qyQeYY7t7E9N/8n715h/31KJidh3R6ShfBZNQl+UaNzwTL5ujvnw3MQu82LSQPW8/40frRABcilp5Q6saM6OHA+dfxMmEb4X/yg7H/IRgH86Xjp2n7v8iJdzT0jq3BbDRfzCb0yR8vRs6Ma9ywyhY8isMrEllLCDO9TVWVNUax
*/