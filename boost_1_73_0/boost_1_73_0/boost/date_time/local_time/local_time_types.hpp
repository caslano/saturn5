#ifndef LOCAL_TIME_LOCAL_TIME_TYPES_HPP__
#define LOCAL_TIME_LOCAL_TIME_TYPES_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/local_time/local_date_time.hpp"
#include "boost/date_time/period.hpp"
#include "boost/date_time/time_iterator.hpp"
#include "boost/date_time/compiler_config.hpp"
#if defined(BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES)
#include "boost/date_time/local_time/date_duration_operators.hpp"
#endif //BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES
#include "boost/date_time/local_time/custom_time_zone.hpp"

namespace boost {
namespace local_time {

  typedef boost::date_time::period<local_date_time, 
                                   boost::posix_time::time_duration> local_time_period;

  typedef date_time::time_itr<local_date_time> local_time_iterator;

  typedef date_time::second_clock<local_date_time> local_sec_clock; 
  typedef date_time::microsec_clock<local_date_time> local_microsec_clock;
  
  typedef date_time::time_zone_base<posix_time::ptime, char> time_zone;
  typedef date_time::time_zone_base<posix_time::ptime, wchar_t> wtime_zone;

  //! Shared Pointer for custom_time_zone and posix_time_zone objects
  typedef boost::shared_ptr<time_zone> time_zone_ptr;
  typedef boost::shared_ptr<wtime_zone> wtime_zone_ptr;
 
  typedef date_time::time_zone_names_base<char> time_zone_names;
  typedef date_time::time_zone_names_base<wchar_t> wtime_zone_names;

  //bring special enum values into the namespace
  using date_time::special_values;
  using date_time::not_special;
  using date_time::neg_infin;
  using date_time::pos_infin;
  using date_time::not_a_date_time;
  using date_time::max_date_time;
  using date_time::min_date_time;

}} // namespaces

#endif // LOCAL_TIME_LOCAL_TIME_TYPES_HPP__

/* local_time_types.hpp
yqZC9XwTlmn8/6CoeH3bY85HZxrY1I2dyJslXhgYM4L1I50VykyijmFHW8m3ao/gmESlHJ7RAq9A3eue+UgbbhqHFrBlGG1Foecq/9xlAtgIqMcemgX+LisOgZobOS1IW8kv0gJKFwfGPy1D6elJ0vWssSy8HUm247i4uEFHz/B4tCxmUHDVOURaPQmX9txPjIl+m0VhEjqhHxuKYL3l/mW/n/murl5XCw3v988qxWomh0gqK4ZqcwSfsBBPFW2oPMP3LwqrNp4LiosJg93QovcEG4laGV+PB6MXuH9dD3Dka2eEsAcYBw+ysO7Qnhn/GlbB9GHtD7bn2xee7yULw87zboqfWJNfrDfaIHKTeRTAB9ufu0ZEJc4moUG4aXgNrBtDXTepqop2s+ENzphu7nWG8+A6CG+CNNTSU04176sxiF0XbD8OsRMvoqfTxcnUjSIYYAWRpKftqXsxf3c5Dxwdp/+653igAG2DJv8BUEsDBAoAAAAIAC1nSlJxM/xzxgMAAGkIAAA+AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9IVFRQX1RSQU5TRkVSX0RFQ09ESU5HLjNVVAUAAbZIJGCtVF1zm0YUfedX3FFfpAxBVtyp69rNlGBc
*/