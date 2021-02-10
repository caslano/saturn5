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
EUhqig3uaLBsX4bRDM6W8eXgzKJ8kGUhkSEhDQ5kO18qeYdlyCvAlJD8oaCMcyC5aQnnW4fatwMXGTWegymMkpwjOioMUxSNNtudDBQlNgfONyT/C98MjiccFzhJnG5s0lJQr6cL8x14IThzypIq9Aqkli3e7Ljl1h/yQJWSSge9qs/C1Sz1VpZ+t7JYxmk8iWeJd0nE1i1Nfw8vF7OpF4jS65rHpffuQWsxwcwedgor9+ziPvztQddGnWCckt+BFUNmKX/j4f/fdKZd2HUk3nwYlabBs4XeE5x3NMBqjPHcM0wQd0QZooKbz6P9Z/lbzOIQZ+nh7FnmDwfCLonHW/FkQc3UXdZvvH+8oGSOtPATSig8jWZReu1ZcYJum0biWUuKojuzT4Kj4+DAWS+n6Wo5h0/hbDX1ll2pHZJpFn8E1o2AXnv2fOlc0aI75TrD1fzjPL6aZ7EbUnYTCrQr8yiZTiGcJTGO4NPld1LsuhNG2J/I+SPKhmXvX1BLAwQKAAAACAAtZ0pS99wm67UEAABDCgAAOAAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfSU5GSUxFU0laRV9MQVJHRS4zVVQFAAG2SCRgrVVhU9s4EP3uX7GT+xI6xoHS
*/