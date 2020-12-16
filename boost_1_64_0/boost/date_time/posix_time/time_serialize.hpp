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
lmrY0v2dN93qWoVbtqwhMbqKAn7aRTHgJ8LCd+40aD/R9MVUfAsWZ2rRlARjFK1wE8zRcQaVfi+WBn0cnbWmpkECecYZ9cMYVaukiKaYZTSwvZjvJ7BhAstOPDnIWOMarLFmDfVzfTqeCTadfOtQPfm0Xi8W/gvWi8thvbjRrBezVMBK8pMWyjtE2NG3I7T90YzLp2790KGU2JD8EDh8seToKNodBeycTiFfb8NeBOdwFNsDC7Hy9HIWD27rgqAqNb0T4W+pCfKSaDiwdoheAP8/t6T79HOQX2RFXjqP5VfIEqvyxaXiQMTKEosCy8dzcBMkfrF2vkNkffNYGZ/WqAe5YD6N/KWpcXUEke0uLpN8G5WZnbZW5ffHe5ytaDGRVQ3KdH5Fm6EhQ/ACRTCwdX8ZP+nz/3bP+WlzTf+BTacNsA/AwoNPZwatPedLzQWadasnnkatnmYNG6tHzVoL4FjiuToqFaCjfiEN+nIF+nid0KYpclPu3TXYFF6Q1qK1+z4tB65/CeTANSAHbjVyoHoqin049UnjY3y7KL9Re40EQBy21Qa8bOoveWf6tpq7zN4ZDKqa0rClI2FtPHQ+ml1h1Hcmqwf1MgtB86d+5a5ahJHmAAE7UDbwzRV6BBZhCff4hzVVGNtAN8xV5zzT+hRp5BGMrzS3ZexPgo2VAVrx1htEtATQ6tcXxpDTMgQdE90Bm1l6qTj4gvJPIjbcwijshN4DD1FbXYmXCQH8wCIiQF3SK4uhtMVdOXApK0HN6/o3rxrhsY8Qjs+WmoAep/uG0Ar+5rMM7FLszjlGNWwESdQQR7W8AWeK5irMg4Eyh2uejqX5cLRqp6wRUBuRqXE96+wQdZI0/I0c0YAAeHvXuDCcdqMZ8Az1vPZa1EiZgVmHDRBISHrmULSQAumqKEatCosgonaP/t2AA0v3FNGyWmnObVR6iBErUR4lr+zu5gP/YzTA/R7W1RuwzdhixQ1vgBup1knV3jWL5dO2tHzapOXTr/5q5NMnjHzaXoXyKa59PNts8ili0qScqWY5Uw0XjrCarYcqsnYQJ8BGdPMImEu04hxdxOpuLqm7m9G6VNHVkzUeufWFQ8sq/Awt7+JnwzQ3AKctSnPaw15xvJBAa65OlZoTuwUa/c1ePcwRLgjbo21a6oQZCItOpgEYR7Vxcifog1wI7aVoAHy7SmyCC9xRxMVx9YrikoZbsQF8Z/6M2iIoO5P7OKySqIhZSwAiF2kavxTEZlrqJdCo6h3WUiEk9e1dheZ+S5xLktbUx2wIZLDsQNPOGDQSeok5wdhupHv/r59FsasGM2cYJ0lLYgWGzMeH6ZWkKfHqQmb9L3nTCyKLOV6mw3qHn8OtNs7q9Da73H0nPvNbbZTLlvgkWN80ypKF6clxpoMKIVWCqEZsPreL+HkdriJZesgLErNEyFJUQfOj7EM157nqdY1nEmL/PT7EQI7SVXSlnfpSwCuywK5gFQJgvskuCgt3b4TFNGExJiyGhKXasNkURoPPyJxF+Eic+eZY0Hu4UmDP82fn8Fb7984zW+0QAy6/lbLZi9LYBIqsr8KpB6UiASjEr7K9dL8jbVx3vV3hoVLRGRpkvJhTdP8ONqU/7GdPDXd0lclbTHkRYoOA2c//B8VtoW+jmhm3KlEf5UsffqR99RX+5tHULtyqb0X4gcTbY8rGHkFlAs5lFkCZIx5dJrj2jLo2Jd5qAa1T6Z+Xq9L7UQkgv93H52qzSUtZdFar0YjqHQ0lLjkPFgLaGq+Dd9BamueBaf3MIT6/sX4+NQy32uhetoArMRVq1yo1G/sFq0dM9UezqV6o2oIvNMpp2bKVyubDCZJupQr/uI7qv60=
*/