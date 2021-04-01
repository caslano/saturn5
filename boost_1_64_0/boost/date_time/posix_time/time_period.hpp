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
QulQrtNmGkDME2BQhlFp9KGseWHNqRrOUFwNjSIYvys3xC8KTkutdzRxPcZm4kXd2xnSEa/dH4qNPLxAw55/Ei21133wvDajlyUerGBpACGK/FFEHpYnfkQN8hRrW7yE7F6KtgzEQQMxK/AwU7/MdilmgznKWFrWCnxOphPqvK6qZrc+XM8Tctd05UDUEwlU8+cDRFdOfbAoklWy2J/aXx2+q/+u1yAvCDKrN/AI4tvNP5TfMNRIsCUdfzxywADARvSz0L7nXESn2dDPiETgTBHv/lVLsYtN4tjZgEoFnYF50srCEEDwO9im+ucEqSnUbIiPY7BDBSI+7gVrNVIw8VYEtN9yimfc9ZxLh0ow57Q7NRerT5T9mN3W+6zn0nDlyfZDyrcx0cxl1Z+bWoR1CPZitWCFweXDnC+HeeyklDU2/70IgyZuwiFkDgBFOM7xufg74NAQKbNVuWHfIbRQIeiY8kIdhXTQWj/BR1GcXvUtPeflW1nTWVPx8tWe3tLMsYFedMSqnBDI2s1KqwTb3GGHlth3Jy9X22u54B8FeNSO1pMnlD89j+enDQ==
*/