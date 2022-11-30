#ifndef GREGORIAN_SERIALIZE_HPP___
#define GREGORIAN_SERIALIZE_HPP___

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/gregorian/parsers.hpp"
#include "boost/core/nvp.hpp"


namespace boost {

  namespace gregorian {
    std::string to_iso_string(const date&);
  }

namespace serialization {

// A macro to split serialize functions into save & load functions.
// It is here to avoid dependency on Boost.Serialization just for the
// BOOST_SERIALIZATION_SPLIT_FREE macro
#define BOOST_DATE_TIME_SPLIT_FREE(T)                                         \
template<class Archive>                                                       \
inline void serialize(Archive & ar,                                           \
                      T & t,                                                  \
                      const unsigned int file_version)                        \
{                                                                             \
    split_free(ar, t, file_version);                                          \
}

/*! Method that does serialization for gregorian::date -- splits to load/save
 */
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::date)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::date_duration)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::date_duration::duration_rep)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::date_period)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::greg_year)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::greg_month)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::greg_day)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::greg_weekday)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::partial_date)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::nth_kday_of_month)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::first_kday_of_month)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::last_kday_of_month)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::first_kday_before)
BOOST_DATE_TIME_SPLIT_FREE(::boost::gregorian::first_kday_after)

#undef BOOST_DATE_TIME_SPLIT_FREE

//! Function to save gregorian::date objects using serialization lib
/*! Dates are serialized into a string for transport and storage. 
 *  While it would be more efficient to store the internal
 *  integer used to manipulate the dates, it is an unstable solution.  
 */
template<class Archive>
void save(Archive & ar, 
          const ::boost::gregorian::date & d, 
          unsigned int /* version */)
{
  std::string ds = to_iso_string(d);
  ar & make_nvp("date", ds);
}

//! Function to load gregorian::date objects using serialization lib
/*! Dates are serialized into a string for transport and storage. 
 *  While it would be more efficient to store the internal
 *  integer used to manipulate the dates, it is an unstable solution.  
 */
template<class Archive>
void load(Archive & ar, 
          ::boost::gregorian::date & d, 
          unsigned int /*version*/)
{
  std::string ds;
  ar & make_nvp("date", ds);
  try{
    d = ::boost::gregorian::from_undelimited_string(ds);
  }catch(bad_lexical_cast&) {
    gregorian::special_values sv = gregorian::special_value_from_string(ds);
    if(sv == gregorian::not_special) {
      throw; // no match found, rethrow original exception
    }
    else {
      d = gregorian::date(sv);
    }
  }
}


//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, 
                                ::boost::gregorian::date* dp, 
                                const unsigned int /*file_version*/)
{
  // retrieve data from archive required to construct new 
  // invoke inplace constructor to initialize instance of date
  ::new(dp) ::boost::gregorian::date(::boost::gregorian::not_a_date_time);
}

/**** date_duration ****/

//! Function to save gregorian::date_duration objects using serialization lib
template<class Archive>
void save(Archive & ar, const gregorian::date_duration & dd, 
          unsigned int /*version*/)
{
  typename gregorian::date_duration::duration_rep dr = dd.get_rep();
  ar & make_nvp("date_duration", dr);
}
//! Function to load gregorian::date_duration objects using serialization lib
template<class Archive>
void load(Archive & ar, gregorian::date_duration & dd, unsigned int /*version*/)
{
  typename gregorian::date_duration::duration_rep dr(0);
  ar & make_nvp("date_duration", dr);
  dd = gregorian::date_duration(dr);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, gregorian::date_duration* dd, 
                                const unsigned int /*file_version*/)
{
  ::new(dd) gregorian::date_duration(gregorian::not_a_date_time);
}

/**** date_duration::duration_rep (most likely int_adapter) ****/

//! helper unction to save date_duration objects using serialization lib
template<class Archive>
void save(Archive & ar, const gregorian::date_duration::duration_rep & dr, 
          unsigned int /*version*/)
{
  typename gregorian::date_duration::duration_rep::int_type it = dr.as_number();
  ar & make_nvp("date_duration_duration_rep", it);
}
//! helper function to load date_duration objects using serialization lib
template<class Archive>
void load(Archive & ar, gregorian::date_duration::duration_rep & dr, unsigned int /*version*/)
{
  typename gregorian::date_duration::duration_rep::int_type it(0);
  ar & make_nvp("date_duration_duration_rep", it);
  dr = gregorian::date_duration::duration_rep::int_type(it);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, gregorian::date_duration::duration_rep* dr, 
                                const unsigned int /*file_version*/)
{
  ::new(dr) gregorian::date_duration::duration_rep(0);
}

