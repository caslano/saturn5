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