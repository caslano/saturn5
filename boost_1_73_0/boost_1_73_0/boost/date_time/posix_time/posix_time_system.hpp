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
DhYGFMVYKtCU894dbmVUdylQSHq2fGsJDaJnxt60FNpGu6tk/ZUh0to7KlslMBzSgnaFROJ9aEVBlbN3RAxRepYd5U+UbIe9ACkQFYzCBKJkBBuimfbhKkov4lUKV+FyGc7Ta4jPIJxf9/4+RvMPqA2GURXQ+0ZRjSgUsLrhjBZfBf+hne4F6QVMVstZvEizaH4WzaZJ9McUjmF0eAK/tQKVffhqBCPONrb0cBIcnwQHuGDfMkr0NtPU2CLjF/Wk0WVyAfPwcup9x+/6JRbVgGaf6cAyE01rOlljRTTFgsqydF6S63m8SKLE+4mJnLcFhbc2bCfC6r3nIuQS1x+j2bP/wIsK5cFRJd8i8YFLcePCWjD7b1zAD9NksowWaRTPvauKCmgbLknB0JL8B5FgZ9USVaqZQd/rMhq8rMvF0IEbaiXvRGasigf+7ipsJps2VhknJVr8DxdMB53MbglvKdStNtZpQzS69bClicsggIT2/YpAvs0zm4XL8+ne8b7FVrqeEi4fhxk4wR5UnkGi4Oj8NPC8M7TZZd1q+5tMFn43OroiW2k+HQ1brkb+iZFqi45THALCFt/ssiI3hAnfSYK5MfHyEC0d8wNOWuMU0gOQy3RAksvaeocckT8gWyOrOF0sm14HluBAttLD
*/