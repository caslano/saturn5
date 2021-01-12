/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 */
#ifndef POSIX_TIME_TYPES_HPP___
#define POSIX_TIME_TYPES_HPP___

#include "boost/date_time/time_clock.hpp"
#include "boost/date_time/microsec_time_clock.hpp"
#include "boost/date_time/posix_time/ptime.hpp"
#if defined(BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES)
#include "boost/date_time/posix_time/date_duration_operators.hpp"
#endif
#include "boost/date_time/posix_time/posix_time_duration.hpp"
#include "boost/date_time/posix_time/posix_time_system.hpp"
#include "boost/date_time/posix_time/time_period.hpp"
#include "boost/date_time/time_iterator.hpp"
#include "boost/date_time/dst_rules.hpp"

namespace boost {

//!Defines a non-adjusted time system with nano-second resolution and stable calculation properties
namespace posix_time {

  //! Iterator over a defined time duration
  /*! \ingroup time_basics
   */
  typedef date_time::time_itr<ptime> time_iterator;
  //! A time clock that has a resolution of one second
  /*! \ingroup time_basics
   */
  typedef date_time::second_clock<ptime> second_clock;

#ifdef BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK
  //! A time clock that has a resolution of one microsecond
  /*! \ingroup time_basics
   */
  typedef date_time::microsec_clock<ptime> microsec_clock;
#endif

  //! Define a dst null dst rule for the posix_time system
  typedef date_time::null_dst_rules<ptime::date_type, time_duration> no_dst;
  //! Define US dst rule calculator for the posix_time system
  typedef date_time::us_dst_rules<ptime::date_type, time_duration> us_dst;


} } //namespace posix_time




#endif


/* posix_time_types.hpp
oHEsJY67Rb/Mgxyp0hXdJhlWv/dG1YEbM7+gOqr6eepgNEnPSFP0jAQgYZJ2fx0jbtnl2bJTnXIhq8fT6l/wKjIpTDUmorw2E+vV3jpBlfM5J/gkLZsW4rZFagm1YK7T0RxyQuaFQIg1eyH2HIbMr5ErU0KsRwqZe5HfIp+GU0QvTMjovbjz4sDokK1PYu9bn+zZWSfL9cfJz16hE0PLA/mEl+YJryBlhrMqPMRTzxLDLJHy
*/