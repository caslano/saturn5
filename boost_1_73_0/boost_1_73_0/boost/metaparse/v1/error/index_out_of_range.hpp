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
P7G1CkbYsVwIFbBWh32nQNvkVdovAXSlpKCmkFmv0BJzRr3kuYgnvFNBHWgzhINlXnID5t+uxM1CmtroLxmVXBGZlrCziBvPdFYQnoOnFWv2vdVmKASwGy+rylubFpLYPQfrrRWG4j6atZSmHpls5UEkykvhiI8nuRGSMg6IzksDcZ1jfihm+B45uH1FLBXBHyM2avRt9uBiJ4rlcO4MF7hTfs06vbOngBkri1JyOeAL68XOMBHplJMEQrEO59Q=
*/