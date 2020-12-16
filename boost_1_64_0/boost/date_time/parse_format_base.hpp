#ifndef DATE_TIME_PARSE_FORMAT_BASE__
#define DATE_TIME_PARSE_FORMAT_BASE__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

namespace boost {
namespace date_time {

  //! Enum for distinguishing parsing and formatting options
  enum month_format_spec {month_as_integer, month_as_short_string, 
                          month_as_long_string};

  //! Enum for distinguishing the order of Month, Day, & Year.
  /*! Enum for distinguishing the order in which Month, Day, & Year
   * will appear in a date string */
  enum ymd_order_spec {ymd_order_iso,  //order is year-month-day
                       ymd_order_dmy,  //day-month-year
                       ymd_order_us};  //order is month-day-year


} }//namespace date_time

#endif

/* parse_format_base.hpp
MkvrEA++RYNGWfomB7mgCXexx4ZDbpbKk9IMSZPvoZsJqICJSeq4nift0HWTW2Y4oRlHi32A/HeZAUc+L1lYxYZnE4t+f7VCt9+9Kem2HJ7FZkAMbjYui2voW2dSM+UeBugSOwpRSoSNbaqV362vke9e7SoGsXcvP3CBag1Wq3XLG41qTG5pyzB4EcSJWOi0rYG/9vD7R/jeDH8f4jt4tqWlpdkdTmdaCvxwpOEH3uEntdm2Ix9r+2VSD8+vY0wWJROhiYwG0/ELDsUi0GOpz3yQw2Ozt4en5/BJRmp/SjzhCPDSSeDz2xsPJdA620+aGe19Uks1Te3yfg4ehfum/b64JrUNPMCw+n6XUJ28DXLs71N/gecgDvdMZBOp/4RHVAzlkRmqL1LHjGYB8DkJuAIB4SUDe1ucl2t773S6NiMSkCP66bWQ/ejaS2uyhBPSYQ1P8XNNsZ9KW/a6pNIkrksfxLN5SrA38BzpfVG3xbfI3AMjDE2AEoZqaLoV1Tpo6tslXMMDYJ+73xHUOsOa0vAQPrHnD3lPiVXcI0VbUGcPrIbX8qya2ERfZRRVvUaMh1gVCsaLaD0ofI8a5w29DppTPF5PbnwVm95/3qgpYUFZ4IR1DH+ya55pJI7+/T1B1NTFkubnRtpB0uS7RdKLr8qkAeIi7LSetDw5imsaDIyWwJbUMrDD0kuxXhsffpI3LfX2ujyMsq5pl7i7sbvBMgNOK7duwh5BerLZX4nzu8VKaBndSrJzIQhBnsYVnyxPLwWj2RL8VYJdAcR45N0cxXXfQn3DJOvHGOu7wK7x0J33Ib8wj+f76BPUcqy0XOY1gUbEmz5GZGD6db839qKxKgL5SVwSi2ArJQKbW3iNKJbXZdRI7+U8Yg29wWz84klbh+AcWbPqdMXRlZIKyuvAQwHokdnPUY+UMv47QTypFdGOUYQG5NQ7aPeGfYL37/6Wo1nZ97tZiga7cdfMhNSAgMzUQ16vQh64SUKuFhfFlevoUlPZXN0B46nzedBk2vLi2RZjetNws37cnQr2q/8qsaPYr51ZD3HwC0hKv/HxNnOTQ7i/wMHgE1sHze5YsBN2o2MTORATJZ4YkSGCdyLnHgx7YWLlvZECtKcGmuxfnsO3qNN3KhXes0BWeKnsR/0u+vnlOmrue1sBX79ATpURdIY1TGkgZqNmlSjqXVTe4hsvRRKXV1WoBMOFiqH/iP7vX6hQuPqGDYo9WcdpluzJpmyIsSc7fxOHS1yef4P+EGTHW2JdyN1i4TwH5m5gc9LnLyq8LUG62YGRcmo+fT2vfweqfyuof10pUxNda3KI04kOcSJvykOcD+QhTvEdTF/DzmoLxEVVv8UjHeN6pjaiBB8DEgVwwR1Qg81m/b9O6f8z55h2AcJP3qnAE2glgdY5GV2WcNBE/a+W9+HsuOV9/DdDeam8vE744DYtL3F769cq5V8Qv/yhbxvKn02gdc3xYeFtTZf/aJzy/Wr5H86KX76R3qm8/GzW/tus0Xv7I0p5l8Uvb4axvbcRaF0HfFh1q7XyRqnl/TIzfv++ZSivGy/vGHwosFje3oeV8m6KX97QNw3lPUmg5IW//hZr5U0noNBSmLzS0mD5ZabAavlFRvr24ahKGKqG0Cf15liIXq8jvNJfO8zH1+6HFHpMuyEuPVq9YajP/QRKQQs2LLZGjwq1vJbxy1tkLK8PL+8ofPBbLM9GQKHLgwr9212akP69Xjf2/4OEKjdI9L/ohSboP3q7nv6PvqZ/XrTdvD9KqRCq557pcelz9w5D/doQKJkIeBY1zW9aYfvM5v8aauT9zyr0Ck80RxYz/znoJc8SfU55nkM1Of/XqPP/+rjt3WE=
*/