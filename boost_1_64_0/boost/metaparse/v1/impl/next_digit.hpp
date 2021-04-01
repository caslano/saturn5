#ifndef BOOST_METAPARSE_V1_IMPL_NEXT_DIGIT_HPP
#define BOOST_METAPARSE_V1_IMPL_NEXT_DIGIT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct next_digit
        {
          typedef next_digit type;

          template <class PartialResult, class NextDigit>
          struct apply :
            boost::mpl::int_<
              PartialResult::type::value * 10 + NextDigit::type::value
            >
          {};
        };
      }
    }
  }
}

#endif


/* next_digit.hpp
UN2A92sUsbHu/ADBd3mRb/Mdt+uAXDsXrKZSxki72KK+pdw3ZhezdoipwOAQoGTPLiZ+HZi1QtwJpQMV+7K/P+nMz4NGnMYGcNYMTqmxmdxpP4oSQxnsuJMWkuRsE6nLKe4434RT36Oc9F88fEeLXKyzM7axpHjCiO0Sug75bmwYvwzZrCIYebGytM2VJeSGsC00zYQg/K3JT0wTi2Jy/s/28SNMLY+NZYejeaW4LioB+eNqW8e8BSWRHqjtj7I3yBsK1jwrh9AurjVnBCfJTlZaHH4AIQVhsaVJzyPY3ODdHdog450yQbTdrP3H02I9qn7HcTRCSHC8ygddVb4m0oYCQXoL1jtBiK1Pc16vgLklGuwBFlBihEt6ycblfw6/wbDY3NaeQj9L+nFDuVv+PhI9NN87ir58ZX0H03zfpXdovB46CKfYVOhGOg4tTmkyZ1Q4ofP28zYcKWNFEGCxhaW2LgthLo0OMCMduBUcryfR+o4ulB1WnN4bJ5TnL6pZbpTfcKgg2eAliZdloAGQjtkkxzB15bJg6kR1+rWnlJsf2QtpQsiK5fw+HA==
*/