/**** date_period ****/

//! Function to save gregorian::date_period objects using serialization lib
/*! date_period objects are broken down into 2 parts for serialization:
 * the begining date object and the end date object
 */
template<class Archive>
void save(Archive & ar, const gregorian::date_period& dp, 
          unsigned int /*version*/)
{
  gregorian::date d1 = dp.begin();
  gregorian::date d2 = dp.end();
  ar & make_nvp("date_period_begin_date", d1);
  ar & make_nvp("date_period_end_date", d2);
}
//! Function to load gregorian::date_period objects using serialization lib
/*! date_period objects are broken down into 2 parts for serialization:
 * the begining date object and the end date object
 */
template<class Archive>
void load(Archive & ar, gregorian::date_period& dp, unsigned int /*version*/)
{
  gregorian::date d1(gregorian::not_a_date_time);
  gregorian::date d2(gregorian::not_a_date_time);
  ar & make_nvp("date_period_begin_date", d1);
  ar & make_nvp("date_period_end_date", d2);
  dp = gregorian::date_period(d1,d2);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, gregorian::date_period* dp, 
                                const unsigned int /*file_version*/)
{
  gregorian::date d(gregorian::not_a_date_time);
  gregorian::date_duration dd(1);
  ::new(dp) gregorian::date_period(d,dd);
}

/**** greg_year ****/

//! Function to save gregorian::greg_year objects using serialization lib
template<class Archive>
void save(Archive & ar, const gregorian::greg_year& gy, 
          unsigned int /*version*/)
{
  unsigned short us = gy;
  ar & make_nvp("greg_year", us);
}
//! Function to load gregorian::greg_year objects using serialization lib
template<class Archive>
void load(Archive & ar, gregorian::greg_year& gy, unsigned int /*version*/)
{
  unsigned short us;
  ar & make_nvp("greg_year", us);
  gy = gregorian::greg_year(us);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, gregorian::greg_year* gy, 
                                const unsigned int /*file_version*/)
{
  ::new(gy) gregorian::greg_year(1900);
}

/**** greg_month ****/

//! Function to save gregorian::greg_month objects using serialization lib
template<class Archive>
void save(Archive & ar, const gregorian::greg_month& gm, 
          unsigned int /*version*/)
{
  unsigned short us = gm.as_number();
  ar & make_nvp("greg_month", us);
}
//! Function to load gregorian::greg_month objects using serialization lib
template<class Archive>
void load(Archive & ar, gregorian::greg_month& gm, unsigned int /*version*/)
{
  unsigned short us;
  ar & make_nvp("greg_month", us);
  gm = gregorian::greg_month(us);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, gregorian::greg_month* gm, 
                                const unsigned int /*file_version*/)
{
  ::new(gm) gregorian::greg_month(1);
}

/**** greg_day ****/

//! Function to save gregorian::greg_day objects using serialization lib
template<class Archive>
void save(Archive & ar, const gregorian::greg_day& gd, 
          unsigned int /*version*/)
{
  unsigned short us = gd.as_number();
  ar & make_nvp("greg_day", us);
}
//! Function to load gregorian::greg_day objects using serialization lib
template<class Archive>
void load(Archive & ar, gregorian::greg_day& gd, unsigned int /*version*/)
{
  unsigned short us;
  ar & make_nvp("greg_day", us);
  gd = gregorian::greg_day(us);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, gregorian::greg_day* gd, 
                                const unsigned int /*file_version*/)
{
  ::new(gd) gregorian::greg_day(1);
}

/**** greg_weekday ****/

//! Function to save gregorian::greg_weekday objects using serialization lib
template<class Archive>
void save(Archive & ar, const gregorian::greg_weekday& gd, 
          unsigned int /*version*/)
{
  unsigned short us = gd.as_number();
  ar & make_nvp("greg_weekday", us);
}
//! Function to load gregorian::greg_weekday objects using serialization lib
template<class Archive>
void load(Archive & ar, gregorian::greg_weekday& gd, unsigned int /*version*/)
{
  unsigned short us;
  ar & make_nvp("greg_weekday", us);
  gd = gregorian::greg_weekday(us);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, gregorian::greg_weekday* gd, 
                                const unsigned int /*file_version*/)
{
  ::new(gd) gregorian::greg_weekday(1);
}

