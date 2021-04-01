#ifndef YearMonthDayBase_HPP__
#define YearMonthDayBase_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include <boost/date_time/compiler_config.hpp>

namespace boost {
namespace date_time {

  //! Allow rapid creation of ymd triples of different types
  template<typename YearType, typename MonthType, typename DayType>
  struct BOOST_SYMBOL_VISIBLE year_month_day_base {
    BOOST_CXX14_CONSTEXPR
    year_month_day_base(YearType  year,
                        MonthType month,
                        DayType   day);

    YearType year;
    MonthType month;
    DayType day;
    typedef YearType  year_type;
    typedef MonthType month_type;
    typedef DayType   day_type;
  };


  //! A basic constructor
  template<typename YearType, typename MonthType, typename DayType>
  inline BOOST_CXX14_CONSTEXPR
  year_month_day_base<YearType,MonthType,DayType>::year_month_day_base(YearType y, 
                                                                       MonthType m,
                                                                       DayType d) :
    year(y),
    month(m),
    day(d)
  {}

} }//namespace date_time


#endif


/* year_month_day.hpp
jcj7fWfHFRZ3E5/LqgUuUhHbE6lYyfNvnn+Y8EXmYGj3zKGULKArpF/z5+ElTGXe+vW9vgin87APyAKT1wsAIBOCGRVDbEoekxQWJBmaNHMHtFxd/q1gtWIRY5QL7BbBWI11xvpmkgkSjgG1Ac8ZQAGTXomcerqI7HPp1C49TivCFfG1uf254pSjRAAAG9JVKtwgMTFd1QsC9HfgiKsVmkUFXRrjt5e8p4z2VkzNb0arLfynYeoxX+8MvmbKrCLHqCB6OGr7d9b68lp0GuM33QXabcQf3ulnk5IyYRGibv1vzUwZfbf0MhVPE7f/G7rLEMqaMo7yvlZzHjjEBKQ5JiE7Am9jOFz+N5vrj0BX9DMn0BJZs+/tNrdWFjtVQdawyKmngrfpRY4CVcKlT5fYKMQwfNzUBQyFpEKUZp9bfFP0qsYzApi3Zfs//H9yRYDeNyF2GN0Ai9dLG1XyL/Ec4SptHR5b8VoGP6VZgblZlAXlvL4TjAqWI1erums/gN66rpTuRa2jVBMVkm+9avCj5kON7458/R9sVLR9+UtwNHw5y+KC1a0P6yaPeA==
*/