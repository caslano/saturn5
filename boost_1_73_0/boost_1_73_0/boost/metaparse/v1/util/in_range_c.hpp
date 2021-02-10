#ifndef BOOST_METAPARSE_V1_UTIL_IN_RANGE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IN_RANGE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class T, T LowerBound, T UpperBound>
        struct in_range_c
        {
          typedef in_range_c type;
        
          template <class Item>
          struct apply :
            boost::mpl::bool_<(
              LowerBound <= Item::type::value
              && Item::type::value <= UpperBound
            )>
          {};
        };
      }
    }
  }
}

#endif


/* in_range_c.hpp
ABY/PDbNLEaQ7rEPg0d41QfaCQcQjqLRY0SYl1+px9bYHLCJwHkLTLvgZbZFj020sqhs8BPVxlYRPLQlhbkVWkWQS22uUOmxRsfyaXlld9JjHguH96NvZN+ZdW2czFMfNzCRwp0yokAW5+2CIJ1+wiprazpwXsYq22FySQcCDaUrQSDgQ9hK7y2cfUyFqbURzmP/shlMia0jiXO922WqAF07zNhXOiBIvbd9+hIql/sC/c5CxHlvtlin82XUc+LLxSrl4f33BydMJqTecDpbComuShoncpIhE7YdT8JqbCT01qvJdL7iUry7qLnSlJUw1tzVsiU6MVydI7pTMG1kb9iI8gjt6LPSYgO2wnZuUGUG3hEV+KbS1mfxocU6G422OtcyYS64zvz5onhsRmIR/NOjx35T9MHThsRp0PtG8t7b82o9X7x67CnPsabyLb91QybHFwkWt1GAS3rs/5XO/3xDW49n/8Mr/8YW1MLJfocbOhy/BMy/fuo/UEsDBAoAAAAIAC1nSlJAs6R2FwIAAHcEAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTM3N1VUBQABtkgkYOVU227iMBB9t5R/GKXipSI1UHarpiFSBVVBu1sQZPueJhNiEewoNnT5+x07
*/