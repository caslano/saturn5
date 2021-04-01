#ifndef BOOST_DATE_TIME_TZ_DATABASE_HPP__
#define BOOST_DATE_TIME_TZ_DATABASE_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <string>
#include "boost/date_time/local_time/custom_time_zone.hpp"
#include "boost/date_time/local_time/dst_transition_day_rules.hpp"
#include "boost/date_time/tz_db_base.hpp"


namespace boost {
namespace local_time {

  using date_time::data_not_accessible; 
  using date_time::bad_field_count; 

  //! Object populated with boost::shared_ptr<time_zone_base> objects
  /*! Object populated with boost::shared_ptr<time_zone_base> objects
   * Database is populated from specs stored in external csv file. See
   * date_time::tz_db_base for greater detail */
  typedef date_time::tz_db_base<custom_time_zone, nth_kday_dst_rule> tz_database;

}} // namespace

#endif // BOOST_DATE_TIME_TZ_DATABASE_HPP__


/* tz_database.hpp
bsOV2ORD31+6V3cjD5Bxx78m0oGnxp3Vg1A8SkJVdIthk9FIYbrFinf5fofS+CkG7m5Do/sd6cEkhWJoECIwWegjyeB/De0BDBbwbfDGd9RwB4JHZO6vHMoTjHhLx4mZZxb5oOCiOHWCp1TNCgqJXp631y/t55hdHVvA1SiwPv0DYyD2th5NeYrf3ucZHlvxQ+A0RpZfpMuDzPjFi7KHHBtOraYI0WH72EH9DkC9K7r71dxFuhh6rkhy8KsqZ6KozDpuid3I/FfmIUoByssajVcjmhHOAv6Ma8aJhokff34l9BssI1hzZRB58lRFXzwHvsPuBXaC/Ij3SrADOUQjUp1ovsmZmZ43fouM+SorTTe83iNzxTS5NkMZlMP4wYe0vNWG/+LwANQ5+uyFMDvBIiWmaLn27ZPQIYxw5C0eHTC8mR+i5RMzUDdycreLpxbKitYSUkcw41o18yXD1AL1BWkDgy1fA2NCOXyG5jAowy9L4UoXjducnqH5O1Qcc+SLhga4rLUpEb4j4UtUJ5cbVIuzv0Qpe5hd+wY7vLs5pMr0ByCRdaHKdaPWWQ==
*/