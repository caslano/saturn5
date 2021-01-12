#ifndef POSIX_TIME_PERIOD_HPP___
#define POSIX_TIME_PERIOD_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include "boost/date_time/period.hpp"
#include "boost/date_time/posix_time/posix_time_duration.hpp"
#include "boost/date_time/posix_time/ptime.hpp"

namespace boost {
namespace posix_time {

  //! Time period type
  /*! \ingroup time_basics
   */
  typedef date_time::period<ptime, time_duration> time_period;


} }//namespace posix_time


#endif


/* time_period.hpp
3flOoTPQnslo4+C5f9qaRL2ZTcX8quNpz9ZtT4lLmo3r38TtCZhj4ddVVZfPMU21DbWQ6y842ufGrrs5YMewM8TNNc4oJ2KS+9F87SczxM0rzjPkyxonpcGzjZ4Wt+lWz+BgifPtZjAtvsDGowY94eWuhldVcBWfq50n/i81c6m7Gm+bxzi2c5ol4u4W+rZMmVetTZN9J+ZdOScvjX4hEI64rb1NHnVu5Qz+6hmRNE2TdJ+o
*/