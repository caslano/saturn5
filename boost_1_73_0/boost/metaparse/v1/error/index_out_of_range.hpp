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
lbSBwWFBUQPoGo68+Zun/E2dRvuzbZ7F5PthSnFDWVQZr34nzToqKIKnCdRv9qj90Zks1s9fKf16LSf+mHqoQ+hIPUB6X3XMg+WiRz4Zd083Lkj6/tH3f/SzPBxh7YujMqJSv3uOK/WrVa36nTz3l+vD7sgp+2cq9hjiqwzx5PR41nzzT/L/Sndzf831ptWvzFP3XUizbl7qPG4qfV2p+StrWSnXZWt6xts+TKhNVUS+QWZJ
*/