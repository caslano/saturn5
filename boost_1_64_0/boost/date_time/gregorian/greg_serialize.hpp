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
7DVDCn+upfD29iXrxsvlwe2Vl8uDmypAvawF9UeCivDJe5/yTZT1XlvRBYMUgfm8NIV5cEWXF4lbSlfdIoZukw4qJGp5mwxAhQfWMH+XAaiNlgIVcbw1OB+v0ffWQCao8AWc3C2Uyq1MlEJ1eokbSn1qErZw69Vuip5KUV47Ndn46Di8vfLRcXhTxU3759qb9kEqvwqfvPcp30RZHXpIdGCQIjBZiESFe3CF+v7W0lW3iHErL1BOISRqeYEKKBxmttwfLP18WyxBoTfzVvp2CiFZayCLwqEolFvrElKYT/gmyiGFQ6MQtnRr1RooHFZTeMfs37765LAW08Oai+XwsPJieUhMET7Jfco3Ue5SFluH6npmc2gK8+CKLhW3lq66RQyBcauDASlrJ5CDNzdm+NwfLP18Wyy1HdLjoYZjCslaA1mYHhJTcwulcisTppCdHvKGch+LH5JUr3lT9DyA8rqx+J1/G4tLc9ffb/ivfzneyV98tT/2x/7YH/tjf+yP/bE/9sf+2B/7Y3/sj/2xP/bH/tgf+2N/7I/9sT/2x/7YH/tjf+yP/bE/9sf+2B/7Y3/sj/3xnxzPvPXMI6Nndvsf75m9lbYyPoN9uV/8Vf/kX/Vr/AbdZefbn36fPbbF9xlGB7vjjc/Sz+AcvHLfE+t3d39n7979/VP37/7ccfz0/Qe/3/3sc+ODxzeyevXmxzc/vHTrwcH6992RfznlYW3HnGE7Jop8ByoUJ/y5nTe2v+x2Zb753c3Fb2nOOtypu7M9pfNnHjmlZ3xZ9AAGO2Xp+RQhoYXVmaygGeO/k7Tp9oz6b6ifsZS1rHRXDUVbFp2oKLlT+Ttw5N/BgSTt5Ep+8V7brbs7lzHN5Qk2fi7NNtuRWuQtOPMWQPIWJBn7tuHo9012iGLvzTF7cAcDfKJYPmUE1QSCHJ7S4Wnu6JGnkr89936q4XtsO2WeFznPiz/zvGbQRZnnBdoPLazekxU0R0rUrpz6y5xRL33PSlENXxKxPO+K6E7l78CR9QikrJ3s5CDPRzSXp8sgz5GN8gzf3oL3vAWQrAWQlZYjpEUOUey9ecQeZJ5RbN+m9Tyvs8MFHS6uBM9zx/O8LvLcLfO8zHle/pnnDYMuyzwv0X5oYfWBrKA5VqJQzq+NKKMsVS3P8zGKkB5WRxHdqfwdOLIegZS1k50c5PmY5vIEGz+X0MbyDEfegg+8BZCsBZCVlmOkRQ5R7L2ZTmypPKPYfG48z5vscEmHyyvB89z1PG+KPPfKPK9ynld/5vmcQVdlnldoP7Sw+lBW0EyVqF059UOmb8ZS1fI8T1F0aHneFdGdyt+BI+sRSFk7gfz3PE9pLk+w8XNpslGe4dtb8KHnBJK1ALLSMkVa5BDF3ptT9iDzjGL7XrLn+Tw7XNHh6krwPPc8z+fMc/6hxjc26URmPJGpleF/3dkv+7sC/PfD4c+//64nhrvenHYb7vVw8NqBPUtA+JOcC3YNSr3DVQ062EC+YbY4s7kY2Kloco8QYqkqOkJzFI0MoV0R3an8HTiyzoaUtZOdHCA0p7k8wcbPKLQxhODbW3DD0w3JWgBZGZ8j43KI4tytUKofRRE05vbCKYKAr+WwBtzyXxY1PwZc/B2nYYDTsMDp93PR9MmvoAMNef3L487+Kzn74/9/2Khs1d2Nyl74Oo3K9L3J/G3zv70r5urRv/vnTfeefNO9h5dOPbLdU9xxdwVvQ4Wr2j12RWTRwiomE1ah3aO7+K/tPD6YQukyofi6LrIJn28fUoDsAI/5f1Zb5PLJTsDlCsF+31g79dIUaOxF9yz0r7mqFF9zbX4/fqfh/fdsxDB8K8Cbv+Hrg9b3r3Wbv+bauUo=
*/