//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_DETAIL_PTIME_TO_TIMESPEC_HPP
#define BOOST_INTERPROCESS_DETAIL_PTIME_TO_TIMESPEC_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/posix_time_types_wrk.hpp>

namespace boost {

namespace interprocess {

namespace ipcdetail {

inline timespec ptime_to_timespec (const boost::posix_time::ptime &tm)
{
   const boost::posix_time::ptime epoch(boost::gregorian::date(1970,1,1));
   //Avoid negative absolute times
   boost::posix_time::time_duration duration  = (tm <= epoch) ? boost::posix_time::time_duration(epoch - epoch)
                                                              : boost::posix_time::time_duration(tm - epoch);
   timespec ts;
   ts.tv_sec  = duration.total_seconds();
   ts.tv_nsec = duration.total_nanoseconds() % 1000000000;
   return ts;
}

}  //namespace ipcdetail {

}  //namespace interprocess {

}  //namespace boost {

#endif   //ifndef BOOST_INTERPROCESS_DETAIL_PTIME_TO_TIMESPEC_HPP

/* ptime_to_timespec.hpp
C7EPzwsKdCPMeEM95hU+SkEDm/TKAec1YdI2v2/5jLzIGYeezD9KrXHfG2pWf3vKGtQOGQ1zFt0vIml80VWjksD+oZZWIg9rY+rVFBYsY+uM3DZLCT59S70F+Yzk9Osh86I2qfS6HoJ7E1zOOA2OEfvQz8fWp+nFmf4acE1hPHJO7lmhh7kE6bO9R/f7OJNAWQTgOxv7tsH5GyPP80gyPL8EhjeagaLpSitB7c2o8NV/5TdI3zHK4tJG6gl6z5KXj+obVEgYpGZn7VtWuPuH5EfGf19bodYC/7EdKzjPUDauetris/8bQMa3RjwJ7piJmpi89LirtMac9t5NvLgJ8kvNRvryhekVXt9KU5hIex7htFx7mMhWvn9jO8mZtNxAHUsPg0+bxRj3zL4pQuQp4VkL1jtaIHuMlS2rXjtQC0QIAL+lfdudwQaxO+VqqQxn5MXm3+TlipECSOmJ4qcUTHSRA2GCviKebJ7pcMxd0l0LqcufsPrDwBKLY9ct3y2NX6LOSxqGY/b1y66sQfoTUtlVMlkVNjwL79Oqwq15309YgdMtS+voPT52GLOX4abHVKoXWtTwm62lhAniKn/2AjTsIhIb3rHWjjqNXCt37vJAYr2zk8yd3+BqzixfxRS3Kg/jBMwsmxx2EJZR3uRh4/m/ST86PQGO/8LKrLfrnyI34QE64Ajv3Y2pmURRHG/Rx2eXUTeYLppqu13E
*/