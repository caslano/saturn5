//  boost/chrono/round.hpp  ------------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_CEIL_HPP
#define BOOST_CHRONO_CEIL_HPP

#include <boost/chrono/duration.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * rounds up
     */
    template <class To, class Rep, class Period>
    To ceil(const duration<Rep, Period>& d)
    {
        To t = duration_cast<To>(d);
        if (t < d)
            ++t;
        return t;
    }

  } // namespace chrono
} // namespace boost

#endif

/* ceil.hpp
BSZHfWmJGDbXrdeUFyaz7zssk1WWYIHr2ggzIoFHhcnC59JcSk7pDyzlAFu1vGCGUb/m2sDffruJB9bxnC14uPfilPyW/YAZo7t7vzdubcR1QH5wOIVg59cu1I64uJC3d0Zhf/jQItjAiYIkLMaPNE0hkRy7UUtSP8OuwrJIqZRxbK6xgBQ196lQAGYl54FX2IDVd3nqtqxtfUTvh3c3N7tZKDfIcIiob4K+5qHofsEpJnn5Kvg4UKgKJM+/G6TbpUK1ieLvtoKxALvyLUyJLIipxP4MUKB35sCgkY4vNuwP5Cj+Hln4xCz4AcW6tpZtokaVXYacoE8DJqLADjQz9B7HchlCZ6gM8FxV88yzQuANowMGBzrOXkpAt/+Qd6ypdSLUF4c9kRwvPT9THC2fkQcdO3bEpFgF79oR/X0d0D+6IWAGCP3jWoML9JSIx5taW3I7C4Dn6Vt67vv2kG2ZXs9m1OPd2f+TrBCn/aNDd9cIZ7ghEL5Q4CFYD9sh+plklwy30gwwZVOWfPHRYoy4YhjE07MignNrwr3mCN/0vwya9dWAVziMCDcHgV+xCJqG6PAoWoOTqin2jeq8wIXI2j/+fyEncziH7jzygXOkW4+oUS5XzjlsC1jy97ibyBVtAmlMrWhIMZjhpqsq
*/