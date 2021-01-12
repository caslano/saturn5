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
1quOdA+h0rPFx2W9nmvi58IHdL+Lw7sg2Axem8l7ulWi18CNEtoc/XX5N8f9l+LuH6wv9z3nXMNxxH8RFo7ojYzrq9sv11v76jtQv1/TC2zPGr9Yztozz5tmcmb3M9gNIj1vcDGa1jp8DMeWtA1mc5zJwDBKp5Fc9Kxkh2K6PO5U/a9v4j6be6yv15lSUY46nuLyUqv/zv+8cz0fWeJwE+vwsiQMdKryqy4RZU+qa+E51QdT
*/