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
ae+vd2O68vth8l1CryjlONt7HnVoNaGnUXprNseD7PnS+qpAYv70mAXrXnVYGJkXWCgJ5owfNVHAUvQH40V6yEg6EJn5qJ3Q8cR+CrpRW+602IrzxubI1HyStH/FX6K0jiAZJRJA5CuR7SORX6Q34Ixt71wJkutAQjUGAIaapwWz0CG6iDXNXopRATCTbJu3JDkpE7OoZXNCorm2Xut50y5MxSKTKQOBz0QlLwx7NzXmtYwLULfOkLmQyiJ6LcfEVVXmb8UVul4L6/beKlH6EuoLSdpEa7uwmxUZsnfhn1P/w9rv3T2hQvm/1X3XxxeaeNKHBWpKl7RfeRNIexMBtHdK3PATAdWl6i9t1ZQBbIGAxwqPteVFjuBfxGKjodw2EJZ+slFdULRzr14k4WadiSYph6La7x6Oi5aWar3exUfnZZFmtXvMbcubo28szy/T9E6HmGY4yygwjWAgne1Lia2Ubdzj39aFS4NU/vaCSFXXnlPAjPy6PWTeRFdO07ZA+/TKhTGMKhKikEHwCrFFqx53T9P9ScLwHL1jzGczK/jxYC8sqEN2AsY/eg==
*/