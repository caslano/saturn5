#ifndef BOOST_METAPARSE_V1_GET_PREV_CHAR_HPP
#define BOOST_METAPARSE_V1_GET_PREV_CHAR_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_prev_char.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_prev_char_impl;

      template <class T>
      struct get_prev_char : get_prev_char_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_prev_char.hpp
zC4dz2nOb7JFF49dYc3MO2YT0239cKaHaxvsLdUNapoSOjdtY5etxnxEX9+yYe9lnxqZgo8czCRDPVobBeHaqaa+LGlbkA+qW5ZZom57cAH0vrgnPIYgyZkXWl01qkCEVTKKiyH0LsHJYUoGJGprBWaeLKSix/1zHoKU+Fj4j+C/PwioNHs2rj1DmB4WsB7gcIZc7DANqPwuKfd/WM+8GqJvwpg6EX0lNZGaPwZLvKiyMYvlv662t1CjZvCA58dTaNvNlXy/UMIy0xtkoaLwXpdxhURLUmKv4v2+iMfImDOGlrlZh2m33rDX6kEb/MXD1Pi4JKAmAGCSMIuKCSjWfkHyahADoi9b2QLI/4vG8g3gbibHynihs4G3reZIZpZiIS5JFM2bANPG2oTIQpMiNnYrKuNOzLhl9y4HohnaTEp+NByhlpYpXXo2juwaCAFV55n5WnJuSCKFV+/tSa6wmMmEf1X/BKVjN+6uiJ2tF1rHBuq2Ebx62LIyzb47LKr8bxnwmQErJnRt1BIZq0qC2FXp7xMmhBJ9icb5xjB3l7Gxk20MDJziCtzDGw==
*/