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
/HXVECKkbF60qudMG207D0VvDJR5TrFqCLyMsnnbKh0zT0Q48w2BMs/sKiFESNl8wfKcaWNt56GFrg+Uea5ghcDLKJvNlTtmnohw7esCZZ5brRxChJTNnpU9Z9p42/X7ttcGyjz3WSkEXkbZnG6ljpknIjz8mkCZ5ykrhhAhZTO3YiDMM6miPu7qQJnneSuEwMsor8ut0DHzRIRXXxUo87x7+RAipLyWl/8LzBOx3ndloMxzZLkQeBllc6/lOmaeiPCNKwJlnp8uG0KElM2TlvVcD5l5Gcf6xeWBMs/YsiHwMsrmZYWOmScinOzyQJlnqhBChJTNh5bxXA+ZeRnHOutlgTLPhZcJgZdRNl9ZumPmiQiXvTRQ5rnO0iFESNn8dinP9VCk7Ty0/iWBMs/tlgqBl1E2e5fqmHkiwj0vDpR5HrFkCBFSNjNLes600bbz0NEXBco8z1giBF5G2VxyiY6ZJyK89MJAmedti4cQIWVz48U9Z9pY23nojgsCZZ6P50PgZZTNXfMdM09E+PL5gTLPZi6ECCmbx+Y8Z9p42/X7R+cFyjx/XiwEXkbZvGCxjpknIpzovECZ53RhREjZvHfRQJjnRCrqKc8NlHmmFw2Bl1Fe64t0zDwR4QLnBMo8l1skhAgpr+8v/BeYJ2Jd8exAmecGC4fAyyibPy7UMfNEhFufFSjz3GuhECKkbE67kOd6yMzLONZ9zwyUeQ4uGAIvo2zOs2DHzBMRnnpGoMzzsgVCiJCyueoCnushMy/jWK88PVDmeWc2BF5G2dw82zHzRISPnhYo83xl/hAipGweOL/neijSdh567dRAmefH84XAyyibw/N1zDwR4Q+nBMo8e8OIkLJ53byeM2207Tw0ySmBMs+Z5g2Bl1E2H5inY+aJCOc+OVDmueQ8IURI2WzM7TnTxtrOQ8ucFCjzLM4dAi+jbH49V8fMExFudmKgzHPXuUKIkLI5xVyeM2287fp99+FAmedhc4bAyyibs8/ZMfNEhCecECjzvCATQoSUzRUyPpin9egK6VREXR9NYg2pW2u0Zh2Dv4cfmE4l91yjJRw6Nt2Ao6H10qmhcScOrXBEeaH7raHVVWn1YwsL1Y9ZPT2PbTmkbo5Z/YiCNXQE1YDNeko41eBH58EkC2dNqOJ1a+h+65gj7JJWfY7C3KyyS4ffbf+NTHZkaefRURjVIF7oyearC/8wah360Cuq+OCT3at7da/u1b26V/fqXt2re3Wv7tW9ulf36l7dq3t1r+7VvbpX9+pe3at7da/u1b26V/fqXt2re3Wv7vVfv6xjVk8nq7lIJNIcif4was3dWLY6oEoLPYevtQrN5MIzRvRXYb1D6m60doz6v/1F2EEzW1ure+u4Sbbtnylibb1eOrW6MikMJQ5d9pjE8Ecj1uEP5R70aH+9dJ/oxGqtTljKjWWphjKtbqw/6vl12qIQwhwdSgxaQ/XmIcrYrs/fqi1UH7p/THBM4sSPbvXuomG8+Dts+Eo+ukI0M6quBz3GtxKxQ0MUUVWe7F51c2RtrxmXtd2hRwXruNXT6ebxC84YUbGkP9ryoy2qUdFUYbLbEtE7WpLHoqoGJON67387OfH9LI4Jcd+YOC7E0058P0YWw9Vh9E8+iXQhJFW5b7Lb6upP8vnmHUjL3Kun+4bWU8V3hh6f+H43p450bzr6PY1JmsckrcZkGhqT49ZLWy0A7L/AjJGPVkCKCzYs3DCZOGhmCO5vxFu9s55vWlsrSCD8zGCi1w8mXfA5LTp89a92h1sAPCaRFvkZl57sNjQyVbSFxPubSZGrqdKqdVb06Ww5FNPqfDkUKVYkHIoMKyYghYpvWv/xmfGaQai1Xyg=
*/