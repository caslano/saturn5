#ifndef POSIX_TIME_SERIALIZE_HPP___
#define POSIX_TIME_SERIALIZE_HPP___

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/greg_serialize.hpp"
#include "boost/numeric/conversion/cast.hpp"
#include "boost/serialization/split_free.hpp"
#include "boost/serialization/nvp.hpp"
#include "boost/serialization/version.hpp"

// macros to split serialize functions into save & load functions
// NOTE: these macros define template functions in the boost::serialization namespace.
// They must be expanded *outside* of any namespace
BOOST_SERIALIZATION_SPLIT_FREE(boost::posix_time::ptime)
BOOST_SERIALIZATION_SPLIT_FREE(boost::posix_time::time_duration)
BOOST_SERIALIZATION_SPLIT_FREE(boost::posix_time::time_period)

// Define versions for serialization compatibility
// alows the unit tests to make an older version to check compatibility
#ifndef BOOST_DATE_TIME_POSIX_TIME_DURATION_VERSION
#define BOOST_DATE_TIME_POSIX_TIME_DURATION_VERSION 1
#endif

BOOST_CLASS_VERSION(boost::posix_time::time_duration, BOOST_DATE_TIME_POSIX_TIME_DURATION_VERSION)

namespace boost {
namespace serialization {


/*** time_duration ***/

//! Function to save posix_time::time_duration objects using serialization lib
/*! time_duration objects are broken down into 4 parts for serialization:
 * types are hour_type, min_type, sec_type, and fractional_seconds_type
 * as defined in the time_duration class
 */
template<class TimeResTraitsSize, class Archive>
void save_td(Archive& ar, const posix_time::time_duration& td)
{
    TimeResTraitsSize h = boost::numeric_cast<TimeResTraitsSize>(td.hours());
    TimeResTraitsSize m = boost::numeric_cast<TimeResTraitsSize>(td.minutes());
    TimeResTraitsSize s = boost::numeric_cast<TimeResTraitsSize>(td.seconds());
    posix_time::time_duration::fractional_seconds_type fs = td.fractional_seconds();
    ar & make_nvp("time_duration_hours", h);
    ar & make_nvp("time_duration_minutes", m);
    ar & make_nvp("time_duration_seconds", s);
    ar & make_nvp("time_duration_fractional_seconds", fs);
}

template<class Archive>
void save(Archive & ar, 
          const posix_time::time_duration& td, 
          unsigned int version)
{
  // serialize a bool so we know how to read this back in later
  bool is_special = td.is_special();
  ar & make_nvp("is_special", is_special);
  if(is_special) {
    std::string s = to_simple_string(td);
    ar & make_nvp("sv_time_duration", s);
  }
  else {
    // Write support for earlier versions allows for upgrade compatibility testing
    // See load comments for version information
    if (version == 0) {
        save_td<int32_t>(ar, td);
    } else {
        save_td<int64_t>(ar, td);
    }
  }
}

//! Function to load posix_time::time_duration objects using serialization lib
/*! time_duration objects are broken down into 4 parts for serialization:
 * types are hour_type, min_type, sec_type, and fractional_seconds_type
 * as defined in the time_duration class
 */
template<class TimeResTraitsSize, class Archive>
void load_td(Archive& ar, posix_time::time_duration& td)
{
    TimeResTraitsSize h(0);
    TimeResTraitsSize m(0);
    TimeResTraitsSize s(0);
    posix_time::time_duration::fractional_seconds_type fs(0);
    ar & make_nvp("time_duration_hours", h);
    ar & make_nvp("time_duration_minutes", m);
    ar & make_nvp("time_duration_seconds", s);
    ar & make_nvp("time_duration_fractional_seconds", fs);
    td = posix_time::time_duration(h, m, s, fs);
}

template<class Archive>
void load(Archive & ar, 
          posix_time::time_duration & td, 
          unsigned int version)
{
  bool is_special = false;
  ar & make_nvp("is_special", is_special);
  if(is_special) {
    std::string s;
    ar & make_nvp("sv_time_duration", s);
    posix_time::special_values sv = gregorian::special_value_from_string(s);
    td = posix_time::time_duration(sv);
  }
  else {
    // Version "0"   (Boost 1.65.1 or earlier, which used int32_t for day/hour/minute/second and
    //                therefore suffered from the year 2038 issue.)
    // Version "0.5" (Boost 1.66.0 changed to std::time_t but did not increase the version;
    //                it was missed in the original change, all code reviews, and there were no
    //                static assertions to protect the code; further std::time_t can be 32-bit
    //                or 64-bit so it reduced portability.  This makes 1.66.0 hard to handle...)
    // Version "1"   (Boost 1.67.0 or later uses int64_t and is properly versioned)

    // If the size of any of these items changes, a new version is needed.
    BOOST_STATIC_ASSERT(sizeof(posix_time::time_duration::hour_type) == sizeof(boost::int64_t));
    BOOST_STATIC_ASSERT(sizeof(posix_time::time_duration::min_type) == sizeof(boost::int64_t));
    BOOST_STATIC_ASSERT(sizeof(posix_time::time_duration::sec_type) == sizeof(boost::int64_t));
    BOOST_STATIC_ASSERT(sizeof(posix_time::time_duration::fractional_seconds_type) == sizeof(boost::int64_t));

    if (version == 0) {
        load_td<int32_t>(ar, td);
    } else {
        load_td<int64_t>(ar, td);
    }
  }
}

// no load_construct_data function provided as time_duration provides a
// default constructor

/*** ptime ***/

//! Function to save posix_time::ptime objects using serialization lib
/*! ptime objects are broken down into 2 parts for serialization:
 * a date object and a time_duration onject
 */
template<class Archive>
void save(Archive & ar, 
          const posix_time::ptime& pt, 
          unsigned int /*version*/)
{
  // from_iso_string does not include fractional seconds
  // therefore date and time_duration are used
  posix_time::ptime::date_type d = pt.date();
  ar & make_nvp("ptime_date", d);
  if(!pt.is_special()) {
    posix_time::ptime::time_duration_type td = pt.time_of_day();
    ar & make_nvp("ptime_time_duration", td);
  }
}

//! Function to load posix_time::ptime objects using serialization lib
/*! ptime objects are broken down into 2 parts for serialization:
 * a date object and a time_duration onject
 */
template<class Archive>
void load(Archive & ar, 
          posix_time::ptime & pt, 
          unsigned int /*version*/)
{
  // from_iso_string does not include fractional seconds
  // therefore date and time_duration are used
  posix_time::ptime::date_type d(posix_time::not_a_date_time);
  posix_time::ptime::time_duration_type td;
  ar & make_nvp("ptime_date", d);
  if(!d.is_special()) {
    ar & make_nvp("ptime_time_duration", td);
    pt = boost::posix_time::ptime(d,td);
  }
  else {
    pt = boost::posix_time::ptime(d.as_special());
  }
    
}

//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, 
                                posix_time::ptime* pt, 
                                const unsigned int /*file_version*/)
{
  // retrieve data from archive required to construct new 
  // invoke inplace constructor to initialize instance of date
  new(pt) boost::posix_time::ptime(boost::posix_time::not_a_date_time);
}

/*** time_period ***/

//! Function to save posix_time::time_period objects using serialization lib
/*! time_period objects are broken down into 2 parts for serialization:
 * a begining ptime object and an ending ptime object
 */
template<class Archive>
void save(Archive & ar, 
          const posix_time::time_period& tp, 
          unsigned int /*version*/)
{
  posix_time::ptime beg(tp.begin().date(), tp.begin().time_of_day());
  posix_time::ptime end(tp.end().date(), tp.end().time_of_day());
  ar & make_nvp("time_period_begin", beg);
  ar & make_nvp("time_period_end", end);
}

//! Function to load posix_time::time_period objects using serialization lib
/*! time_period objects are broken down into 2 parts for serialization:
 * a begining ptime object and an ending ptime object
 */
template<class Archive>
void load(Archive & ar, 
          boost::posix_time::time_period & tp, 
          unsigned int /*version*/)
{
  posix_time::time_duration td(1,0,0);
  gregorian::date d(gregorian::not_a_date_time);
  posix_time::ptime beg(d,td);
  posix_time::ptime end(d,td);
  ar & make_nvp("time_period_begin", beg);
  ar & make_nvp("time_period_end", end);
  tp = boost::posix_time::time_period(beg, end);
}

//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, 
                                boost::posix_time::time_period* tp, 
                                const unsigned int /*file_version*/)
{
  posix_time::time_duration td(1,0,0);
  gregorian::date d(gregorian::not_a_date_time);
  posix_time::ptime beg(d,td);
  posix_time::ptime end(d,td);
  new(tp) boost::posix_time::time_period(beg,end);
}

} // namespace serialization
} // namespace boost

#endif

/* time_serialize.hpp
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
*/