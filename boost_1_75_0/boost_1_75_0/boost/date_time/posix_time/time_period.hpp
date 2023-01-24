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
8dzZ3NSVY9eIkl8f2M9aYO9XOD4otwdpiM6zng9esxEl2S8IqX/wR06XrFEhMA8oLofskbEcllMrZU0oTPfjDckf5y1aQetEDzwNZgPXgh3B1xK3C/d1MshVDZ/9HZFyW76dhdbfc+36XjM2GBxmsV2P+3LkoOWgBVd5zKaywFC+XOkTxceVfe8YsPXqel7NYvtBY4XvTRqbSU+1X1MwwrIcIl2pAC5A9lJSXM22n7pf+dzpOpmVuzexz0GnazsVtnIxOjgcTLkkuM0CZsCnkmwIthbKVV1Ily6Ju3dWKEXjd+pQH+F3/vF9ZA39xbjazrMm7tdUGFHzPUef+LT1tDr1ehLuw4ubprUg6WhOlqISvpcf2iZqemK6m+Sa7VBCHC9vYYuPGQI5mP4Aq9DwJx6/NvJMNHvG7QKrx32ODl1F8kixp4uQkTxdoWGNWVBszq6Lw78cdvyvrATPmj9VBnfy1senQRba2HcW7LatYWA4h8wsTteY7HZXP81vaHqUJVNhfpJnE+Zx7wZvB0X+1P7iI4SjPiXG8x3/1tjMB16RlmO3IlZ0PkWlgyQWiMVgWUBmOu0E2pPj6T5nPLCxaVHCS8ACb1YETP/NdQWNJ6P+76/GFzyW9ZNaNj5uTVna8bvq1/EWLHgx4Lu+KhHWnoX/4lL4u3BPqFcJo1+7UmrwNDAXPsEt5QpLBRB7vh3Ct9cRtkmOrfLqqyH0
*/