#ifndef DATE_TIME_TIME_PRECISION_LIMITS_HPP
#define DATE_TIME_TIME_PRECISION_LIMITS_HPP

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */



/*! \file time_defs.hpp 
  This file contains nice definitions for handling the resoluion of various time
  reprsentations.
*/

namespace boost {
namespace date_time {

  //!Defines some nice types for handling time level resolutions
  enum time_resolutions {
    sec,
    tenth,
    hundreth, // deprecated misspelled version of hundredth
    hundredth = hundreth,
    milli,
    ten_thousandth,
    micro,
    nano,
    NumResolutions
  };

  //! Flags for daylight savings or summer time
  enum dst_flags {not_dst, is_dst, calculate};


} } //namespace date_time



#endif

/* time_defs.hpp
q7GO6W+yFvHdyFmH+PXI34CcHvIt+Un5afl78n/Iz8s/kV+S/1P+L/m38h/kgG+D7/O+kP86//3+7/p/4P+bPxSoDKwNXBzIB94auDnwgcBdgc8GvhT4RuA7gR8GXgj8MvCbwCsBSQkrqlKpzFLmKguVRcp5ygZli0KvdQj+F8a+vCtcBd37Jl89lJ8MNUL5SJCWFyi0nJBp+YEoLS+Kz4OyLdwK5YCPlqEoLbcEF0GZk1dE6d4k3esrwZGkErq/VAo8GUZBFMoyQvcvy+G6yXDdVCjngESG60ZHxlwYEzJcgSqaI4BxsAjWY4PkKLmevBee0/eRL5OHyNfJo7DueYJ8hzxN/p38gGyVBqQj0hukN0s3SO+QbpZukz4k/V7aLPtPaGPajzkFQnYqh+nHfIj5b3V0mayNfJ63I6LVUlgWSzsiYYP6jIXa7+Op9wZ5KmhBnm+hPsYorV2PRPQ7qhJ6bYlMj0l2/B92fIUdfZJ2DLBjkB1VdkywYzk7zmLHBnZsZMeF7NjOjh3seB47rmLHbnZcz4497LiJHTez44XsuJUdt7HjDnbsZceL2fFSdsyyYx87vo4dd7NjPzsOsGOeHfez4xA7HmTHQ+w4yo5XsOM4Ox6B4x7pvIAEq3QZfnRP1g+/APwU+AXhF4JfGH4R+EXhF4NfHH5F8CuGXwn8VPiVwi8BvzL4lcMvCb8K+EGvwPjdDHPZZhjB
*/