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
GdnfI8ZMGH1DNAVaFEYSA4JkUaik0nbaJyRyUt1nB0pjqyvYoJbA4+UPnplHXG1kqltGtXMEKeqtee4DEpuJ6SeBva81W2NVN7yugd0i7spltGsbi2RQEeJBjka2WhJcYvFwSNbWaUxfcO0D/G/Ky588czxM22ZM7mXct8eTaI4QywfAZf+qrI/Z6GiBRG1FXrVSyE7VW1w2V1ZumAZSZDS4ppagCt0MeUHrlOs1Q1so0EuQvm63nqy7WvMDa9Zu6K3kmGJdy80O1goTp1a1zG/coV01jHQalvMS+5qgYTziopAIKaRG79R5ZQ7L7tBbDOw+ppN0eBB0dhFE4/CcIHbLNBocpl22vQXuWrfsRG7r0ClXRfRLc3Dney0VqkRxE7Jbv89EdU0j8fpwHDyRMTi6TR/b28UZAVabfOGikBuFmEbotEEvy6md3GPbiwpzuWGssYkYG8UotJVoykBLqw+mteMVBeHg/b5hL4L5OCWT+Xg8sA23qVAtt72Zp6Op0VZ+gw4uCuS949rcZ3bvdBan8SgeJyQwlwyOhH8GV9NxSHxREucglodf7/kLF1wfoVvw8sgMHsPfBJ7ajxk42A4+BuDt7k92R9HTmY/6GpZS+isuPAT8Nsw99/KYrk76XVjvBxn2RXXpPcLN
*/