/**** date_generators ****/

/**** partial_date ****/

//! Function to save gregorian::partial_date objects using serialization lib
/*! partial_date objects are broken down into 2 parts for serialization:
 * the day (typically greg_day) and month (typically greg_month) objects
 */
template<class Archive>
void save(Archive & ar, const gregorian::partial_date& pd, 
          unsigned int /*version*/)
{
  gregorian::greg_day gd(pd.day());
  gregorian::greg_month gm(pd.month().as_number());
  ar & make_nvp("partial_date_day", gd);
  ar & make_nvp("partial_date_month", gm);
}
//! Function to load gregorian::partial_date objects using serialization lib
/*! partial_date objects are broken down into 2 parts for serialization:
 * the day (greg_day) and month (greg_month) objects
 */
template<class Archive>
void load(Archive & ar, gregorian::partial_date& pd, unsigned int /*version*/)
{
  gregorian::greg_day gd(1);
  gregorian::greg_month gm(1);
  ar & make_nvp("partial_date_day", gd);
  ar & make_nvp("partial_date_month", gm);
  pd = gregorian::partial_date(gd,gm);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, gregorian::partial_date* pd, 
                                const unsigned int /*file_version*/)
{
  gregorian::greg_month gm(1);
  gregorian::greg_day gd(1);
  ::new(pd) gregorian::partial_date(gd,gm);
}

/**** nth_kday_of_month ****/

//! Function to save nth_day_of_the_week_in_month objects using serialization lib
/*! nth_day_of_the_week_in_month  objects are broken down into 3 parts for 
 * serialization: the week number, the day of the week, and the month
 */
template<class Archive>
void save(Archive & ar, const gregorian::nth_kday_of_month& nkd, 
          unsigned int /*version*/)
{
  typename gregorian::nth_kday_of_month::week_num wn(nkd.nth_week());
  typename gregorian::nth_kday_of_month::day_of_week_type d(nkd.day_of_week().as_number());
  typename gregorian::nth_kday_of_month::month_type m(nkd.month().as_number());
  ar & make_nvp("nth_kday_of_month_week_num", wn);
  ar & make_nvp("nth_kday_of_month_day_of_week", d);
  ar & make_nvp("nth_kday_of_month_month", m);
}
//! Function to load nth_day_of_the_week_in_month objects using serialization lib
/*! nth_day_of_the_week_in_month  objects are broken down into 3 parts for 
 * serialization: the week number, the day of the week, and the month
 */
template<class Archive>
void load(Archive & ar, gregorian::nth_kday_of_month& nkd, unsigned int /*version*/)
{
  typename gregorian::nth_kday_of_month::week_num wn(gregorian::nth_kday_of_month::first);
  typename gregorian::nth_kday_of_month::day_of_week_type d(gregorian::Monday);
  typename gregorian::nth_kday_of_month::month_type m(gregorian::Jan);
  ar & make_nvp("nth_kday_of_month_week_num", wn);
  ar & make_nvp("nth_kday_of_month_day_of_week", d);
  ar & make_nvp("nth_kday_of_month_month", m);
  
  nkd = gregorian::nth_kday_of_month(wn,d,m);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, 
                                gregorian::nth_kday_of_month* nkd, 
                                const unsigned int /*file_version*/)
{
  // values used are not significant
  ::new(nkd) gregorian::nth_kday_of_month(gregorian::nth_kday_of_month::first,
                                         gregorian::Monday,gregorian::Jan);
}

/**** first_kday_of_month ****/

//! Function to save first_day_of_the_week_in_month objects using serialization lib
/*! first_day_of_the_week_in_month objects are broken down into 2 parts for 
 * serialization: the day of the week, and the month
 */
template<class Archive>
void save(Archive & ar, const gregorian::first_kday_of_month& fkd, 
          unsigned int /*version*/)
{
  typename gregorian::first_kday_of_month::day_of_week_type d(fkd.day_of_week().as_number());
  typename gregorian::first_kday_of_month::month_type m(fkd.month().as_number());
  ar & make_nvp("first_kday_of_month_day_of_week", d);
  ar & make_nvp("first_kday_of_month_month", m);
}
//! Function to load first_day_of_the_week_in_month objects using serialization lib
/*! first_day_of_the_week_in_month objects are broken down into 2 parts for 
 * serialization: the day of the week, and the month
 */
