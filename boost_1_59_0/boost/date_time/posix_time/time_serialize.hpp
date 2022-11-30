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
#include "boost/core/nvp.hpp"
#include "boost/numeric/conversion/cast.hpp"
#include "boost/type_traits/integral_constant.hpp"

// Define versions for serialization compatibility
// alows the unit tests to make an older version to check compatibility
#ifndef BOOST_DATE_TIME_POSIX_TIME_DURATION_VERSION
#define BOOST_DATE_TIME_POSIX_TIME_DURATION_VERSION 1
#endif

namespace boost {
namespace serialization {

template<typename T>
struct version;

template<>
struct version<boost::posix_time::time_duration>
  : integral_constant<int, BOOST_DATE_TIME_POSIX_TIME_DURATION_VERSION>
{
};

// A macro to split serialize functions into save & load functions.
// It is here to avoid dependency on Boost.Serialization just for the
// BOOST_SERIALIZATION_SPLIT_FREE macro
#define BOOST_DATE_TIME_SPLIT_FREE(T)                                         \
template<class Archive>                                                       \
inline void serialize(Archive & ar,                                           \
                      T & t,                                                  \
                      const unsigned int file_version)                        \
{                                                                             \
  split_free(ar, t, file_version);                                            \
}

BOOST_DATE_TIME_SPLIT_FREE(boost::posix_time::ptime)
BOOST_DATE_TIME_SPLIT_FREE(boost::posix_time::time_duration)
BOOST_DATE_TIME_SPLIT_FREE(boost::posix_time::time_period)

#undef BOOST_DATE_TIME_SPLIT_FREE

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