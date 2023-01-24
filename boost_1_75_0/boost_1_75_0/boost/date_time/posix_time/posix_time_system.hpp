#ifndef POSIX_TIME_SYSTEM_HPP___
#define POSIX_TIME_SYSTEM_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */


#include "boost/date_time/posix_time/posix_time_config.hpp"
#include "boost/date_time/time_system_split.hpp"
#include "boost/date_time/time_system_counted.hpp"
#include "boost/date_time/compiler_config.hpp"


namespace boost {
namespace posix_time { 

#ifdef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG

#if (defined(BOOST_DATE_TIME_NO_MEMBER_INIT)) //help bad compilers 
  typedef date_time::split_timedate_system<posix_time_system_config, 1000000000> posix_time_system;
#else
  typedef date_time::split_timedate_system<posix_time_system_config> posix_time_system;
#endif

#else

  typedef date_time::counted_time_rep<millisec_posix_time_system_config> int64_time_rep;
  typedef date_time::counted_time_system<int64_time_rep> posix_time_system;

#endif

} }//namespace posix_time


#endif





























/* posix_time_system.hpp
20Fqvvrr1aQzHvV6N8a2dfBEYMybQvJiogX0Rt1LhEVbtQPz2IKhhTbu7seGpZrkeZS2coPlmHnRmBag6PnCFet6m/4Vnr/qvInzYF3XnqBpy6gvdPQdWDcFnIbSbGNzB1jRH0AxIzegIvooXTgEaKCsqVwezHcocRfrBqumHDCuqFPmlQ0pgPA98ueHvwr4PgcosqMBCguoxOHbcbwVDHo/cRx6b710FanTfcWX+RDcLYEGL5l1GeHdYGJDoSHrejJk4Dfpj0iKU/wKbw71QECpXhIy5KuMCNXpNRhC+xzb++b98ZSIEvul7qOTGhodDy6GdBI8C28f+/P+fPqZi+l1v/OD6Sh3VUlTrjv0oJvF4VVQwAgT9KwncL/Yw4I4Ac2K/HjDuiuGBoRickL+VVLXT/hjHY7xvwCX6b8CLud/SurKLo6WLuaurv8hXKCfnpa7yJPOXS1feOIf6zna6ISmqVjamEO+cDW6+mpyyRJnm724lOLse9POldqRBG+fiP2UQCGiNlFuNoP+QA21oJB6FXRVTWPiy7ZeHh4Q7DqqWZ2K9gqb8YxDLrtk+WOnyFZj1UjF5QPmWKgv4LjzbX/DN2Dj/kr4Sdbo+T3ieMvzpc1RWUZAXAOsmh9TEXmWJhpPhPKl4V01X9mpAk1ErrYCbJYX4q1XfDQbyZt7T2TMUoehjakPZwfDisiq1lRcjvKwPDH72AhOTI9R
*/