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
V0RwMflihFkNGVKtzUvAP1brQ7qzJlrIVWHN2yyBcqHR+XsyoyOGRv5ojZeoSsYsF076iURxqUCATH9IYRMv+RHSogRIdWlJosop3dmWQDFVcigWjcueNOV67VT0/ktXilflSkf+CXeTqzwrwL3I1JhfjQf4VmtKOS5dw1fFh4jJoY1ZosTEuOaRRY8ogRPnH4U0NfE1QJVGtBJKqRQMO2LsUEgGF0AN62jNm2OLHsMbqljq07OYOyJrPFu7/ig=
*/