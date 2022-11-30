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
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
*/