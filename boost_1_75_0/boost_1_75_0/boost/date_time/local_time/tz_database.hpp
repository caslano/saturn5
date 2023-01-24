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
zvswWXGZ0vXfgEQJrXz5j893x3ZnbvTZ0xX685wvzHyGI5bZn5jZftj/8qvTLGHJnBa1FKcbsybMzD9On9tVLhGgOnMtj6q+TFc+uklfSBcqEIvKHS/FLFWztq5VkRPduijbesShKpuhyhVjdgsalqzDyEM3W6DUmmq+zSGkI0saKfaU7dCXptuXqDHLic05cqnBzWoFi4qq/MxK8ATdGLQqC0R9evrVXEd9MGm81EBxirjBo2N5NDTkkhfMgtVeLMHP4n7EIf1R498wB0gAUB98NpcNNZnPqsMu2udJ5Zmw9JY7rdsHziiCpbOxXNOwkuaYXuxKKtnZNrqLY2Ml05rnNI93TtN0xNNnqDAnTdhWrBY85lPH/iLD3Ceg+xMHjOQnUzOgqCrWsv/mgeNtxWnfi3JM090+TJaHcdEYevL1QZntwWQ4OgKIRn2CkF2EfArhku+WJ+9h9dMduIqNoIeYffpNXoq2kuy9kV0YCUbE0gLqDMywmda+umJhAaM/Ij7wBKd4JS7GzBYqKfEg9WH8dJGIXu8auuLvDxq0+2wWw0ZCGG91pKHZLWa50yvsvZEe+jchpKGbpsNq65dejD+G1bI9/DxWYvqZBTF8N2KWcxr2m9nWbtfQEI+f2nFDIVV7ZX1/SuomLhdURbyrDofUHzzW+GSOqAVLVDEBj3Mb8cer6s66xQ3yrTo6NRtlVepL9EwrDLqDFU6P
*/