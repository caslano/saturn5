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
O5fLvMDyPwHBey0vma8w/wClFW7rSuHlqEU7+lNnYHgo0Wz1TQ3OphTur4IPJsn7bV2hcoP33D86iu8oZKVbd6zhBULJBv1kwKAzFW4QJCxbh2Pj5wOC9xAQuW4aqYqQjQ1Mx5MZkNYF5/sPizSbxxf7JBIvkoxPjk+oxC+aroMJMveMpipb6JoBWTo04FYI3dJgJS0sERWM7Eq7ERMbjyWBtdFO57oO2VMaJSBpVm2jP23A4us07Wxc4Zds1jUeUFWKvtwFftEBy17jCOYBS+dvEZCxgHafZjAN/B/oI9c3iyRgj0/zLCCzu2KC/zrgu2/1A1BLAwQKAAAACAAtZ0pSRIbaQ0wDAADfBQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzNTBVVAUAAbZIJGB1VH+L2zgQ/V/g7zD1dSEpm3V+0Cst3nDtJksDLZtLvF16hAuKPd6IOpKR5KRmt9/9RrKzCYVziC3Nk2fezLxxbNHYlBscs1jIXNHjB9YHpTMzZrfJnC2myYLF0ckYR8059gcsUe9R94zIkMUay6ImOOOWg1TpFtMf12GNJhyzXCnFdu4WRw53Xtrz5OamECht6yb1mzGZ7VYY0Eh7A0rSFiHDTfUIOXJbaQSrgBeFOkBl
*/