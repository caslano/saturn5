#ifndef BOOST_METAPARSE_V1_ERROR_INDEX_OUT_OF_RANGE_HPP
#define BOOST_METAPARSE_V1_ERROR_INDEX_OUT_OF_RANGE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <string>
#include <sstream>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <int From, int To, int N>
        struct index_out_of_range
        {
          typedef index_out_of_range type;

          static std::string get_value()
          {
            std::ostringstream s;
            s
              << "index (" << N << ") out of range ["
              << From << "-" << To << "]";
            return s.str();
          }
        };
      }
    }
  }
}

#endif


/* index_out_of_range.hpp
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
*/