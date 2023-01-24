//  boost/chrono/round.hpp  ------------------------------------------------------------//

//  (C) Copyright Howard Hinnant
//  Copyright 2011 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/chrono for documentation.

#ifndef BOOST_CHRONO_FLOOR_HPP
#define BOOST_CHRONO_FLOOR_HPP

#include <boost/chrono/duration.hpp>

namespace boost
{
  namespace chrono
  {

    /**
     * rounds down
     */
    template <class To, class Rep, class Period>
    To floor(const duration<Rep, Period>& d)
    {
      To t = duration_cast<To>(d);
      if (t>d) --t;
      return t;
    }


  } // namespace chrono
} // namespace boost

#endif

/* floor.hpp
7jY+yb1lh3U7fCFAYs59G7RlX2yz1HqSSSYLWAEIQZv9YvSzPCIMO7+5iA07G9UuZYugoX/2tVjYGrOQ8L9esfw12hozqo0rL8I2nOY24i7S24CK/4oVb/dpFVfFcMWLLmhVcUS9cy/EelPM9R7vb+57TT/dKPVOvk2G1j59DVpb+7VmVGoXRqVZrVvTdKljn/jf7TGdZI9pEsLcrHe4/mpdCMN4mR7kdH6lITCJys3Ymxd4WaJQIv/CC+7QrvfjLBqdImHsKyzOVAsE7bc6Y9XDaeHreo4X8WFwOMY48HyGnfOc+y3FzMgJvIseLHDhUJaj8llZk/I8hr8MvMLbtDy8SGxWzHu6LliopZsf3hlp8yuM6kEW35V/XIs6SeqDJGtepFvU/GJYATMwSMcdwIfCIp4UeJa24DyMYfoK00qNNeBcIYWCL27sBJ2smJCaj/9ch/9cj/+MyJP3Y6CrIvy80czAkbkwwJXUjNAv/K26QkuIuwEwLRBtNQo25GyhImJrMNhOSklz3MlUihm4NCszcFhhJAO32MzADYMvw5fmlf+CosU6rZsG+9No7ECvaNVrbBz39fIlYvPRinaNLJqTCeBwlMeSs5c/dQb2HiHomX0CGSlHeQVG6a8aDx1R8j7jg+vPQeYOlcWSFg+bnoBHVrmwIa0zxItk4QFTpHS+TYgX3KFX3o2jqa4jhJmQWponH8LfxNICd1EE
*/