template<class Archive>
void load(Archive & ar, gregorian::first_kday_of_month& fkd, unsigned int /*version*/)
{
  typename gregorian::first_kday_of_month::day_of_week_type d(gregorian::Monday);
  typename gregorian::first_kday_of_month::month_type m(gregorian::Jan);
  ar & make_nvp("first_kday_of_month_day_of_week", d);
  ar & make_nvp("first_kday_of_month_month", m);
  
  fkd = gregorian::first_kday_of_month(d,m);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, 
                                gregorian::first_kday_of_month* fkd, 
                                const unsigned int /*file_version*/)
{
  // values used are not significant
  ::new(fkd) gregorian::first_kday_of_month(gregorian::Monday,gregorian::Jan);
}

/**** last_kday_of_month ****/

//! Function to save last_day_of_the_week_in_month objects using serialization lib
/*! last_day_of_the_week_in_month objects are broken down into 2 parts for 
 * serialization: the day of the week, and the month
 */
template<class Archive>
void save(Archive & ar, const gregorian::last_kday_of_month& lkd, 
          unsigned int /*version*/)
{
  typename gregorian::last_kday_of_month::day_of_week_type d(lkd.day_of_week().as_number());
  typename gregorian::last_kday_of_month::month_type m(lkd.month().as_number());
  ar & make_nvp("last_kday_of_month_day_of_week", d);
  ar & make_nvp("last_kday_of_month_month", m);
}
//! Function to load last_day_of_the_week_in_month objects using serialization lib
/*! last_day_of_the_week_in_month objects are broken down into 2 parts for 
 * serialization: the day of the week, and the month
 */
template<class Archive>
void load(Archive & ar, gregorian::last_kday_of_month& lkd, unsigned int /*version*/)
{
  typename gregorian::last_kday_of_month::day_of_week_type d(gregorian::Monday);
  typename gregorian::last_kday_of_month::month_type m(gregorian::Jan);
  ar & make_nvp("last_kday_of_month_day_of_week", d);
  ar & make_nvp("last_kday_of_month_month", m);
  
  lkd = gregorian::last_kday_of_month(d,m);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, 
                                gregorian::last_kday_of_month* lkd, 
                                const unsigned int /*file_version*/)
{
  // values used are not significant
  ::new(lkd) gregorian::last_kday_of_month(gregorian::Monday,gregorian::Jan);
}

/**** first_kday_before ****/

//! Function to save first_day_of_the_week_before objects using serialization lib
template<class Archive>
void save(Archive & ar, const gregorian::first_kday_before& fkdb, 
          unsigned int /*version*/)
{
  typename gregorian::first_kday_before::day_of_week_type d(fkdb.day_of_week().as_number());
  ar & make_nvp("first_kday_before_day_of_week", d);
}
//! Function to load first_day_of_the_week_before objects using serialization lib
template<class Archive>
void load(Archive & ar, gregorian::first_kday_before& fkdb, unsigned int /*version*/)
{
  typename gregorian::first_kday_before::day_of_week_type d(gregorian::Monday);
  ar & make_nvp("first_kday_before_day_of_week", d);
  
  fkdb = gregorian::first_kday_before(d);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, 
                                gregorian::first_kday_before* fkdb, 
                                const unsigned int /*file_version*/)
{
  // values used are not significant
  ::new(fkdb) gregorian::first_kday_before(gregorian::Monday);
}

/**** first_kday_after ****/

//! Function to save first_day_of_the_week_after objects using serialization lib
template<class Archive>
void save(Archive & ar, const gregorian::first_kday_after& fkda, 
          unsigned int /*version*/)
{
  typename gregorian::first_kday_after::day_of_week_type d(fkda.day_of_week().as_number());
  ar & make_nvp("first_kday_after_day_of_week", d);
}
//! Function to load first_day_of_the_week_after objects using serialization lib
template<class Archive>
void load(Archive & ar, gregorian::first_kday_after& fkda, unsigned int /*version*/)
{
  typename gregorian::first_kday_after::day_of_week_type d(gregorian::Monday);
  ar & make_nvp("first_kday_after_day_of_week", d);
  
  fkda = gregorian::first_kday_after(d);
}
//!override needed b/c no default constructor
template<class Archive>
inline void load_construct_data(Archive & /*ar*/, 
                                gregorian::first_kday_after* fkda, 
                                const unsigned int /*file_version*/)
{
  // values used are not significant
  ::new(fkda) gregorian::first_kday_after(gregorian::Monday);
}

} // namespace serialization
} // namespace boost

#endif

/* greg_serialize.hpp
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
*/