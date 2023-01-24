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
00frVy5hir+OeNTD5GGT7Svf13d9677uwzd45th5gXumsnFlWUg5BKnMbyDNUVJoRzUUW4qNiPH/XEr6x7FUOAt2pbFEWYxaEsmoOEYzYhhUJpPiCzxQVnlVSLXFuYoW8k29+4wdzd163HI9en+qKo2p//v4l5taHGO3ZIh0D/PN2qhHHfmsRg+w9Wab9X0lmNfgORytcUWcXvKjD0CTV2kZXYX4J7y5QXDFQn7DAxTtnZZmxM65v9T9d8Dc6gE10AZdVkXbf++2rQ4wNcfk9ChdmW8biHmo65TrpPcoaLGyeZku5fncnUjnmcsqv/FgCMjufE1sf8MTcgb9XKp9eff0QtCrGPEVDMh9sqW+BpNReYc+ySR4BhlReJN7BR9kG3MnegZFy29BgtM6oOvTB53b/vJbOGQWdwE3/fJ3ItMH/nv78lsMgMGDzj1iL9Bt40OiK77f4eKxjol3MMt4JxaVHZlSWXs0QhdRoQ+Je0f0NpqHBLYMS0Tt7A8+1fGlhlvB3WcDVzvri6gdHO1YiUmKAMTiMTbS5sJSJfIZapEALXute71YKl1RrcHgKDma0+fs461PAGnsIxW5h/TbNAZHtQsPh1wv0cgzFJbvIP/+x/lWYDEcKbkbqyrPXWRS9DulOVW39Kq2V7yL7NrtYfFZRAZbZ88z37vvD8ToD8Xx8fWg7BLzCpP8MP7nDJtH4hKfu+SAyyL2OUcM
*/