#ifndef DATE_TIME_LOCAL_TIME_CONVERSION_HPP__
#define DATE_TIME_LOCAL_TIME_CONVERSION_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/date_time/posix_time/conversion.hpp"
#include "boost/date_time/c_time.hpp"
#include "boost/date_time/local_time/local_date_time.hpp"

namespace boost {
namespace local_time {

//! Function that creates a tm struct from a local_date_time
inline
std::tm to_tm(const local_date_time& lt) {
  std::tm lt_tm = posix_time::to_tm(lt.local_time());
  if(lt.is_dst()){
    lt_tm.tm_isdst = 1;
  }
  else{
    lt_tm.tm_isdst = 0;
  }
  return lt_tm;
}


}} // namespaces
#endif // DATE_TIME_LOCAL_TIME_CONVERSION_HPP__

/* conversion.hpp
rVontU5KHpFDJ3PUCF5SPunfv0+8vGcznt+R3zO7Z1Z/ksre+ZhUVPB2bpDrX/9iZqkjCnP9ScnJdDcLCCSpoLQw3z+BHz1oMvG40PYlP0kFhXnjRzbrz6bdnDOq7X/gZLNpD+dMdFJIEnvWebNi9pwLvqgeF2vMmOPIHnsXiCmcVYtzWActQjoEcQz7BHNOkPz+Tovda22f2pzzsWQLldMnhHNqye9/f77DDdunDuecQD4hlk8o57CDPZunGb8=
*/