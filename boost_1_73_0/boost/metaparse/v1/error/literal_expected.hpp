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
xc74AAPwJ+yHv+AwfISj8VecjY9xET7BPdLXyknIgufQFR9gVvwVs0mfStmxEObE+pgLO2IeNGFeHID5cBIWwCnoIX2reLrI71x+957Yj+AmfUs1ojyVsQnWxKbYAJthc2yOSdgCZ2FLnIut8F38Oy7DNvgetsX16IfHsQPewY74EDvjr9gVs1Ko7tgIe2AABmA49sJB2Bvj8HWcjX1xHgbiYuyPhzAEz2E4XsGBeA0H4SOM
*/