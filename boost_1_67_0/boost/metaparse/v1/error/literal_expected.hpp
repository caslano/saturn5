#ifndef BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP
#define BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <char C>
        struct literal_expected
        {
          typedef literal_expected type;

          static std::string get_value()
          {
            return std::string("Expected: ") + C;
          }
        };
      }
    }
  }
}

#endif



/* literal_expected.hpp
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
*/