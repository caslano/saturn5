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
#include "boost/serialization/split_free.hpp"
#include "boost/serialization/nvp.hpp"

  
// macros to split serialize functions into save & load functions
// An expanded version is below for gregorian::date
// NOTE: these macros define template functions in the boost::serialization namespace.
// They must be expanded *outside* of any namespace
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::date_duration)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::date_duration::duration_rep)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::date_period)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::greg_year)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::greg_month)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::greg_day)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::greg_weekday)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::partial_date)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::nth_kday_of_month)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::first_kday_of_month)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::last_kday_of_month)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::first_kday_before)
BOOST_SERIALIZATION_SPLIT_FREE(::boost::gregorian::first_kday_after)

namespace boost {

  namespace gregorian {
    std::string to_iso_string(const date&);
  }

namespace serialization {

/*! Method that does serialization for gregorian::date -- splits to load/save
 */
template<class Archive>                         
inline void serialize(Archive & ar,                               
                      ::boost::gregorian::date & d,
                      const unsigned int file_version)
{
  split_free(ar, d, file_version);              
}                                               

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